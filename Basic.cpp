#include<bits/stdc++.h>
#include<bits/extc++.h>
//DataStruct
template<typename T>
struct ChxSet{
	typedef __gnu_pbds::tree<T,__gnu_pbds::null_type,std::less<T>,__gnu_pbds::rb_tree_tag,__gnu_pbds::tree_order_statistics_node_update> Type;
	Type S;
	void insert(T x){S.insert(x);}
	bool have(T x){return S.find(x)!=S.end();}
	bool erase(T x){return S.erase(x);}
	typename Type::iterator find(T x){return S.find(x);}
	typename Type::iterator erase(typename Type::iterator it){return S.erase(it);}
	int getrank(T x){return S.order_of_key(x);}//返回严格小于 x 的元素个数(以 Cmp_Fn 作为比较逻辑),即从 0 开始的排名
	typename Type::iterator select(int x){return S.find_by_order(x);}//返回 Cmp_Fn 比较的排名所对应元素的迭代器
	typename Type::iterator prev(T x){//<x 严格前驱
		int t=S.order_of_key(x);
		if(t==0)return S.end();
		else return S.find_by_order(x-1);
	}
	typename Type::iterator succ(T x){//>x 严格后继
		return S.upper_bound(x);
	}
	typename Type::iterator lower_bound(T x){return S.lower_bound(x);}
	typename Type::iterator upper_bound(T x){return S.upper_bound(x);}
	typename Type::iterator begin(){return S.begin();}
	typename Type::iterator end(){return S.end();}
	bool empty(){return S.empty();}
	size_t size(){return S.size();}
};
template<typename T>
struct FanwickTree{
	#define lb(x) (x&-x)
	int L,O;
	std::vector<T>V;
	void Init(int _L,int _O=0){O=_O;L=_L;V.resize(_L+10);}
	void Upd(int x,T v){
		x+=O;for(;x<=L;x+=lb(x))V[x]+=v;
	}
	T Qry(int x,T v=0){
		x+=O;for(;x>=1;x-=lb(x))v+=V[x];
		return v;
	}
	#undef lb
};
struct SegmentTrees{
	struct Tags{
		
	};
	struct Datas{
		friend Datas Merge(const Datas&a,const Datas&b){
			return a;
		}
	};
	struct Nodes{
		int ls,rs;
		Tags ts;
		Datas ds;
	};
	std::vector<Nodes>N;int cnt;
	#define ls(t) N[t].ls
	#define rs(t) N[t].rs
	#define ts(t) N[t].ts
	#define ds(t) N[t].ds
	void Init(const int&L){cnt=0;N.resize(L+10);}
	void PushUp(int t){
		N[t].ds=Merge(N[ls(t)].ds,N[rs(t)].ds);
	}
	void PushDown(int t){
		
	}
	void Build(int&t,int L,int R){
		//Init
		if(L==R){
			//Init
			return ;
		}
		int M=(L+R)>>1;
		Build(ls(t),L,M);
		Build(rs(t),M+1,R);
		PushUp(t);
	}
	void ModifyA(int t,int L,int R,int p){
		PushDown(t);
		if(L==R){
			//?
			return ;
		}
		int M=(L+R)>>1;
		if(p<=M)ModifyA(ls(t),L,M,p);
		else ModifyA(rs(t),M+1,R,p);
		PushUp(t);
	}
	void ModifyB(int t,int L,int R,int l,int r){
		PushDown(t);
		if(l<=L&&R<=r){
			//?
			return ;
		}
		int M=(L+R)>>1;
		if(l<=M)ModifyB(ls(t),L,M,l,r);
		if(M+1<=r)ModifyB(rs(t),M+1,R,l,r);
		PushUp(t);
	}
	int QryA(int t,int L,int R,int p){
		PushDown(t);
		if(L==R){
			//return ;
		}
		int M=(L+R)>>1;
		if(p<=M)return QryA(ls(t),L,M,p);
		else return QryA(rs(t),M+1,R,p);
	}
};
//Function
template<typename T>
void Clear(T&x){T y;x.swap(y);}
template<typename... Args>
void Clear(Args&... args){(Clear(args), ...);/*必须加括号*/}
template<typename O,typename...T>
void For_each(O opt,T&...x){(opt(x),...);}
std::default_random_engine E(std::chrono::steady_clock().now().time_since_epoch().count());
template<typename... Args>
std::istream& InPut(Args&...x){return (std::cin>>...>>x);}
bool g_AddEndl=false;
template<typename... Args>
std::ostream& OutPut(const Args&... x) {
	(std::cout<<...<<x);
	if(g_AddEndl){std::cout<<std::endl;}
	return std::cout;
}
template<typename...Args>
std::ostream& ErrPut(const Args&...x){return (std::cerr<<...<<x);}
void Flush(){std::cout.flush();}
//Math
const int Mod=998244353;
std::vector<int>F,IF,I;
int A(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
int M(int a,int b){return 1ll*a*b%Mod;}
int Pow(int a,int b){
	int r=1;
	while(b){
		if(b&1){r=M(r,a);}
		a=M(a,a);b>>=1;
	}
	return r;
}
int Inv(int a){return Pow(a,Mod-2);}
void Init(const int&L){
	F.resize(L+1),I.resize(L+1),IF.resize(L+1);
	F[0]=1;
	for(int i=1;i<=L;i++)F[i]=M(i,F[i-1]);
	IF[L]=Inv(F[L]);
	for(int i=L-1;i>=0;i--)IF[i]=M(IF[i+1],i+1);
	for(int i=1;i<=L;i++)I[i]=M(IF[i],F[i-1]);
}
int CalcC(int n,int m){
	if(m<0||m>n)return 0;
	return M(M(F[n],IF[m]),IF[n-m]);
}
int CalcCat(int n){return M(CalcC(2*n,n),I[n+1]);}

//Interactor
namespace Wql{
	bool g_Builtin_Interactor=false;
	void Init(){
		if(g_Builtin_Interactor){
			ErrPut("交互库输入开始----------------------------------");
			ErrPut("交互库输入结束----------------------------------");
		}
		else{
			
		}
	}
	auto Qry1(){
		if(g_Builtin_Interactor){
			
		}
		else{
			
		}
	}
	auto End(){
		if(g_Builtin_Interactor){
			
		}
		else{
			
		}
	}
}

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

void Main(int Case,bool flag=false){
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
//	freopen("Err.txt","w",stderr);
	#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);std::cout.tie(nullptr);
	int Task=1;cin>>Task;
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}