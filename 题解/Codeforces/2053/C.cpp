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

ll n,k;

void Main(int Case){
	scanf("%lld%lld",&n,&k);
	
	std::function<pair<ll,ll>(ll,ll)>Dfs=[&](ll l,ll r){
		if(r-l+1<k)return pair<ll,ll>{0,0};
		else{
			ll ans=0,m=(l+r)/2;
			if((r-l+1)&1){
				ans+=m;
				auto [x,y]=Dfs(l,m-1);
				ans+=2*x+(m-l+1)*y;
				return pair<ll,ll>{ans,y*2+1};
			}
			else{
				auto [x,y]=Dfs(l,m);
				ans+=2*x+(m-l+1)*y;
				return pair<ll,ll>{ans,y*2};
			}
		}
		return pair<ll,ll>{0,0};
	};
	
	printf("%lld\n",Dfs(1,n).fi);
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