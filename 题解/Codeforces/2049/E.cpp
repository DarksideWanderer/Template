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


namespace Checker{
	int p,n,k;
	int cnt;
	void Init(){
		scanf("%d%d%d",&n,&p,&k);
		cnt=0;
	}
	int Query(int l,int r){
		cnt++;
		if(cnt>=34)puts("Er");
		if(r-l+1<k)return (l<=p&&p<=r);
		else return 1-(l<=p&&p<=r);
	}
	int Check(int t){
		cnt++;
		if(cnt>=34)puts("Er");
		if(t==k)puts("Ac");
		else puts("Wa"),printf("%d %d\n",t,k);
		return 0;
	}
}

int Query(int l,int r){
	#ifdef LOCAL
	return Checker::Query(l,r);
	#endif
	printf("? %d %d\n",l,r);
	fflush(stdout);
	int x;scanf("%d",&x);
	return x;
}
int Check(int t){
	#ifdef LOCAL
	return Checker::Check(t);
	#endif
	printf("! %d\n",t);
	fflush(stdout);
	//int x;scanf("%d",&x);
	return 0;
}

int n;
void Main(int Case){
	#ifdef LOCAL
	Checker::Init();
	n=Checker::n;
	#else
	scanf("%d",&n);
	#endif
	
	int s=Query(1,n/2),l,r;
	if(s==0)l=n/2+1,r=n;
	else l=1,r=n/2;
	
	int m=(l+r)>>1;
	int a=Query(l,m);
	int b=Query(m+1,r);
	if(a!=b){//这说明k大于等于n/2
		if(l==1){
			int L=r+1,R=n;
			while(L<R){
				int M=(L+R)>>1;
				if(Query(l,M)==0)R=M;//Ans
				else L=M+1;
			}
			Check(R);
		}
		else{
			int L=1,R=l-1;
			while(L<R){
				int M=(L+R+1)>>1;
				if(Query(M,r)==0)L=M;
				else R=M-1;
			}
			Check(r-L+1);
		}
	}
	else{//这里边肯定没有1
		while(true){
			m=(l+r)>>1;
			a=Query(l,m);
			if(a==0)break;
			else r=m;
		}
		int L=m+1,R=r;
		while(L<R){
			int M=(L+R)>>1;
			if(Query(l,M)==0)L=M+1;//Ans
			else R=M;
		}
		Check(R-l+1);
	}
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	#endif
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}