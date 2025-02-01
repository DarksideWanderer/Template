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
template<typename O,typename T>
void For_each(O opt,T&x){opt(x);}
template<typename O,typename...T>
void For_each(O opt,T&...x){
	(opt(x),...);
}
template<typename T>
void DebugP(T x){
	std::cout<<x<<'\n';
	fflush(stdout);
}
template<typename...Args>
void DebugP(Args...x){(DebugP(x),...);}
std::default_random_engine E(std::chrono::steady_clock().now().time_since_epoch().count());


using std::cin;
using std::cout;
void Main(int Case,bool flag=false){
	int n;cin>>n;
	
	vector<vector<int>>To(n+10);
	
	vector<ll>Li(n+10),Ri(n+10);
	
	for(int i=1;i<=n;i++)
		cin>>Li[i]>>Ri[i];
	for(int i=1;i<=n-1;i++){
		int x,y;cin>>x>>y;
		To[x].push_back(y);
		To[y].push_back(x);
	}
	vector<ll>Dp(n+10);
	ll ans=0;
	std::function<void(int,int)>Dfs=[&](int from,int dad){
		ll tmp=Li[from];
		for(int to:To[from]){
			if(to==dad)continue;
			Dfs(to,from);
			tmp=std::max(tmp,Dp[to]);
		}
		if(tmp>=Ri[from])tmp=Ri[from];
		for(int to:To[from]){
			if(tmp<=Dp[to])ans+=Dp[to]-tmp;
		}
		Dp[from]=tmp;
	};
	Dfs(1,0);
	cout<<ans+Dp[1]<<'\n';
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int Task=1;cin>>Task;
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}