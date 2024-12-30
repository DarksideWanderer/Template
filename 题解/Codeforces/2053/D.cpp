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
const ll Mod=998244353;

ll Pow(ll a,ll b){
	ll r=1;
	while(b){
		if(b&1){r=r*a%Mod;}
		a=a*a%Mod;b>>=1;
	}
	return r;
}
ll Inv(ll a){return Pow(a,Mod-2);}

int n,q;

int Sa[MaxN],Sb[MaxN],Arr[MaxN],Brr[MaxN];

void Main(int Case){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%lld",&Arr[i]),Sa[i]=Arr[i];
	for(int i=1;i<=n;i++)
		scanf("%lld",&Brr[i]),Sb[i]=Brr[i];
	std::sort(Sa+1,Sa+n+1);
	std::sort(Sb+1,Sb+n+1);
	ll ans=1;
	for(int i=1;i<=n;i++){
		ans=ans*std::min(Sa[i],Sb[i])%Mod;
	}
	printf("%lld",ans);
	for(int i=1;i<=q;i++){
		int o;scanf("%d",&o);
		int p;scanf("%d",&p);
		if(o==1){//改a
			int t=std::upper_bound(Sa+1,Sa+n+1,Arr[p])-Sa-1;
			ans=ans*Inv(std::min(Sa[t],Sb[t]))%Mod;
			Arr[p]++;
			Sa[t]++;
			ans=ans*std::min(Sa[t],Sb[t])%Mod;
		}
		else{
			int t=std::upper_bound(Sb+1,Sb+n+1,Brr[p])-Sb-1;
			ans=ans*Inv(std::min(Sa[t],Sb[t]))%Mod;
			Brr[p]++;
			Sb[t]++;
			ans=ans*std::min(Sa[t],Sb[t])%Mod;
		}
		printf(" %lld",ans);
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