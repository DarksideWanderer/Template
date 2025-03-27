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

int n,x,y,Ans[210000];
void Main(int Case){
	scanf("%d%d%d",&n,&x,&y);
	for(int i=y%n+1,now=1;i!=y;i=i%n+1)Ans[i]=(now++)&1;
	Ans[y]=2*(!(n%2==0&&Ans[x]==1));
	for(int i=1;i<=n;i++)printf("%d ",Ans[i]);
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