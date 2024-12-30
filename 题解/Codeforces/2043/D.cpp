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
std::default_random_engine E(std::chrono::steady_clock().now().time_since_epoch().count());

ll Gcd(ll a,ll b){
	return a==0||b==0?a+b:Gcd(b,a%b);
}
ll l,r,g;
void Main(int Case){
	scanf("%lld %lld %lld",&l,&r,&g);
	ll lt=(l+g-1)/g;
	ll rt=r/g;
	ll ansj=-1,ansi=-1;
	for(ll i=rt-lt+1;i;i--){
		for(ll j=lt;j+i-1<=rt;j++){
			if(Gcd(j,j+i-1)==1){
				printf("%lld %lld\n",j*g,g*(j+i-1));
				return ;
			}
		}
	}
	puts("-1 -1");
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