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

int x;ll m;
void Main(int Case){
	scanf("%d%lld",&x,&m);
	int k=log2(x);int t=(1<<(k+1))-1;
	ll ans=0;
	for(int i=1;i<=t;i++){//y=1~t
		if((x^i)%i==0||(x^i)%x==0){
			if(i<=m)ans++;
		}
	}
	
	if(m>t){
		ll s=m|t;//最大范围
		ll p=s-t;
		ll r=p-1;
		ans+=(r/x)-(t/x);
		for(ll y=p;y<=m;y++){
			if((y^x)%x==0&&y)ans++;
		}
	}
	
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