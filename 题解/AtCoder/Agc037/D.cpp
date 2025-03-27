#include<bits/stdc++.h>

using std::vector;
using std::pair;

#define fi first
#define se second
#define pii pair<int,int>

namespace Flow{
	const int MaxN=410;
	const int MaxM=210000;
	int La[MaxN];
	int Ne[MaxM],To[MaxM],Fl[MaxM];
	int cnt,tot;
	void Init(int _tot){
		cnt=0;tot=_tot;
		std::fill(La,La+tot+1,-1);
	}
	void Insert(int fr,int to,int f1,int f2){
		To[cnt]=to;Fl[cnt]=f1;
		Ne[cnt]=La[fr];La[fr]=cnt++;
		To[cnt]=fr;Fl[cnt]=f2;
		Ne[cnt]=La[to];La[to]=cnt++;
	}
	int Dinic(int sur,int sik){
		vector<int>High;
		High.resize(tot+1);
		std::function<bool()>Bfs=[&](){
			std::queue<int>Q;
			std::fill(High.begin(),High.begin()+tot+1,0);
			Q.push(sik);
			High[sik]=1;
			while(!Q.empty()){
				int fr=Q.front();Q.pop();
				for(int k=La[fr];k!=-1;k=Ne[k]){
					int to=To[k];
					if(High[to]==0&&Fl[k^1]>0){
						High[to]=High[fr]+1;
						if(to==sur)return true;
						Q.push(to);
					}
				}
			}
			return false;
		};
		vector<int>Cur;
		Cur.resize(tot+1);
		std::function<int(int,int)>Dfs=[&](int fr,int fl){
			if(fr==sik)return fl;
			int used=0,test;
			for(int k=Cur[fr];k!=-1;k=Ne[k]){
				Cur[fr]=k;
				int to=To[k];
				if(High[fr]==High[to]+1&&Fl[k]){
					test=Dfs(to,std::min(fl-used,Fl[k]));
					Fl[k]-=test;Fl[k^1]+=test;used+=test;
					if(used==fl)return fl;
				}
			}
			High[fr]=0;
			return used;
		};
		int ans=0,test;
		while(Bfs()){
			std::copy(La,La+tot+1,Cur.begin());
			while((test=Dfs(sur,1000000)))
				ans+=test;
		}
		return ans;
	}
}

pii Vrr[110][110];
bool Tmp[110][110];
int n,m;
int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&Vrr[i][j].fi);
			Vrr[i][j].se=(Vrr[i][j].fi-1)/m+1;
		}
	for(int i=1;i<=m-1;i++){
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				Tmp[j][k]=false;
		for(int j=1;j<=n;j++)
			for(int k=i;k<=m;k++)
				Tmp[j][Vrr[j][k].se]=true;
		Flow::Init(2*n+2);
		int tot=2*n;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(Tmp[j][k])Flow::Insert(j,k+n,1,0);//行->颜色
		for(int j=1;j<=n;j++)
			Flow::Insert(tot+1,j,1,0);
		for(int j=1;j<=n;j++)
			Flow::Insert(j+n,tot+2,1,0);
		Flow::Dinic(tot+1,tot+2);
		for(int j=1;j<=n;j++){
			for(int k=Flow::La[j];k!=-1;k=Flow::Ne[k])
				if(Flow::To[k]<=2*n&&Flow::Fl[k]==0){
					for(int t=i;t<=m;t++){
						if(Vrr[j][t].second+n==Flow::To[k]){
							std::swap(Vrr[j][t],Vrr[j][i]);
							break;
						}
					}
					break;
				}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",Vrr[i][j].first);
		}
		puts("");
	}
	for(int i=1;i<=m;i++){//调整列
		for(int j=1;j<n;j++){
			for(int k=j+1;k<=n;k++){
				if(Vrr[j][i].first>Vrr[k][i].first)
					std::swap(Vrr[j][i],Vrr[k][i]);
			}
		} 
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			printf("%d ",Vrr[i][j].first);
		}
		puts("");
	}
	return 0;
}