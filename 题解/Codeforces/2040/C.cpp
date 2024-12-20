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

ll n,k;
void Main(int Case){
	scanf("%lld %lld",&n,&k);k--;
	
	if(n==1){
		if(k==0)puts("1");
		else puts("-1");
		return ;
	}
	
	ll now=1;
	bool flag=false;
	for(int i=1;i<=n-1;i++){
		now<<=1;
		if(now>k){
			flag=true;
			break;
		}
	}
	if(!flag){
		puts("-1");
		return ;
	}
	std::list<int>L;L.push_back(n);
	for(ll i=0;i<=std::min(60ll,n-2);i++){
		if((k>>i)&1)L.push_back(n-i-1);
		else L.push_front(n-i-1);
	}
	for(ll i=std::min(60ll,n-2)+1;i<=n-2;i++)
		L.push_front(n-i-1);
	for(auto x:L)printf("%d ",x);
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