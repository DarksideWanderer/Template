#include<bits/stdc++.h>
//#define Debug
using std::vector;
using std::set;
using std::array;
using std::pair;
using std::cin;
using std::cout;
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

const ll Inf=1e18;

ll Arr[210][420];
ll Sum[210][420];
ll Dp[210][210];
ll Pr[210][210];
ll G[210];
int n,m;ll K;
void Main(int Case){
	cin>>n>>m>>K;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>Arr[i][j];
			Arr[i][j+m]=Arr[i][j];
		}
		for(int j=1;j<=2*m;j++)
			Sum[i][j]=Sum[i][j-1]+Arr[i][j];
	}
	for(int i=0;i<=n;i++)
		for(int j=1;j<=m;j++)
			Dp[i][j]=Inf;
	Dp[0][1]=0;
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			G[j]=Dp[i-1][j];
		//前后缀维护
		for(int k=1;k<=m;k++){//长度
			for(int j=m;j>=1;j--){
				if(j!=m)Pr[j][k]=std::min(Pr[j+1][k]+K,Sum[i][j+k-1]-Sum[i][j-1]);
				else Pr[j][k]=Sum[i][j+k-1]-Sum[i][j-1];
			}
		}
		for(int k=1;k<=m;k++){
			ll mi=Inf;
			for(int j=1;j<=m;j++)
				mi=std::min(K*j+Sum[i][j+k-1]-Sum[i][j-1],mi);
			for(int j=m;j>=1;j--)
				Pr[j][k]=std::min(Pr[j][k],mi),mi+=K;
		}
		for(int j=1;j<=m;j++){
			for(int k=1;j+k-1<=m;k++){
				Dp[i][j+k-1]=std::min(Dp[i][j+k-1],G[j]+Pr[j][k]);
			}
		}
		// for(int j=1;j<=m;j++)
		// 	printf("%lld ",Dp[i][j]);
		// puts("");
	}
	printf("%lld\n",Dp[n][m]);
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