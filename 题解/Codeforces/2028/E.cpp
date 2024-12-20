#include<bits/stdc++.h>
// #define Debug
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

const int MaxN=210000;
const int Inf=1e9;
const int Mod=998244353;

int Pow(int a,int b){
	int r=1;
	while(b){
		if(b&1){r=1ll*r*a%Mod;}
		a=1ll*a*a%Mod;b>>=1;
	}
	return r;
}
int Inv(int a){
	return Pow(a,Mod-2);
}

vector<int>To[MaxN];

int n;
void Main(int Case){
	vector<int>Mi;
	vector<int>Dp;
	
	scanf("%d",&n);
	
	Mi.resize(n+10);
	Dp.resize(n+10);
	for(int i=1;i<=n;i++)
		Clear(To[i]);
	
	for(int i=1;i<=n-1;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		To[x].push_back(y);
		To[y].push_back(x);
	}
	
	std::function<int(int,int)>Dfs1=[&](int from,int dad){
		Mi[from]=Inf;
		for(auto to:To[from]){
			if(to==dad)continue;
			Mi[from]=std::min(Mi[from],Dfs1(to,from)+1);
		}
		if(Mi[from]==Inf)Mi[from]=1;
		return Mi[from];
	};
	Dfs1(1,0);
	
	#ifdef Debug
	for(int i=1;i<=n;i++)
		printf("%d ",Mi[i]);
	puts("");
	#endif
	
	
	std::function<void(int,int)>Dfs2=[&](int from,int dad){
		
		for(auto to:To[from]){
			if(to==dad)continue;
			int t=Mi[to];
			int A=Dp[from];
			int B=Mod-1ll*A*Inv(t)%Mod;
			Dp[to]=(A+B)%Mod;
			Dfs2(to,from);
		}
	};
	Dp[1]=1;
	Dfs2(1,0);
	for(int i=1;i<=n;i++){
		printf("%d ",Dp[i]);
	}
	puts("");
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