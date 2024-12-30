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


void Main(int Case){
	int n;
	vector<int>Arr;
	
	scanf("%d",&n);
	Arr.resize(n+10);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	bool flag=false;
	for(int i=1;i<n;i++){
		int a=std::min(Arr[i],Arr[i+1]);
		int b=Arr[i]+Arr[i+1]-a;
		if(a*2>b){
			flag=true;
		}
	}
	if(flag)puts("Yes");
	else puts("No");
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