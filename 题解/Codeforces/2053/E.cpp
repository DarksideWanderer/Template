#include<bits/stdc++.h>
//#define Debug
using std::vector;
using std::set;
using std::array;
using std::pair;
#define fi first
#define se second
#define ll long long
#define pii pair<int,int>
template<typename T>
void Clear(T&x){T y;x.swap(y);}
template<typename... Args>
void Clear(Args&... args){
    (Clear(args), ...);//必须加括号
}
std::default_random_engine E(std::chrono::steady_clock().now().time_since_epoch().count());

const int MaxN=210000;
const int Inf=1e9;

vector<int>To[MaxN];
int Deg[MaxN];
bool Vis[MaxN];
int Dist[MaxN];
ll Dp1[MaxN],Dp2[MaxN];

//1: p 到不了叶子 Dist[p]>1
//2: 向根节点一步有叶子,且本身不是叶子

int n;
void Main(int Case){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		Clear(To[i]),Deg[i]=0;
	
	for(int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		To[x].push_back(y);Deg[x]++;
		To[y].push_back(x);Deg[y]++;
	}
	
	for(int i=1;i<=n;i++){
		Vis[i]=false;
		Dist[i]=Inf;
	}
	
	ll ans=0,tmp=0;
	std::queue<int>Q;
	for(int i=1;i<=n;i++){
		if(Deg[i]==1){
			Q.push(i);
			Dist[i]=0;
			tmp++;
		}
	}
	ans+=(tmp)*(n-tmp);
	while(!Q.empty()){
		int from=Q.front();Q.pop();
		for(int to:To[from]){
			Dist[to]=std::min(Dist[to],Dist[from]+1);
			if(!Vis[to]){
				Vis[to]=true;
				Q.push(to);
			}
		}
	}
	
//	for(int i=1;i<=n;i++)
//		printf("%d\n",Dist[i]);
	
	std::function<void(int,int)>Dfs=[&](int from,int dad){
		int son=0;
		for(int to:To[from]){
			if(to==dad)continue;
			son++;
			Dfs(to,from);
		}
		if(son==0){
			Dp1[from]=0;
			Dp2[from]=0;
			return ;
		}
		Dp1[from]=Dp2[from]=0;
		for(int to:To[from]){
			if(to==dad)continue;
			if(Dist[to]==1&&Dist[from]!=0)
				ans=ans+Dp2[to];
			Dp2[from]+=Dp2[to];
		}
		if(from==2){
			from++;
			from--;
		}
		for(int to:To[from]){//子树交叉
			if(to==dad)continue;
			ans=(ans+(Dp2[from]-Dp2[to])*Dp1[to])+(Dist[to]!=0&&Dist[from]==1)*(Dp2[from]-Dp2[to]);
			Dp1[from]+=(Dist[to]!=0&&Dist[from]==1)+Dp1[to];
		}
		if(Dist[from]>1){
			Dp2[from]++;
			ans+=Dp1[from];
		}
	};
	Dfs(1,0);
	
	
//	for(int i=1;i<=n;i++)
//		printf("%d:%d %lld %lld\n",i,Dist[i],Dp1[i],Dp2[i]);
	
	printf("%lld\n",ans);
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}