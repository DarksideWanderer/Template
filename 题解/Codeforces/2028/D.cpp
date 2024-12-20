#include<bits/stdc++.h>
//#define Debug
using std::vector;
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

std::set<pii>S[3];

const char Pc[3]={'q','k','j'};
const int MaxN=210000;
int P[MaxN][3];
int Ans[MaxN];
int Vis[MaxN];
int n;

void Main(int Case){
	scanf("%d",&n);
	
	for(int i=0;i<=2;i++)
		S[i].clear();
	for(int i=0;i<=2;i++){
		for(int j=1;j<=n;j++){
			int x;scanf("%d",&x);
			P[j][i]=x;
			S[i].insert({x,j});
		}
	}
	for(int i=1;i<=n;i++)
		Vis[i]=false;
	
	Vis[1]=true;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=2;j++)
			S[j].erase({P[i][j],i});
		if(!Vis[i]){
			continue;
		}
		for(int j=0;j<=2;j++){
			for(auto it=S[j].begin();it!=S[j].end();){
				if((*it).first>P[i][j])break;
				Vis[(*it).second]=i;
				Ans[(*it).second]=j;
				it=S[j].erase(it);
			}
		}
	}
	if(!Vis[n]){
		puts("No");
		return;
	}
	puts("Yes");
	vector<pii>An;
	int now=n;
	while(now!=1){
		An.push_back({Ans[now],now});
		now=Vis[now];
	}
	printf("%ld\n",An.size());
	std::reverse(An.begin(),An.end());
	for(auto [x,y]:An)
		printf("%c %d\n",Pc[x],y);
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