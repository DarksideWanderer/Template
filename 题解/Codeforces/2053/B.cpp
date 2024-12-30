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

array<int,MaxN>Li,Ri;
array<int,MaxN*2>T,S;
array<int,MaxN>Ans;

void Main(int Case){
	int n;
	
	scanf("%d",&n);
	
	for(int i=1;i<=2*n;i++)
		T[i]=0,S[i]=0;
	
	for(int i=1;i<=n;i++){
		scanf("%d%d",&Li[i],&Ri[i]);
		if(Li[i]==Ri[i])T[Li[i]]=1,S[Li[i]]++;
	}
	for(int i=1;i<=2*n;i++)
		T[i]+=T[i-1];
	for(int i=1;i<=n;i++){
		if(Li[i]==Ri[i]){
			if(S[Li[i]]==1)Ans[i]=true;
			else Ans[i]=false;
		}
		else{
			int t=Ri[i]-Li[i]+1;
			if(T[Ri[i]]-T[Li[i]-1]==t)Ans[i]=false;
			else Ans[i]=true;
		}
	}
	for(int i=1;i<=n;i++)
		putchar(Ans[i]+'0');
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