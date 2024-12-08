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

const int Mod=(1e9)+7;
int Pow(int a,int b){
	int r=1%Mod;
	while(b){
		if(b&1){r=1ll*r*a%Mod;}
		a=1ll*a*a%Mod;b>>=1;
	}
	return r;
}
int Inv(int a){return Pow(a,Mod-2);}

int Arr[510000];
void Main(){
	//Def
	int n,k;
	
	//Init
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	int ans1=0,ans2=0;
	for(int i=1;i<=k;i++){
		ans1=(ans1+(ll)ceil((n-k+1)/2.0)*Inv(n-k+1)%Mod*Arr[i]%Mod)%Mod;
		ans2=(ans2+(ll)floor((n-k+1)/2.0)*Inv(n-k+1)%Mod*Arr[i]%Mod)%Mod;
	}
	for(int i=k+1;i<=n;i++){
		ans1=(ans1+(ll)ceil((n-k)/2.0)*Inv(n-k)%Mod*Arr[i]%Mod)%Mod;
		ans2=(ans2+(ll)floor((n-k)/2.0)*Inv(n-k)%Mod*Arr[i]%Mod)%Mod;
	}
	printf("%d %d\n",ans1,ans2);
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		Main();
	}
	return 0;
}