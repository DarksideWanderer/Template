基础板

```cpp
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
std::uniform_int_distribution<int>U(Down,Up);
int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		
	}
	return 0;
}
```

图论基础板

```cpp
const int MaxN=1000;
const int MaxM=1000;
namespace A{
	int cnt;
	int tot;
	int Last[MaxN];
	int To[MaxM],Next[MaxM];
	void Insert(int from,int to){
		To[cnt]=to;
		Next[cnt]=Last[from];Last[from]=cnt++;
	}
	typedef int flowtype;
	typedef int costtype;
	flowtype Flow[MaxM];
	costtype Cost[MaxM];
	void Insert(int from,int to,flowtype flow1,costtype cost1,flowtype flow2,costtype cost2){//加权图
		To[cnt]=to;Flow[cnt]=flow1;Cost[cnt]=cost1;
		Next[cnt]=Last[from];Last[from]=cnt++;
		To[cnt]=from;Flow[cnt]=flow2;Cost[cnt]=cost2;
		Next[cnt]=Last[to];Last[to]=cnt++;
	}
	//k^1 反向边
}
namespace B{
	int cnt;//总边数
	int tot;//总点数
	struct Edges{
		int to,nxt;
	};Edges Ei[MaxM];
	int Last[MaxN];
	void Insert(int from,int to){
		Ei[cnt]={to,Last[from]};
		Last[from]=cnt++;
	}
}
namespace C{
	int tot;
	struct Edges{
		int to;
	};
	std::vector<Edges>Ei[MaxN];
	void Insert(int from,int to){
		Ei[from].push_back({to});
	}
}
//比较重要的初始化
namespace A{
	void Init(){
		cnt=0;
		//任意实现将Last复制为-1
		//std::fill(Last+1,Last+tot+1,-1);
	}
}
namespace C{
	void Init(){
		//std::fill(Ei+1,Ei+tot+1,...);
	}
}
```

数学基础板

```cpp
#include<bits/stdc++.h>

const int Mod=998244353;

int Sb(int&x,int y){
	x-=y;if(x<0)x+=Mod;
	return x;
}
int Ad(int&x,int y){
	x+=y;if(x>=Mod)x-=Mod;
	return x;
}
int Ml(int&x,int y){
	x=1ll*x*y%Mod;
	return x;
}
int Sub(int x,int y){return Sb(x,y);}
int Add(int x,int y){return Ad(x,y);}
int Mul(int x,int y){return Ml(x,y);}
int Pow(int x,int n,int p=Mod){
	int r=1;
	while(n){
		if(n&1){Ml(r,x);}
		Ml(x,x);n>>=1;
	}
	return r;
}
int Inv(int x){return Pow(x,Mod-2);}

const int MaxN=100;
int Fa[MaxN],If[MaxN],Iv[MaxN];
int CalcC(int x,int y){
	if(y<0||y>x)return 0;
	return Mul(Mul(Fa[x],If[y]),If[x-y]);
}
int Gcd(int a,int b){
	return (!a||!b)?a+b:Gcd(b,a%b);
}
void ExGcd(int a,int b,int &x,int &y){//ax+by=gcd(a,b),(a,b\not=0)
	if(b==0){x=1;return ;}
	ExGcd(b,a%b,y,x);y-=(a/b)*x;
}
int Lucas(int x,int y){
	if(y<0||y>x)return 0;
	if(y==0)return 1;
	return Mul(CalcC(x%Mod,y%Mod),Lucas(x/Mod,y/Mod));
}
//CalcC可以分段打表
int main(){
	const int L=100;
	Fa[0]=1;
	for(int i=1;i<=L;i++)Fa[i]=Mul(Fa[i-1],i);
	If[L]=Pow(Fa[L],Mod-2);
	for(int i=L-1;i>=0;i--)If[i]=Mul(If[i+1],i+1);
	for(int i=1;i<=L;i++)Iv[i]=Mul(If[i],Fa[i-1]);
	
	return 0;
}
```

Dijkstra

```cpp
#include<bits/stdc++.h>
#define ll long long
#define plli std::pair<ll,int>

namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
	template<typename T>
	T Min(T x,T y){return(x<y?x:y);}
	template<typename T>
	T Max(T x,T y){return(x>y?x:y);}
}
using namespace Wql;

namespace Dijkstra{
	const int MaxN=1e6+1e5;
	const int MaxM=1e6+1e5;
	int Last[MaxN];int tot;
	int Next[MaxM],To[MaxM];
	ll Cost[MaxM];
	void Insert(int from,int to,ll cost){
		To[tot]=to;Cost[tot]=cost;
		Next[tot]=Last[from];Last[from]=tot++;
	}
	bool Vis[MaxN];
	ll Dist[MaxN];
	std::priority_queue<plli>Q;
	void Init(){
		tot=0;
		memset(Last,-1,sizeof(Last));
	}
	void Dijkstra(int surc){
		Clear(Q);
		memset(Vis,false,sizeof(Vis));
		memset(Dist,0x3f,sizeof(Dist));
		Dist[surc]=0;
		Q.push((plli){0,surc});
		while(!Q.empty()){
			int from=Q.top().second;Q.pop();
			if(Vis[from])continue;
			Vis[from]=true;
			for(int k=Last[from];k!=-1;k=Next[k]){
				Dist[To[k]]=Min(Dist[To[k]],Dist[from]+Cost[k]);
				Q.push((plli){-Dist[To[k]],To[k]});
			}
		}
	}
}
int n,m,st;
int main(){
	scanf("%d %d %d",&n,&m,&st);
	Dijkstra::Init();
	for(int i=1;i<=m;i++){
		int x,y;ll c;
		scanf("%d %d %lld",&x,&y,&c);
		Dijkstra::Insert(x,y,c);
	}
	Dijkstra::Dijkstra(st);
	for(int i=1;i<=n;i++)
		printf("%lld ",Dijkstra::Dist[i]);
	#ifndef ONLINEJUDGE
	std::system("pause");
	#endif
	return 0;
}
```

马拉车算法

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MaxN=31000000;
char St[MaxN],Tmp[MaxN];
int Res[MaxN],n,len;

int main(){
	scanf("%s",St+1);n=strlen(St+1);
	Tmp[++len]='?';
	for(int i=1;i<=n;i++){
		Tmp[++len]='#';
		Tmp[++len]=St[i];
	}
	Tmp[++len]='#';
	Tmp[++len]='&';
	int mid=1,ans=0;
	Res[1]=0;
	for(int i=2;i<=len-2;i++){
		int right=mid+Res[mid];
		if(i<=right)
			Res[i]=min(i+Res[2*mid-i],right)-i;
		while(Tmp[i-Res[i]-1]==Tmp[i+Res[i]+1])
			++Res[i];
		if(i+Res[i]>=mid)mid=i;
		ans=max(ans,Res[i]);
	}
	printf("%d\n",ans);
	return 0;
}
```

原根(原理未知)

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MaxN=1100000;

int Phi[MaxN],Prime[MaxN],tot;
bool NotPrime[MaxN],Root[MaxN];
inline void Init(const int&limit){
	Phi[1]=1;
	for(int i=2;i<=limit;i++){
		if(!NotPrime[i]){
			Prime[++tot]=i;
			Phi[i]=i-1;
		}
		for(int j=1;j<=tot;j++){
			if(i*Prime[j]>limit)break;
			NotPrime[i*Prime[j]]=true;
			if(i%Prime[j]==0){
				Phi[i*Prime[j]]=Prime[j]*Phi[i];
				break;
			}
			Phi[i*Prime[j]]=Phi[i]*Phi[Prime[j]];
		}
	}
	Root[2]=Root[4]=true;
	for(int i=2;i<=tot;i++){
		for(int j=1;(1ll*j*Prime[i])<=limit;j*=Prime[i])Root[j*Prime[i]]=true;
		for(int j=2;(1ll*j*Prime[i])<=limit;j*=Prime[i])Root[j*Prime[i]]=true;
	}
}
inline int Gcd(int a,int b){return(b==0?a:Gcd(b,a%b));}
inline int GetPow(int x,int n,int Mod){
	int r=1;x=x%Mod;
	while(n){
		if(n&1)r=1ll*r*x%Mod;
		x=1ll*x*x%Mod;n>>=1;
	}
	return r;
}
int Fac[MaxN],cnt;
inline void GetFac(int x){
	for(int i=2;i*i<=x;i++){
		if(x%i==0){
			Fac[++cnt]=i;
			while(x%i==0){x/=i;}
		}
	}
	if(x>1)Fac[++cnt]=x;
}

inline bool Check(int x,int Mod){
	if(GetPow(x,Phi[Mod],Mod)!=1)return false;
	for(int i=1;i<=cnt;i++)
		if(GetPow(x,Phi[Mod]/Fac[i],Mod)==1)return false;
	return true;
}

inline int MinRoot(int Mod){
	for(int i=1;i<Mod;i++){
		if(Check(i,Mod))return i;
	}
	return 0;
}
int Ans[MaxN],cans;
inline void GetRoot(int Mod,int x){
	int now=1;
	for(int i=1;i<=Phi[Mod];i++){
		now=(1ll*now*x)%Mod;
		if(Gcd(i,Phi[Mod])==1)Ans[++cans]=now;
	}
}

int main(){
	Init(1000000);
	int Task;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		int wtf,x;scanf("%d%d",&x,&wtf);
		if(Root[x]){
			cans=cnt=0;
			GetFac(Phi[x]);
			int mn=MinRoot(x);
			GetRoot(x,mn);
			sort(Ans+1,Ans+cans+1);
			printf("%d\n",cans);
			for(int i=1;i<=cans/wtf;i++)
				printf("%d ",Ans[i*wtf]);
			puts("");
		}
		else{
			printf("%d\n",0);
			puts("");
		}
	}
	return 0;
}
```

Pollard-Rho

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<random>
using namespace std;

const __int128 One=1;

default_random_engine rnd(20051219u);

inline long long GetGcd(long long a,long long b){return b==0?a:GetGcd(b,a%b);}

inline long long GetPow(long long x,long long n,long long Mod){
	long long r=1%Mod;x=x%Mod;
	while(n){
		if(n&1)r=One*r*x%Mod;
		x=One*x*x%Mod;n>>=1;
	}
	return r;
}

inline bool MR(long long x,long long a){
	long long k=x-1,t=0;
	while(k%2==0)k>>=1,t++;
	long long v=GetPow(a,k,x);
	if(v==1||v==x-1)return true;
	for(int i=1;i<=t;i++){
		v=One*v*v%x;
		if(v==x-1)
			if(i==t)return false;
			else return true;
		else if(v==1)return false;
	}
	return false;
}

long long Prime[]={2,13,61};
inline bool IsPrime(long long x){
	if(x<3||x%2==0)return x==2;
	for(auto a:Prime)
		if(x==a)return true;
	for(auto a:Prime)
		if(!MR(x,a))return false;
	return true;
}

inline long long PR(long long x){
	long long a,b,c,v,g;
	int i,j;
	while(true){
		a=b=rnd()%(x-1)+1;c=rnd()%(x-1)+1;
		v=1;
		i=0;j=1;
		while(++i){
			a=(One*a*a+c)%x;
			v=One*v*abs(a-b)%x;
			if(a==b||!v)break;
			if(!(i%63)||i==j){
				g=GetGcd(v,x);
				if(g>1)return g;
				if(i==j)b=a,j<<=1;
			}
		}
	}
}
long long maxi;
inline void Solve(long long x){
	if(x<=maxi||x<2)return ;
	if(IsPrime(x)){
		maxi=x;
		return ;
	}
	long long p=PR(x);
	while(x%p==0)x/=p;
	Solve(x),Solve(p);
}
long long n;
int main(){
	int Task;scanf("%d",&Task);
	while(Task--){
		scanf("%lld",&n);
		if(IsPrime(n))puts("Prime");
		else maxi=1,Solve(n),printf("%lld\n",maxi);
	}
	return 0;
}
```

Bellman_Ford

```cpp
#include<bits/stdc++.h>
#define ll long long
#define plli std::pair<ll,int>

const ll Inf=1e17;

namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
	template<typename T>
	T Min(T x,T y){return(x<y?x:y);}
	template<typename T>
	T Max(T x,T y){return(x>y?x:y);}
}
using namespace Wql;

namespace BellmanFord{
	using std::vector;
	int nv,ne,tot;
	vector<int>Last,Next,To;
	vector<ll>Cost;
	void Init(int nnv,int nne){
		nv=nnv;ne=nne;tot=0;
		Last=vector<int>(nv+1,-1);
		Next=vector<int>(ne+1,0);
		To=vector<int>(ne+1,0);
		Cost=vector<ll>(ne+1,0);
	}
	void Insert(int from,int to,ll cost){
		To[tot]=to;Cost[tot]=cost;
		Next[tot]=Last[from];Last[from]=tot++;
	}
	vector<ll>Dist;
	bool BellmanFord(int surc){
		Dist=vector<ll>(nv+1,Inf);
		Dist[surc]=0;
		for(int i=1;i<=nv;i++){
			bool flag=false;
			for(int from=1;from<=nv;from++)
				if(Dist[from]!=Inf)
					for(int k=Last[from];k!=-1;k=Next[k])
						if(Dist[To[k]]>Dist[from]+Cost[k])
							Dist[To[k]]=Dist[from]+Cost[k],flag=true;
			if(!flag)return false;
		}
		return true;
	}
}
#define BF BellmanFord

int n,m,st;
int main(){
	
	int Task;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		scanf("%d%d",&n,&m);
		BF::Init(n,2*m);
		for(int i=1;i<=m;i++){
			int x,y,c;scanf("%d%d%d",&x,&y,&c);
			if(c<0)BF::Insert(x,y,c);
			else BF::Insert(x,y,c),BF::Insert(y,x,c);
		}
		bool flag=BF::BellmanFord(1);//注意可能不连通
		if(flag)puts("YES");
		else puts("NO");
	}
	
	#ifndef ONLINEJUDGE
	std::system("pause");
	#endif
	return 0;
}
```

线性基

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct LinearBases{
	long long Data[51];
	inline bool Insert(long long x){
		for(int i=50;i>=0;i--)
			if((x>>i)&1){
				if(!Data[i]){Data[i]=x;return true;}
				else x^=Data[i];
			}
		return false;
	}
	inline long long Query(){
		long long now=0;
		for(int i=50;i>=0;i--)
			if((now^Data[i])>now)
				now=now^Data[i];
		return now;
	}
};LinearBases LB;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		long long x;scanf("%lld",&x);
		LB.Insert(x);
	}
	printf("%lld\n",LB.Query());
	return 0;
}
```

分治fft

```cpp
#include<bits/stdc++.h>
using std::vector;
using std::pair;
#define pii pair<int,int>
#define ll long long
#define fi first
#define se second
const int Mod=998244353;
const int p=3,ip=332748118;
int Pow(int a,int b){
	int r=1;
	while(b){
		if(b&1){r=1ll*r*a%Mod;}
		a=1ll*a*a%Mod;b>>=1;
	}
	return r;
}
const int MaxN=210000;
namespace NTT{
	int Rev[MaxN];
	int P[30],IP[30];
	void Init(int lim){
		for(int i=1,t=1;i<lim;i<<=1,t++){
			P[t]=Pow(p,(Mod-1)/(i<<1));
			IP[t]=Pow(P[t],Mod-2);
		}
	}
	void InitRev(int lim,int len){//0~lim-1
		for(int i=1;i<lim;i++)
			Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(len-1));
	}
	void NTT(int *Arr,int lim,bool flag=false){
		for(int i=1;i<lim;i++)
			if(i<Rev[i])std::swap(Arr[i],Arr[Rev[i]]);
		for(int i=1,t=1;i<lim;i<<=1,t++){
			int T=!flag?P[t]:IP[t];
			for(int j=0;j<lim;j+=(i<<1)){
				for(int k=0,W=1;k<i;k++,W=1ll*W*T%Mod){
					int x=Arr[j+k],y=1ll*W*Arr[j+k+i]%Mod;
					Arr[j+k]=(x+y)%Mod;
					Arr[j+k+i]=(x-y+Mod)%Mod;
				}
			}
		}
		if(!flag)return ;
		int I=Pow(lim,Mod-2);
		for(int i=0;i<lim;i++)Arr[i]=1ll*Arr[i]*I%Mod;
	}
}
int Fi[MaxN],Gi[MaxN],Ai[MaxN],Bi[MaxN];
void Cdq(int Left,int Right,int len){
	if(Left==Right)return ;
	int Mid=(Left+Right)>>1;
	Cdq(Left,Mid,len-1);
	int lim=(1<<len);
	NTT::InitRev(lim,len);
	std::copy(Fi+Left,Fi+Mid+1,Ai);
	std::fill(Ai+Mid-Left+1,Ai+lim,0);
	std::copy(Gi,Gi+Right-Left+1,Bi);
	std::fill(Bi+Right-Left+1,Bi+lim,0);
	NTT::NTT(Ai,lim);NTT::NTT(Bi,lim);
	for(int i=0;i<lim;i++)Ai[i]=1ll*Ai[i]*Bi[i]%Mod;
	NTT::NTT(Ai,lim,true);
	for(int i=Mid+1;i<=Right;i++)Fi[i]=(Fi[i]+Ai[i-Left])%Mod;
	Cdq(Mid+1,Right,len-1);
}
int n;
int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	scanf("%d",&n);
	for(int i=1;i<=n-1;i++)
		scanf("%d",&Gi[i]);
	Fi[0]=1;
	int len=0,lim=1;
	while(lim<=n-1)lim<<=1,len++;
	NTT::Init(lim);
	Cdq(0,lim-1,len);
	for(int i=0;i<=n-1;i++)
		printf("%d ",Fi[i]);
	return 0;
}
```

```cpp
#include<cstdio>
#include<cstring>
#include<bitset>
using namespace std;
const int MaxN=11000;
const int MaxM=21000;
const int MaxQ=110;
const int MaxK=11000000;
template<typename datatype>
inline datatype Max(const datatype&x,const datatype&y){return(x>y?x:y);}
template<typename datatype>
inline datatype Min(const datatype&x,const datatype&y){return(x<y?x:y);}
int Last[MaxN];int cnt;
int Next[MaxM],To[MaxM];
int Cost[MaxM];
inline void Insert(int from,int to,int cost){
	To[cnt]=to;Cost[cnt]=cost;
	Next[cnt]=Last[from];Last[from]=cnt++;
}
int Size[MaxN],Maxi[MaxN],root,sum;
bool Visit[MaxN];
inline void CalcRoot(int from,int dad){//得到Size,找到重心 
	Size[from]=1;Maxi[from]=0;
	for(int k=Last[from];k!=-1;k=Next[k]){
		if(To[k]==dad||Visit[To[k]])continue;
		CalcRoot(To[k],from);
		Size[from]+=Size[To[k]];
		Maxi[from]=Max(Maxi[from],Size[To[k]]);
	}
	Maxi[from]=Max(Maxi[from],sum-Size[from]);
	if(Maxi[from]<Maxi[root])root=from;
}
int Tmp[MaxN],Dist[MaxN],maxk;
inline void CalcDist(int from,int dad){
	//收集子树中的信息,思考过程可以发现是不重不漏的 
	if(Dist[from]<=maxk)Tmp[++Tmp[0]]=Dist[from];
	for(int k=Last[from];k!=-1;k=Next[k]){
		if(To[k]==dad||Visit[To[k]])continue;
		Dist[To[k]]=Dist[from]+Cost[k];
		CalcDist(To[k],from);
	}
}
int Sta[MaxN];
int q,Query[MaxQ];
bool Ans[MaxQ];
bitset<MaxK>Test;
inline void CalcAns(int from){
	//统计一手答案
	static int top;top=0;
	for(int k=Last[from];k!=-1;k=Next[k]){
		if(Visit[To[k]])continue;
		Dist[To[k]]=Cost[k];
		Tmp[0]=0;CalcDist(To[k],from);
		for(int i=1;i<=Tmp[0];i++)
			for(int j=1;j<=q;j++)
				if(Query[j]>=Tmp[i])Ans[j]|=Test[Query[j]-Tmp[i]];
		for(int i=1;i<=Tmp[0];i++)
			Sta[++top]=Tmp[i],Test[Tmp[i]]=true;
	}
	for(int i=1;i<=top;i++)
		Test[Sta[i]]=false;
}
inline void Solve(int from){
	Visit[from]=Test[0]=true;CalcAns(from);
	for(int k=Last[from];k!=-1;k=Next[k]){
		if(Visit[To[k]])continue;
		sum=Size[To[k]];
		Maxi[root=0]=0x3f3f3f3f;
		CalcRoot(To[k],from);
		Solve(root);
	}
}
int n;
int main(){
	memset(Last,-1,sizeof(Last));
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n-1;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		Insert(u,v,w);
		Insert(v,u,w);
	}
	for(int i=1;i<=q;i++)
		scanf("%d",&Query[i]),maxk=Max(maxk,Query[i]);
	Maxi[root]=sum=n;
	CalcRoot(1,0);
	Solve(root);
	for(int i=1;i<=q;i++)
		printf("%s\n",Ans[i]?"AYE":"NAY");
	return 0;
}
```

LinkCutTree

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
template<typename datatype>
inline void Swap(datatype&x,datatype&y){
	static datatype t;t=x;x=y;y=t;
}
struct LinkCutTrees{
	#define MaxN 110000
	int Son[MaxN][2],Dad[MaxN];
	int Sum[MaxN],Data[MaxN];
	bool ReverseTag[MaxN];
	inline void PushUp(int now){
		//Size[now]=Size[Son[now][0]]+Size[Son[now][1]]+1;
		Sum[now]=Sum[Son[now][0]]^Sum[Son[now][1]]^Data[now];
	}
	inline void PushDown(int now){
		if(ReverseTag[now]){
			if(Son[now][0]){
				ReverseTag[Son[now][0]]^=1;
				Swap(Son[Son[now][0]][0],Son[Son[now][0]][1]);
			}
			if(Son[now][1]){
				ReverseTag[Son[now][1]]^=1;
				Swap(Son[Son[now][1]][0],Son[Son[now][1]][1]);
			}
			ReverseTag[now]=false;
		}
	}
	inline bool NotRoot(int now){return Son[Dad[now]][0]==now||Son[Dad[now]][1]==now;}
	inline bool Which(int now){return Son[Dad[now]][1]==now;}
	inline void Union(int dad,int son){if(son!=0)Dad[son]=dad;}
	inline void Rotate(int now){
		int dad=Dad[now];bool flag=Which(now);
		Son[dad][flag]=Son[now][!flag];
		Union(dad,Son[now][!flag]);
		if(NotRoot(dad))Son[Dad[dad]][Which(dad)]=now;
		Union(Dad[dad],now);
		Son[now][!flag]=dad;
		Union(now,dad);
		PushUp(dad);PushUp(now);
		return;
	}
	inline void SplayInit(int now){
		if(NotRoot(now))SplayInit(Dad[now]);
		PushDown(now);
	}
	inline void Splay(int now){
		SplayInit(now);
		for(int dad=Dad[now];NotRoot(now);Rotate(now),dad=Dad[now])
			if(NotRoot(dad))Rotate(Which(now)^Which(dad)?now:dad);
	}
	inline void Access(int now){
		for(int tmp=0;now;tmp=now,now=Dad[now])
			Splay(now),Son[now][1]=tmp,PushUp(now);
	}
	inline void MakeRoot(int now){
		Access(now);Splay(now);
		ReverseTag[now]^=1;
		Swap(Son[now][0],Son[now][1]);
	}
	inline int FindRoot(int now){
		Access(now);Splay(now);
		while(Son[now][0])PushDown(now),now=Son[now][0];
		Splay(now);
		return now;
	}
	inline bool Link(int x,int y){
		MakeRoot(x);
		if(FindRoot(y)==x)return false;
		Dad[x]=y;
		return true;
	}
	inline void Split(int x,int y){
		MakeRoot(x);Access(y);Splay(y);
	}
	inline bool Cut(int x,int y){
		MakeRoot(x);
		if(FindRoot(y)!=x||Dad[y]!=x||Son[y][0])return false;
		Dad[y]=0;Son[x][1]=0;
		return true;
	}
	inline int Query(int x,int y){
		Split(x,y);
		return Sum[y];
	}
	inline void Modify(int x,int v){
		Access(x);
		Splay(x);
		Data[x]=v;
		PushUp(x);
	}
};
#define GetChar() getchar()
template<typename datatype>
inline void Reader(datatype&x){
	static bool f;f=false;x=0;
	static char c;c=GetChar();
	while(c>57||c<48){
		if(c=='-')f=true;
		c=GetChar();
	}
	while(!(c>57||c<48)){
		x=(x<<3)+(x<<1)+c-48;
		c=GetChar();
	}
	if(f)x=-x;
}
LinkCutTrees T;
int n,m;
int main(){
	Reader(n);Reader(m);
	for(int i=1;i<=n;i++)
		Reader(T.Data[i]),T.PushUp(i);
	for(int i=1;i<=m;i++){
		int opt,x,y;
		Reader(opt);Reader(x);Reader(y);
		switch(opt){
			case 0:
				printf("%d\n",T.Query(x,y));
				break;
			case 1:
				T.Link(x,y);
				break;
			case 2:
				T.Cut(x,y);
				break;
			case 3:
				T.Modify(x,y);
				break;
		}
	}
	return 0;
}
```

矩阵求逆

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long Mod=1000000007;
inline long long GetPow(long long x,long long n){
	long long r=1;x%=Mod;
	while(n){
		if(n&1)r=r*x%Mod;
		x=x*x%Mod;n>>=1;
	}
	return r;
}
inline long long GetInv(long long x){
	return GetPow(x,Mod-2);
}
long long Arr[410][810];
int n;
inline bool Gauss(){
	int now=1;//哪一条方程 
	for(int i=1;i<=n;i++){//哪一个元 
		int tmp=now;
		while(tmp<=n&&Arr[tmp][i]==0)tmp++;
		if(tmp==n+1)return false;
		for(int j=i;j<=2*n;j++)
			swap(Arr[tmp][j],Arr[now][j]);
		for(int j=1;j<=n;j++){
			if(now==j)continue;
			long long tmp=Arr[j][i]*GetInv(Arr[now][i])%Mod;
			for(int k=i;k<=2*n;k++)
				Arr[j][k]=(Arr[j][k]+Mod-Arr[now][k]*tmp%Mod)%Mod;
		}
		now++;
	}
	return true;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&Arr[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=n+1;j<=2*n;j++)
			Arr[i][j]=(i==j-n);
	bool flag=Gauss();
	if(!flag)puts("No Solution");
	else{
		for(int i=1;i<=n;i++,puts(""))
			for(int j=n+1;j<=2*n;j++)
				printf("%lld ",Arr[i][j]*GetInv(Arr[i][i])%Mod);
	}
	return 0;
}
```

Exbsgs

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<map>
#include<cmath>
using namespace std;

inline int Gcd(int a,int b){
	return b==0?a:Gcd(b,a%b);
}
inline void ExGcd(int a,int b,int &x,int &y){
	if(b==0){x=1,y=0;return ;}
	ExGcd(b,a%b,y,x);y-=(a/b)*x;
}
inline int GetInv(int a,int p){
	int x,y;ExGcd(a,p,x,y);
	return (x%p+p)%p;
}

map<int,int>H;
inline int Bsgs(int a,int b,int p){
	if(1%p==b%p)return 0;
	a%=p,b%=p;
	H.clear();
	int k=ceill(sqrtl(p)),r=1;
	for(int t=0;t<k;t++){
		H[1ll*b*r%p]=t;
		r=1ll*r*a%p;
	}
	int ak=r;
	for(int t=1;t<=k;t++){
		auto q=H.find(r);
		if(q!=H.end())return 1ll*t*k-(*q).second;
		r=1ll*r*ak%p;
	}
	return -1;
}
inline int ExBsgs(int a,int b,int p){
	if(1%p==b%p)return 0;
	a%=p;b%=p;
	int g=Gcd(a,p);
	if(g!=1){
		if(b%g!=0)return -1;
		int t=ExBsgs(a,1ll*(b/g)*GetInv(a/g,p/g)%(p/g),(p/g));
		return t==-1?-1:t+1;
	}
	return Bsgs(a,b,p);
}
int a,b,p;
int main(){
	while(~scanf("%d%d%d",&a,&p,&b)&&!(a==0&&b==0&&p==0)){
		int t=ExBsgs(a,b,p);
		if(t==-1)puts("No Solution");
		else printf("%d\n",t);
	}
	return 0;
}
```

狄利克雷前缀和

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#define uint unsigned int
uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}
namespace Chx{
	int n;
	uint Arr[20000000];
	bool Visit[20000000];
	inline void Main(){
		scanf("%d%u",&n,&seed);
		for(int i=1;i<=n;i++)
			Arr[i]=getnext();
		uint t=0;
		Visit[1]=1;
		for(int i=1;i<=n;i++){
			if(!Visit[i])
				for(int j=1;j*i<=n;j++)
					Arr[j*i]+=Arr[j],Visit[j*i]=true;
			t^=Arr[i];
		}
		printf("%u",t);
	}
}
int main(){
	Chx::Main();
	return 0;
}
```

传递闭包

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<bitset>
using namespace std;
#define GetChar() getchar()
template<typename T>
void ReadInt(T&x){
	bool f=false;char c=GetChar();x=0;
	while(c>'9'||c<'0'){if(c=='-')f=true;c=GetChar();}
	while(c<='9'&&c>='0'){x=x*10+c-48;c=GetChar();}
	if(f)x=-x;
}
bitset<2100>K[2100];
int n;
int main(){
	ReadInt(n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int x;ReadInt(x);
			K[i][j]=x;
		}
	}
	for(int k=1;k<=n;k++)//注意阶段
		for(int i=1;i<=n;i++)
			if(K[i][k])K[i]|=K[k];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)
			printf("%d ",K[i][j]==1);
		puts("");
	}
	return 0;
}
```

差分约束

```cpp
#include<bits/stdc++.h>
#define ll long long
#define plli std::pair<ll,int>
const ll Inf=1e9;
namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
	template<typename T>
	T Min(T x,T y){return(x<y?x:y);}
	template<typename T>
	T Max(T x,T y){return(x>y?x:y);}
}
using namespace Wql;
namespace BellmanFord{
	using std::vector;
	int nv,ne,tot;
	vector<int>Last,Next,To;
	vector<int>Cost;
	vector<int>Dist;
	void Init(int nnv,int nne){
		Clear(Last);Clear(Next);Clear(To);Clear(Cost);Clear(Dist);
		nv=nnv;ne=nne;tot=0;
		Last=vector<int>(nv+1,-1);
		Next=vector<int>(ne+1,0);
		To=vector<int>(ne+1,0);
		Cost=vector<int>(ne+1,0);
		Dist=vector<int>(nv+1,0);
	}
	void Insert(int from,int to,ll cost){
		To[tot]=to;Cost[tot]=cost;
		Next[tot]=Last[from];Last[from]=tot++;
	}
	bool BellmanFord(){
		for(int i=1;i<=nv;i++){
			bool flag=false;
			for(int from=1;from<=nv;from++)
				for(int k=Last[from];k!=-1;k=Next[k])
					if(Dist[To[k]]>Dist[from]+Cost[k])
						Dist[To[k]]=Dist[from]+Cost[k],flag=true;
			if(!flag)return false;
		}
		return true;
	}
}
#define BF BellmanFord
int n,m,st;
int main(){
	scanf("%d %d",&n,&m);
	BF::Init(n,m);
	for(int i=1;i<=m;i++){
		int x,y,c;
		scanf("%d%d%d",&x,&y,&c);
		BF::Insert(y,x,c);
	}
	bool flag;
	flag=BF::BellmanFord();
	if(flag)puts("NO");
	else{
		for(int i=1;i<=n;i++)
			printf("%d ",BF::Dist[i]);
	}
	#ifndef ONLINEJUDGE
	std::system("pause");
	#endif
	return 0;
}
```

拉格朗日插值

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
const long long Mod=998244353; 
inline long long Pow(long long base,long long index)
{
	long long power=1;base%=Mod;
	while(index!=0)
	{
		if(index&1)power=power*base%Mod;
		index>>=1;base=base*base%Mod;
	}
	return power;
}
long long Lagrange(long long *x,long long *y,long long n,long long k)
{
    long long ans=0;
    for(register int i=0;i<=n;i++) 
	{
        long long s1=y[i],s2=1;
        for(register int j=0;j<=n;j++)if(i!=j) 
			{
                s1=s1*(k-x[j]+Mod)%Mod;
                s2=s2*((x[i]-x[j]+Mod)%Mod)%Mod;
            }
        ans+=s1*Pow(s2,Mod-2)%Mod;
    }
    return (ans+Mod)%Mod;
}
long long n,k,x[21000],y[21000];
int main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=0;i<n;i++)
		scanf("%lld%lld",&x[i],&y[i]);
    printf("%lld\n",Lagrange(x,y,n-1,k));
    return 0;
}
```

左偏树

```cpp
#include<cstdio>
inline void Swap(int &x,int &y){int swap=x;x=y;y=swap;}
struct LeftistTree
{
	int Dist[100010],Data[100010],Son[100010][2],Dad[100010];
	inline void Merge(int x,int y,int &root)
	{
		if(Data[x]==-1||Data[y]==-1||x==y)return;
		int fx=FindDad(x);
		int fy=FindDad(y);
		Dad[fx]=Dad[fy]=root=Merge(fx,fy);
	}
	inline int Merge(int x,int y)
	{
	    if(x==0||y==0)return x+y;
	    if(Data[x]>Data[y]||(Data[x]==Data[y]&&x>y))
	        Swap(x,y);
	    Son[x][1]=Merge(Son[x][1],y);
	    Dad[Son[x][1]]=x;
	    if (Dist[Son[x][0]]<Dist[Son[x][1]])
	        Swap(Son[x][0],Son[x][1]);
	    Dist[x]=Dist[Son[x][1]]+1;
	    return x;
	}
	inline int FindDad(int x)
	{
		if(x==Dad[x])return x;
		else return Dad[x]=FindDad(Dad[x]);
	}
	inline void Pop(int x)
	{
		if(Data[x]==-1)return ;
		x=FindDad(x);
		Data[x]=-1;
		Dad[Son[x][0]]=Son[x][0];
		Dad[Son[x][1]]=Son[x][1];
		Dad[x]=Merge(Son[x][0],Son[x][1]);
	}
	inline int Top(int x)
	{
		if(Data[x]==-1)return -1;
		x=FindDad(x);
		return Data[x];
	}
};LeftistTree T;
int n,m,opt,x,y;
int main()
{
	scanf("%d%d",&n,&m);T.Dist[0]=-1;
	for(int i=1;i<=n;i++)
		T.Dad[i]=i,scanf("%d",&T.Data[i]);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			scanf("%d",&y);
			T.Merge(x,y,x);
		}
		else
		{
			printf("%d\n",T.Top(x));
			T.Pop(x);
		}
	}
	return 0;
}
```

回文自动机

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
template<int MaxN>
struct PAMs{
	char St[MaxN];int len;
	int Len[MaxN];//回文串长度
	int Son[MaxN][26];//转移边,加一个字符还是回文
	int Fail[MaxN];//最长回文后缀
	int Sum[MaxN];
	int Link[MaxN][26];//Link[x][c] 表示节点 x 所代表的的串向左扩展一个字符 c 找到的串.
	int last,cnt;
	PAMs(){
		cnt=1;
		Fail[0]=1;//偶回文中心
		for(int i=0;i<=25;i++)
			Link[1][i]=1;
		Fail[1]=1;//奇回文中心
		for(int i=0;i<=25;i++)
			Link[0][i]=1;
		Len[1]=-1;
	}
	inline void Add(char c){
		St[++len]=c;
	    int now=last,x=St[len]-'a';
	    if(St[len-Len[now]-1]!=St[len])now=Link[now][x];
	    if(!Son[now][x]) {
	        int np=++cnt; 
			Len[np]=Len[now]+2;
	        Fail[np]=Son[Link[now][x]][x];
	        memcpy(Link[np],Link[Fail[np]],sizeof(Link[Fail[np]]));
	        Link[np][St[len-Len[Fail[np]]]-'a']=Fail[np];
			Sum[np]=Sum[Fail[np]]+1;
	        Son[now][x]=np;
	    }
	    last=Son[now][x];
	}
};PAMs<510000>PAM;
int last;char c;
int main(){
	while((c=getchar())!='\r'){
		c=(c-97+last)%26+97;
		PAM.Add(c);
		printf("%d ",last=PAM.Sum[PAM.last]);
	}
	return 0;
}
```

多项式快速幂

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int input=1000000;
char InPut[1000005];
inline char GetChar()
{
	if(input>=1000000)fread(InPut,1,1000000,stdin),input=0;
	return InPut[input++];
}
#define GetChar() getchar()
template<typename Typename>
inline void Read(Typename &s)
{
	register bool f=false;register char c=GetChar();
	s=0.0;
	while(c>'9'||c<'0'){if(c=='-')f=true;c=GetChar();}
	while(!(c>'9'||c<'0')){s=s*10+c-48;c=GetChar();}
	if(f)s=-s;
}
const int Mod=998244353;
const int Maxn=3e6;
template<typename Typename>
inline void Swap(Typename &x,Typename &y)
{register Typename swap=x;x=y;y=swap;}
inline long long GetPow(long long base,long long index)
{
	long long power=1;base%=Mod;
	while(index!=0)
	{
		if(index&1)power=power*base%Mod;
		index>>=1;base=base*base%Mod;
	}
	return power;
}
int Rev[Maxn];long long Gn[25],Gi[25];
inline void RevInit(int limit,int len)
{
	for(register int i=1;i<limit;i++)
		Rev[i]=(Rev[i>>1]>>1)|((i&1)<<(len-1));
}
inline void NTTInit()
{
	for(register int i=1,g=1;g<=23;g++,i<<=1)
	{
		Gn[g]=GetPow(3,(Mod-1)/(i<<1));
		Gi[g]=GetPow(Gn[g],Mod-2);
	}
}
inline void NTT(long long *Arr,int limit,bool flag=true)
{
	for(register int i=0;i<limit;i++)
		if(i<Rev[i])Swap(Arr[i],Arr[Rev[i]]);
	for(register int i=1,g=1;i<limit;i<<=1,g++)
	{
		register long long T=flag?Gn[g]:Gi[g];
		for(register int j=0;j<limit;j+=(i<<1))
		{
			register long long W=1;
			for(register int k=0;k<i;k++,W=(W*T)%Mod)
			{
				register long long x=Arr[j+k],y=W*Arr[j+k+i]%Mod;
				Arr[j+k]=(x+y)%Mod;Arr[j+k+i]=(x-y+Mod)%Mod;
			}
		}
	}
	if(flag)return;
	long long I=GetPow(limit,Mod-2);
	for(register int i=0;i<limit;i++)Arr[i]=Arr[i]*I%Mod;
}
long long Copy[Maxn];
inline void GetInv(long long *Arr,long long *Inv,int n)
{
	int now=1,limit=2,len=1;
	Inv[0]=GetPow(Arr[0],Mod-2);
	while(now<n*2)
	{
		RevInit(limit,len);
		for(register int i=0;i<now;i++)Copy[i]=Arr[i];
		for(register int i=now;i<limit;i++)Copy[i]=0;
		NTT(Copy,limit);NTT(Inv,limit);
		for(register int i=0;i<limit;i++)
			Inv[i]=((2ll-Inv[i]*Copy[i]%Mod)+Mod)%Mod*Inv[i]%Mod;
		NTT(Inv,limit,false);
		for(register int i=now;i<limit;i++)Inv[i]=0;
		now<<=1;limit<<=1;len++;
	}
}
inline void GetDev(long long *Arr,long long *Inv,int n)
{
	for(register int i=1;i<n;i++)Inv[i-1]=i*Arr[i]%Mod;
	Inv[n-1]=0;
}
inline void GetInvDev(long long *Arr,long long *Inv,int n)
{
	for(register int i=1;i<n;i++)Inv[i]=Arr[i-1]*GetPow(i,Mod-2)%Mod;
	Inv[0]=0;
}
long long TmpAi[Maxn],TmpBi[Maxn];
inline void GetLn(long long *Arr,long long *Inv,int n)
{
	for(register int i=0;i<=(n<<1);i++)TmpAi[i]=0;
	for(register int i=0;i<=(n<<1);i++)TmpBi[i]=0;
	GetDev(Arr,TmpAi,n);
	GetInv(Arr,TmpBi,n);
	int limit=1,len=0;
	while(limit<(n<<1))limit<<=1,len++;
	RevInit(limit,len);
	NTT(TmpAi,limit);NTT(TmpBi,limit);
	for(register int i=0;i<limit;i++)TmpAi[i]=TmpAi[i]*TmpBi[i]%Mod;
	NTT(TmpAi,limit,false);
	GetInvDev(TmpAi,Inv,n);
}
long long TmpCi[Maxn],TmpDi[Maxn];
inline void GetExp(long long *Arr,long long *Inv,int n)
{
	int len=1,limit=2,now=1;
	Inv[0]=1;
	while(now<n*2)
	{
		RevInit(limit,len);
		for(register int i=0;i<limit;i++)TmpCi[i]=0;
		for(register int i=0;i<now;i++)TmpDi[i]=Arr[i];
		for(register int i=now;i<limit;i++)TmpDi[i]=0;
		GetLn(Inv,TmpCi,now);
		NTT(Inv,limit);NTT(TmpCi,limit);NTT(TmpDi,limit);
		for(register int i=0;i<limit;i++)
			Inv[i]=(1ll-TmpCi[i]+TmpDi[i]+Mod)*Inv[i]%Mod;
		NTT(Inv,limit,false);
		for(register int i=now;i<limit;i++)Inv[i]=0;
		now<<=1;limit<<=1;len++;
	}
}
long long Arr[Maxn],Ans[Maxn],Tot[Maxn];int n;
long long k;
char St[1000000];
int main()
{
	NTTInit();
	Read(n);
	scanf("%s",St+1);
	for(register int i=1;i<=(int)strlen(St+1);i++)
		k=(k*10+St[i]-48)%Mod;
	for(register int i=0;i<n;i++)
		scanf("%lld",&Arr[i]);
	GetLn(Arr,Ans,n);
	for(register int i=0;i<n;i++)
		Ans[i]=Ans[i]*k%Mod;
	GetExp(Ans,Tot,n);
	for(register int i=0;i<n;i++)
		printf("%lld ",Tot[i]);
	return 0;
}
```

网络最大流

```cpp
#include<bits/stdc++.h>

namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
}
using namespace Wql;

namespace Flow{
	using namespace std;
	template<typename T>
	struct Infs{
		const static T Inf;
	};
	template<typename T>
	const T Infs<T>::Inf=T();
	
	template<>
	const int Infs<int>::Inf=0x3f3f3f3f;
	template<>
	const long long Infs<long long>::Inf=0x3f3f3f3f3f3f3f3f;
	
	template<typename flowtype>
	struct FlowGraphs{
		int cnt;
		vector<int>Last,Next,To;
		vector<flowtype>Flow;
		int nn,nm;
		void Init(int n,int m){
			cnt=0;
			Clear(Last);Clear(Next);Clear(To);
			Clear(Flow);
			Last=vector<int>(n+1,-1);
			Next=vector<int>(m+1,0);
			To=vector<int>(m+1,0);
			Flow=vector<flowtype>(m+1,0);
			nn=n;nm=m;
		}
		void Insert(int from,int to,flowtype flow1,flowtype flow2){
			To[cnt]=to;Flow[cnt]=flow1;
			Next[cnt]=Last[from];Last[from]=cnt++;
			To[cnt]=from;Flow[cnt]=flow2;
			Next[cnt]=Last[to];Last[to]=cnt++;
		}
		queue<int,list<int>>Q;
		vector<int>High;
		int ssurc,ssink;
		bool Bfs(){
			Clear(Q);Clear(High);
			Q.push(ssink);
			High=vector<int>(nn+1,0);
			High[ssink]=1;
			while(!Q.empty()){
				int from=Q.front();Q.pop();
				for(int k=Last[from];k!=-1;k=Next[k]){
					if(Flow[k^1]&&High[To[k]]==0){
						High[To[k]]=High[from]+1;
						if(To[k]==ssurc)return true;
						Q.push(To[k]);
					}
				}
			}
			return false;
		}
		vector<int>Cur;
		flowtype Dfs(int from,flowtype flow){
			if(from==ssink)return flow;
			flowtype used=0,test;
			for(int k=Cur[from];k!=-1;k=Next[k]){
				Cur[from]=k;
				if(Flow[k]&&High[To[k]]==High[from]-1){
					test=Dfs(To[k],min(flow-used,Flow[k]));
					used+=test;Flow[k]-=test;Flow[k^1]+=test;
					if(used==flow)return flow;
				}
			}
			High[from]=0;
			return used;
		}
		flowtype Dinic(){
			flowtype ans=0,test;
			while(Bfs()){
				Cur=Last;
				while((test=Dfs(ssurc,Infs<flowtype>::Inf)))
					ans+=test;
			}
			return ans;
		}
		flowtype Dinic(int source,int sink){
			ssurc=source;ssink=sink;
			return Dinic();
		}
	};
}

#define ll long long

int n,m,s,t;
int main(){
	scanf("%d%d%d%d",&n,&m,&s,&t);
	if(false){
		Flow::FlowGraphs<ll>G;
		G.Init(n,2*m);
		Flow::FlowGraphs<ll>C;
		C.Init(n,2*m);
		for(int i=1;i<=m;i++){
			int x,y;ll f;
			scanf("%d%d%lld",&x,&y,&f);
			G.Insert(x,y,0,0);
			C.Insert(x,y,f,0);
		}
		ll ans=0;
		for(int i=31;i>=0;i--){
			for(int from=1;from<=n;from++){
				for(int k=G.Last[from];k!=-1;k=G.Next[k]){
					G.Flow[k]*=2;
					G.Flow[k]+=(C.Flow[k]>>i)&1;
				}
			}
			ans*=2;
			ans+=G.Dinic(s,t);
		}
		printf("%lld\n",ans);
	}
	else{
		Flow::FlowGraphs<ll>G;
		G.Init(n,2*m);
		for(int i=1;i<=m;i++){
			int x,y;ll f;
			scanf("%d%d%lld",&x,&y,&f);
			G.Insert(x,y,f,0);
		}
		printf("%lld\n",G.Dinic(s,t));
	}
	return 0;
}
```

行列式求值

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>

int Mod;
inline int Add(int x,int y){
	int t=x+y;
	return t>=Mod?t-Mod:t;
}
inline int Sub(int x,int y){
	int t=x-y;
	return t<0?t+Mod:t;
}
inline int Mul(int x,int y){return 1ll*x*y%Mod;}

template<typename datatype>
inline void ReadInt(datatype&x){
	static bool f;f=false;x=0;
	static char c;c=getchar();
	while(c>'9'||c<'0'){if(c=='-')f=true;c=getchar();}
	while(!(c>'9'||c<'0')){x=x*10+c-48;c=getchar();}
	if(f)x=-x;
}

template<typename datatype>
inline void Swap(datatype&x,datatype&y){datatype t;t=x;x=y;y=t;}

namespace Gauss{
	struct Matrixes{
		int A[610][610],n,m;
		inline int*operator[](const int&idx){return A[idx];}
	};Matrixes M;
	inline int Gauss(){
		int res=1;
		for(int i=1;i<=M.n;i++){//未知元
			for(int j=i+1;j<=M.m;j++){//方程
				while(M[i][i]){
					int div=M[j][i]/M[i][i];
					for(int k=i;k<=M.n;k++)
						M[j][k]=Sub(M[j][k],Mul(div,M[i][k]));
					for(int k=i;k<=M.n;k++)
						Swap(M[j][k],M[i][k]);
					res=Mul(res,Mod-1);
				}
				for(int k=i;k<=M.n;k++)
					Swap(M[j][k],M[i][k]);
				res=Mul(res,Mod-1);
			}
		}
		for(int i=1;i<=M.n;i++)
			res=Mul(res,M[i][i]);
		return res;
	}
	int n;
	inline void Main(){
		ReadInt(n),ReadInt(Mod);
		M.n=M.m=n;;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				ReadInt(M[i][j]),M[i][j]%=Mod;
		printf("%d\n",Gauss());
	}
}
int main(){
	Gauss::Main();
	return 0;
}
```

最小表示法

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n,St[610000];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&St[i]);
	for(int i=1;i<=n;i++)
		St[i+n]=St[i];
	
	int i=1,j=2;
	while(i<=n&&j<=n){
		int k;
		for(k=0;k<=n-1&&St[i+k]==St[j+k];k++);//相同的部分不影响答案 
		if(k==n)break;
		if(St[i+k]>St[j+k]){//j是比i更优的解 
			i=i+k+1;
			if(i==j)i++;
		}
		else{//反过来 
			j=j+k+1;
			if(i==j)j++;
		}
	}
	
	int ans=min(i,j);
	
	for(int i=ans;i<=ans+n-1;i++)
		printf("%d ",St[i]); 
	
	return 0;
} 
```

线段树分裂

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int IOSize=(1<<15)+1;
int input=IOSize;
char InPut[IOSize];
inline char GetChar(){
    if(input>=IOSize)fread(InPut,1,IOSize,stdin),input=0;
    return InPut[input++];
}
template<typename datatype>
inline void Read(datatype&s){
	static bool f;f=false;s=0;
	static char c;c=GetChar();
	while(c>'9'||c<'0'){if(c=='-')f=true;c=GetChar();}
	while(!(c>'9'||c<'0')){s=s*10+c-48;c=GetChar();}
	if(f==true)s=-s;
}
template<typename datatype>
inline void Read(datatype&x,datatype&y){
	Read(x);Read(y);
}
template<typename datatype>
inline void Read(datatype&x,datatype&y,datatype&z){
	Read(x);Read(y);Read(z);
}

template<int MaxN>
struct SegmentTrees{
	int Son[MaxN][2];
	long long Size[MaxN];
	int Trash[MaxN],top,cnt;
	inline void Recycle(int&now){
		Size[now]=0;
		Son[now][0]=Son[now][1]=0;
		Trash[++top]=now;
		now=0;
	}
	inline int Create(){return top?Trash[top--]:++cnt;}
	inline void PushUp(int now){
		Size[now]=Size[Son[now][0]]+Size[Son[now][1]];
	}
	inline void Build(int&now,int Left,int Right,long long*Arr){
		if(!now)now=Create();
		if(Left==Right){
			Size[now]=Arr[Left];
			return;
		}
		else{
			int Mid=(Left+Right)>>1;
			Build(Son[now][0],Left,Mid,Arr);
			Build(Son[now][1],Mid+1,Right,Arr);
			PushUp(now);
		}
	}
	inline int Merge(int x,int y,int Left,int Right){
		if(!x||!y)return x+y;
		if(Left==Right){
			Size[x]+=Size[y];
			Recycle(y);
			return x;
		}
		else{
			int Mid=(Left+Right)>>1;
			Son[x][0]=Merge(Son[x][0],Son[y][0],Left,Mid);
			Son[x][1]=Merge(Son[x][1],Son[y][1],Mid+1,Right);
			Recycle(y);
			PushUp(x);
			return x;	
		}
	}
	inline void Split(int&x,int&y,int left,int right,int Left,int Right){
		if(x==0)return;
		if(left<=Left&&Right<=right){
			y=x;x=0;
			return ;
		}
		else{
			int Mid=(Left+Right)>>1;
			if(!y)y=Create();
			if(left<=Mid)
				Split(Son[x][0],Son[y][0],left,right,Left,Mid);
			if(Mid+1<=right)
				Split(Son[x][1],Son[y][1],left,right,Mid+1,Right);
			PushUp(x);
			PushUp(y);
		}
	}
	inline void Update(int&now,int pos,long long val,int Left,int Right){
		if(!now)now=Create();
		if(Left==Right){
			Size[now]+=val;
			return;
		}
		else{
			int Mid=(Left+Right)>>1;
			if(pos<=Mid)Update(Son[now][0],pos,val,Left,Mid);
			else Update(Son[now][1],pos,val,Mid+1,Right);
			PushUp(now);
		}
	}
	inline int Select(int&now,long long rank,int Left,int Right){
		if(Left==Right)return Left;
		else{
			int Mid=(Left+Right)>>1;
			if(rank<=Size[Son[now][0]])
				return Select(Son[now][0],rank,Left,Mid);
			else 
				return Select(Son[now][1],rank-Size[Son[now][0]],Mid+1,Right);
		}
	}
	inline long long Query(int now,int left,int right,int Left,int Right){
		if(!now)return 0;
		if(left<=Left&&Right<=right)return Size[now];
		else{
			int Mid=(Left+Right)>>1;
			long long tmp1=0,tmp2=0;
			if(left<=Mid)tmp1=Query(Son[now][0],left,right,Left,Mid);
			if(Mid+1<=right)tmp2=Query(Son[now][1],left,right,Mid+1,Right);
			return tmp1+tmp2;
		}
	}
};

SegmentTrees<210000*18+2*210000>T;

int n,m,tot,Root[210000];
int opt,x,y,p;long long k,ans,Arr[210000];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		Read(Arr[i]);
	T.Build(Root[tot=1],1,n,Arr);
	for(int i=1;i<=m;i++){
		Read(opt);
		switch(opt){
			case 0:
				Read(p,x,y);
				T.Split(Root[p],Root[++tot],x,y,1,n);
				break;
			case 1:
				Read(x,y);
				T.Merge(Root[x],Root[y],1,n);
				break;
			case 2:
				Read(p);Read(k);Read(x);
				T.Update(Root[p],x,k,1,n);
				break;
			case 3:
				Read(p,x,y);
				printf("%lld\n",T.Query(Root[p],x,y,1,n));
				break;
			case 4:
				Read(p);Read(k);
				if(k>T.Size[Root[p]])ans=-1;
				else ans=T.Select(Root[p],k,1,n);
				printf("%lld\n",ans);
				break;
		}
	}
	return 0;
}
```

ExKmp

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MaxN=21000000;

int Zi[MaxN*2],la,lb;
long long ans;
char A[MaxN];
char B[MaxN];
char C[MaxN*2];

int main(){
	scanf("%s",A+1);
	la=strlen(A+1);
	scanf("%s",B+1);
	lb=strlen(B+1);
	for(int i=1;i<=lb;i++)
		C[i]=B[i];
	for(int i=1;i<=la;i++)
		C[i+lb]=A[i];
	//拼接是常用的技巧 当然用 z of B 求出 z of A 也可行 
		
	Zi[1]=la+lb-1;
	for(int i=2,l=0,r=0;i<=la+lb;i++){
		if(i<=r&&Zi[i-l+1]<=r-i)
			Zi[i]=Zi[i-l+1];
		else{	
			Zi[i]=max(0,r-i);
			while(i+Zi[i]<=la+lb&&C[Zi[i]+1]==C[i+Zi[i]])
				Zi[i]++;
		}
		if(i+Zi[i]-1>r)l=i,r=i+Zi[i]-1;
	}
	
	ans=0;
	for(int i=1;i<=lb;i++)
		ans^=1ll*i*(min(Zi[i],lb-i+1)+1);
	printf("%lld\n",ans);
	ans=0;
	for(int i=lb+1;i<=lb+la;i++)
		ans^=1ll*(i-lb)*(min(Zi[i],lb)+1);
	printf("%lld\n",ans);
	
	return 0;
} 
```

李超线段树

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<random>
using namespace std;

const double Eps=1e-9;
const int Mod1=39989;
const int Mod2=1000000000;
typedef pair<double,int>Pdi;

inline int Cmp(const double&x,const double&y){
	if(x-y>Eps)return 1;
	if(y-x>Eps)return -1;
	return 0;
}

struct Lines{
	double k,b;
};Lines Pi[110000];
int cnt;
int Si[160000];

inline double Calc(int id,double x){
	return Pi[id].b+x*Pi[id].k;
}

inline void Add(int x0,int y0,int x1,int y1){
	cnt++;
	if(x0==x1)//直线斜率不存在
		Pi[cnt]={0,1.0*max(y0,y1)};
	else
		Pi[cnt]={1.0*(y1-y0)/(x1-x0),y0-1.0*(y1-y0)/(x1-x0)*x0};		
}

inline void Update1(int now,int Left,int Right,int id){
	int mid=(Left+Right)>>1;
	if(Cmp(Calc(id,mid),Calc(Si[now],mid))==1)
		swap(Si[now],id);
	int bl=Cmp(Calc(id,Left),Calc(Si[now],Left));
	int br=Cmp(Calc(id,Right),Calc(Si[now],Right));
	if(bl==1||(!bl&&id<Si[now]))Update1(now<<1,Left,mid,id);
	if(br==1||(!br&&id<Si[now]))Update1(now<<1|1,mid+1,Right,id);
}

inline void Update2(int now,int Left,int Right,int left,int right,int id){
	if(left<=Left&&Right<=right){
		Update1(now,Left,Right,id);
		return ;
	}
	else{
		int mid=(Left+Right)>>1;
		if(left<=mid)Update2(now<<1,Left,mid,left,right,id);
		if(mid+1<=right)Update2(now<<1|1,mid+1,Right,left,right,id);
	}
}

inline Pdi Max(Pdi x,Pdi y){
	if(Cmp(x.first,y.first)==-1)return y;
	else if(Cmp(x.first,y.first)==1)return x;
	else return x.second<y.second?x:y;
}

inline void Query(int now,int Left,int Right,int pos,Pdi&val){
	double res=Calc(Si[now],pos);
	val=Max(val,{res,Si[now]});
	if(Left==Right)return ;
	else{
		int mid=(Left+Right)>>1;
		if(pos<=mid)Query(now<<1,Left,mid,pos,val);
		else Query(now<<1|1,mid+1,Right,pos,val);
	}
}
inline Pdi Query(int now,int Left,int Right,int pos){
	Pdi val={0,0};
	Query(now,Left,Right,pos,val);
	return val;
}

int n,lastans=0;
int main(){
	scanf("%d",&n);
	while(n--){
		int opt;scanf("%d",&opt);
		if(opt==1){
			int x0,y0,x1,y1;
			scanf("%d%d%d%d",&x0,&y0,&x1,&y1);
			x0=(x0+lastans-1+Mod1)%Mod1+1;
			x1=(x1+lastans-1+Mod1)%Mod1+1;
			y0=(y0+lastans-1+Mod2)%Mod2+1;
			y1=(y1+lastans-1+Mod2)%Mod2+1;
			if(x0>x1)swap(x0,x1),swap(y0,y1);
			Add(x0,y0,x1,y1);
			Update2(1,1,Mod1,x0,x1,cnt);
		}
		else{
			int x;scanf("%d",&x);
			x=(x+lastans-1+Mod1)%Mod1+1;
			printf("%d\n",lastans=Query(1,1,Mod1,x).second);
		}
	}
	return 0;
}
```

匈牙利算法

```cpp
#include<bits/stdc++.h>



namespace Wql{
	template<typename T>
	T Min(T a,T b){if(a<b)return a;else return b;}
	template<typename T>
	T Max(T a,T b){if(a>b)return b;else return a;}
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
}
using namespace Wql;

namespace ErFenTuPiFei{
	using namespace std;
	
	int cnt,nn1,nn2,nm;
	vector<int>Last;
	vector<int>Next;
	vector<int>To;
	int tim;
	vector<int>Vis2;
	vector<int>Mat1;
	vector<int>Mat2;
	vector<int>Pre2;
	void Insert(int from,int to){
		To[cnt]=to;
		Next[cnt]=Last[from];Last[from]=cnt++;
	}
	void Init(int n1,int n2,int m){
		Clear(Last);Clear(Next);Clear(To);
		Clear(Vis2);
		Clear(Pre2),Clear(Mat1),Clear(Mat2);
		cnt=0;
		Last=vector<int>(n1+1,-1);
		Next=vector<int>(m,0);
		To=vector<int>(m,0);
		tim=0;
		Vis2=vector<int>(n2+1,0);
		Pre2=vector<int>(n2+1,-1);
		Mat1=vector<int>(n1+1,-1);
		Mat2=vector<int>(n2+1,-1);
		nn1=n1,nn2=n2,nm=m;
	}
	void Augment(int from){//from是二类点
		int tmp;
		while(from!=-1){
			tmp=Mat1[Pre2[from]];
			Mat1[Pre2[from]]=from;
			Mat2[from]=Pre2[from];
			from=tmp;
		}
	}
	queue<int,list<int>>Q;
	bool Bfs(int now){
		Clear(Q);
		Q.push(now);
		while(!Q.empty()){
			int from=Q.front();Q.pop();
			for(int k=Last[from];k!=-1;k=Next[k]){
				int to=To[k];
				if(Vis2[to]==tim)continue;
				Vis2[to]=tim;
				Pre2[to]=from;
				if(Mat2[to]==-1){
					Augment(to);
					return true;
				}
				else Q.push(Mat2[to]);
			}
		}
		return false;
	}
	void Solve(){
		int ans=0;
		for(int i=1;i<=nn1;i++)
			if(Mat1[i]==-1)tim++,ans+=Bfs(i);
		printf("%d\n",ans);
	}
}

#define So ErFenTuPiFei

int n1,n2,m;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	scanf("%d%d%d",&n1,&n2,&m);
	So::Init(n1,n2,m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		So::Insert(x,y);
	}
	So::Solve();
	return 0;
}
```

Bsgs

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<unordered_map>
#include<random>
using namespace std;

std::default_random_engine GetWql(20051219u);

struct Hashs{
	unordered_map<long long,long long>M;
	long long tmp;
	Hashs(){tmp=GetWql();}
	inline void Insert(long long x,long long y){M[x^tmp]=y;}
	inline long long Query(long long x){
		auto t=M.find(x^tmp);
		if(t!=M.end())return (*t).second;
		else return -1ll;
	}
	inline void Clear(){M.clear();}
};
Hashs H;

inline long long Bsgs(long long a,long long b,long long p){
	b%=p;a%=p;//a\in[0,p),b\in[0,p)
	if(a==0)return b==0?1:-1;//特判1
	if(1%p==b%p)return 0;//特判2,a^0
	H.Clear();
	long long k=sqrtl(p)+1,r,t;//a^x=b\pmod p,x=ik-t
	r=1;
	for(int t=0;t<k;t++){
		H.Insert(b*r%p,t);//ba^t,t\in[0,k)
		r=r*a%p;
	}
	long long ak=r;
	for(int x=1;x<=k;x++){
		if((t=H.Query(r))!=-1)return k*x-t;
		r=r*ak%p;
	}
	return -1;
}
long long p,b,n;
int main(){
	scanf("%lld%lld%lld",&p,&b,&n);
	long long ans=Bsgs(b,n,p);
	if(ans==-1)puts("no solution");
	else printf("%lld\n",ans);
}
```

带花树

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
const int MaxN=1100;
const int MaxM=110000;
int Dad[MaxN];
inline int GetDad(int x){return x==Dad[x]?x:Dad[x]=GetDad(Dad[x]);}
int Match[MaxN],Pre[MaxN];
inline int GetLca(int x,int y){
    static int Dfn[MaxN],now;now++;
    while(x){
        x=GetDad(x);
        Dfn[x]=now;
        x=Pre[Match[x]];
    }
    while(y){
        y=GetDad(y);
        if(Dfn[y]==now)return y;
        y=Pre[Match[y]];
    }
    return 0;
}
//Group 形成一朵花
int Mark[MaxN];queue<int>Q;
inline void Group(int x,int lca){
    while(x!=lca){
        int y=Match[x],z=Pre[y];
        if(GetDad(z)!=lca)Pre[z]=y;//双向一下 便于更新
        if(Mark[y]==2)Q.push(y),Mark[y]=1;
        if(Mark[z]==2)Q.push(z),Mark[z]=1;//花上的点再次寻找增广路
        Dad[x]=y;Dad[y]=z;x=z;
    }
}
inline void Augment(int x,int y){
    while(y!=0){
        int z=Match[x];
        Match[x]=y;
        Match[y]=x;
        y=z;x=Pre[y];
    }
}
int Last[MaxN],To[MaxM],Next[MaxM],cnt;
inline void Clear(){cnt=0;memset(Last,-1,sizeof(Last));}
inline void Insert(int from,int to){
    To[cnt]=to;
    Next[cnt]=Last[from];Last[from]=cnt++;
}
int n,ans;
inline bool Bfs(int start){
    for(int i=1;i<=n;i++)
        Mark[i]=0,Pre[i]=0,Dad[i]=i;
    Mark[start]=1;
    while(!Q.empty())Q.pop();
    Q.push(start);
    while(!Q.empty()){
        int from=Q.front();Q.pop();
        for(int k=Last[from];k!=-1;k=Next[k]){
            if(Mark[To[k]]==2||Match[from]==To[k])continue;//增广没有收益
            int dadx=GetDad(from);
            int dady=GetDad(To[k]);
            if(dadx==dady)continue;//我们在同一朵花里 增广没有收益
            if(Mark[To[k]]==1){//一类点 形成奇环
                int lca=GetLca(To[k],from);
                if(dadx!=lca)Pre[from]=To[k];
                if(dady!=lca)Pre[To[k]]=from;
                Group(from,lca);Group(To[k],lca);
            }
            else{
                if(Match[To[k]]==0){
                    Augment(from,To[k]);
                    return true;
                }
                else{
                    Pre[To[k]]=from;//记录前驱,增广的时候用
                    Q.push(Match[To[k]]);
                    Mark[To[k]]=2;
                    Mark[Match[To[k]]]=1;
                }
            }
        }
    }
    return false;
}
int m;
int main(){
    Clear();
    scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++){
        scanf("%d%d",&x,&y);
		Insert(x,y);
		Insert(y,x);
	}
	ans=0;
	for(int i=1;i<=n;i++)
		if(Match[i]==0&&Bfs(i))ans++;
	printf("%d\n",ans);
	for(register int i=1;i<=n;i++)
		printf("%d ",Match[i]);
	return 0;
}
```

Zkw费用流

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

template<typename datatype>
inline void ReadInt(datatype&x){
	static bool f;f=false;x=0;
	static char c;c=getchar();
	while(c>57||c<48){
		if(c=='-')f=true;
		c=getchar();
	}
	while(!(c>57||c<48)){
		x=(x<<1)+(x<<3)+c-48;
		c=getchar();
	}
	if(f)x=-x;
}

template<typename datatype>
inline datatype Min(const datatype&x,const datatype&y){
	return(x<y?x:y);
}
template<typename datatype>
const datatype Inf;
template<>
const long long Inf<long long>{0x3f3f3f3f3f3f3f3f};
typedef long long costtype;
typedef long long flowtype;
const int MaxN=5100;
const int MaxM=101000;

template<typename datatype1,typename datatype2>
struct Pairs{
	datatype1 x;datatype2 y;
	Pairs(datatype1 _x=datatype1(),datatype2 _y=datatype2()):x(_x),y(_y){}
	inline bool operator<(const Pairs&p)const{
		return x==p.x?y>p.y:x>p.x;
	}
};

int Last[MaxN],cnt;
inline void Clear(){cnt=0;memset(Last,-1,sizeof(Last));}

costtype Cost[MaxM];
flowtype Flow[MaxM];
int To[MaxM],Next[MaxM];
inline void Insert(int from,int to,flowtype flow1,costtype cost1,flowtype flow2,costtype cost2){
	To[cnt]=to;Flow[cnt]=flow1;Cost[cnt]=cost1;
	Next[cnt]=Last[from];Last[from]=cnt++;
	To[cnt]=from;Flow[cnt]=flow2;Cost[cnt]=cost2;
	Next[cnt]=Last[to];Last[to]=cnt++;
}

int source,sink;
costtype High[MaxN];
costtype Dist[MaxN];
bool Visit[MaxN];
inline costtype CalcC(const int&k){
	return Cost[k]+High[To[k^1]]-High[To[k]];
}
priority_queue<Pairs<costtype,int>>Q;
inline bool Dijkstra(){
	memset(Dist,0x3f,sizeof(Dist));
	Dist[source]=0;
	memset(Visit,false,sizeof(Visit));
	Q.push(Pairs<flowtype,int>(Dist[source],source));
	while(!Q.empty()){
		int from=Q.top().y;Q.pop();
		if(Visit[from])continue;
		Visit[from]=true;
		for(int k=Last[from];k!=-1;k=Next[k]){
			if(Flow[k]&&Dist[To[k]]>Dist[from]+CalcC(k)){
				Dist[To[k]]=Dist[from]+CalcC(k);
				Q.push(Pairs<flowtype,int>(Dist[To[k]],To[k]));
			}
		}
	}
	return Dist[sink]!=Inf<long long>;
}

bool InPath[MaxN];
int Cur[MaxN];
inline flowtype Dfs(int from,flowtype flow){
	if(from==sink)return flow;
	flowtype used=0,test;
	InPath[from]=true;
	for(int k=Cur[from];k!=-1;k=Next[k]){
		Cur[from]=k;
		if(!InPath[To[k]]&&Flow[k]&&Dist[To[k]]==Dist[from]+CalcC(k)){
			test=Dfs(To[k],Min(Flow[k],flow-used));
			used+=test;Flow[k]-=test;Flow[k^1]+=test;
			if(used==flow){
				InPath[from]=false;
				return used;
			}
		}
	}
	//s<f InPath won't update to true 
	return used;
}
int limit;
inline Pairs<flowtype,costtype>Zkw(){
	flowtype flow=0,test;
	costtype cost=0;
	while(Dijkstra()){
		memset(InPath,false,sizeof(InPath));
		memcpy(Cur,Last,sizeof(Last));
		test=Dfs(source,Inf<flowtype>);
		flow+=test;
		for(int i=0;i<=limit;i++)
			if(Dist[i]!=Inf<flowtype>)High[i]+=Dist[i];
		cost+=test*High[sink];
	}
	return Pairs<flowtype,costtype>(flow,cost);
}
int n,m;
int main(){
	Clear();
	ReadInt(n),ReadInt(m),ReadInt(source),ReadInt(sink);
	limit=n;
	for(int i=1;i<=m;i++){
		int x,y;long long f,c;
		ReadInt(x),ReadInt(y),ReadInt(f),ReadInt(c);
		Insert(x,y,f,c,0,-c);
	}
	Pairs<long long,long long>p=Zkw();
	printf("%lld %lld",p.x,p.y);
	return 0;
}
```

负圈费用流

```cpp
#include<cstdio>
#include<cstring> 
#include<algorithm>
#include<queue>
using namespace std;
namespace Tools{
	template<typename datatype1,typename datatype2>
	struct Pairs{
		datatype1 x;
		datatype2 y;
		Pairs(datatype1 _x=0,datatype2 _y=0):x(_x),y(_y){}
		inline bool operator<(const Pairs&p)const{
			return x>p.x;
		}
	};
	template<typename datatype1,typename datatype2>
	inline Pairs<datatype1,datatype2>MakePairs(const datatype1&x,const datatype2&y){
		return Pairs<datatype1,datatype2>(x,y);
	}
	template<typename datatype>
	const datatype Inf;
	template<>
	const long long Inf<long long>{0x3f3f3f3f3f3f3f3f};
	template<typename datatype>
	inline datatype Min(const datatype&x,const datatype&y){
		return(x<y?x:y);
	}
};
using namespace Tools;

const int MaxN=510;
const int MaxM=21000;
typedef long long flowtype;
typedef long long costtype;
int Last[MaxN],cnt;
inline void Clear(){cnt=0;memset(Last,-1,sizeof(Last));}
costtype Cost[MaxM];
flowtype Flow[MaxM];
int To[MaxM],Next[MaxM];
inline void Insert(int from,int to,flowtype flow1,costtype cost1,flowtype flow2,costtype cost2){
	To[cnt]=to;Flow[cnt]=flow1;Cost[cnt]=cost1;
	Next[cnt]=Last[from];Last[from]=cnt++;
	To[cnt]=from;Flow[cnt]=flow2;Cost[cnt]=cost2;
	Next[cnt]=Last[to];Last[to]=cnt++;
} 
costtype High[MaxN];
inline flowtype CalcC(const int&k){
	return Cost[k]+High[To[k^1]]-High[To[k]];
}
bool Visit[MaxN];
costtype Dist[MaxN];
int source,sink;
priority_queue<Pairs<costtype,int>>Q;
inline bool Dijkstra(){
	memset(Visit,false,sizeof(Visit));
	memset(Dist,0x3f,sizeof(Dist));
	Dist[source]=0;
	Q.push(MakePairs(Dist[source],source));
	while(!Q.empty()){
		int from=Q.top().y;Q.pop();
		//if(Visit[from])continue;
		//Visit[from]=true;
		for(int k=Last[from];k!=-1;k=Next[k]){
			if(Flow[k]&&Dist[To[k]]>Dist[from]+CalcC(k)){
				Dist[To[k]]=Dist[from]+CalcC(k);
				Q.push(MakePairs(Dist[To[k]],To[k]));
			}
		}
	}
	return Dist[sink]!=Inf<flowtype>;
}
bool InPath[MaxN];
int Cur[MaxN];
inline flowtype Dfs(int from,flowtype flow){
	if(from==sink)return flow;
	flowtype used=0,test;
	InPath[from]=true;
	for(int k=Cur[from];k!=-1;k=Next[k]){
		Cur[from]=k;
		if(!InPath[To[k]]&&Flow[k]&&Dist[from]==Dist[To[k]]+CalcC(k)){
			test=Dfs(To[k],Min(flow-used,Flow[k]));
			used+=test;Flow[k]-=test;Flow[k^1]+=test;
			if(used==flow){
				InPath[from]=false;
				return flow;
			}
		}
	}
	return used;
}
int limit;
inline Pairs<flowtype,costtype>Zkw(){
	flowtype flow=0,test;
	costtype cost=0;
	while(Dijkstra()){
		memset(InPath,false,sizeof(InPath));
		memcpy(Cur,Last,sizeof(Last));
		test=Dfs(source,Inf<flowtype>);
		flow+=test;
		for(int i=1;i<=limit;i++)
			if(Dist[i]!=Inf<costtype>)High[i]+=Dist[i];
		cost+=test*High[sink];
	}
	return MakePairs(flow,cost);
}

flowtype Excess[MaxN];
flowtype flow;
costtype cost;
inline void Solve(int source1,int sink1,int source2,int sink2){
	Pairs<flowtype,costtype>p;
	source=source1;sink=sink1;
	memset(High,0,sizeof(High));
	p=Zkw();
	cost+=p.y;
	source=source2;sink=sink2;
	memset(High,0,sizeof(High));
	p=Zkw();
	flow+=p.x;
	cost+=p.y;
}

int n,m,s1,t1,s2,t2;
int main(){
	Clear();
	scanf("%d%d%d%d",&n,&m,&s2,&t2);
	limit=n+4;
	for(int i=1;i<=m;i++){
		int x,y;
		long long f,c;
		scanf("%d%d%lld%lld",&x,&y,&f,&c);
		if(c>=0)Insert(x,y,f,c,0,-c);
		else{
			Excess[x]-=f;
			Excess[y]+=f;
			cost+=f*c;
			Insert(y,x,f,-c,0,c);
		}
	}
	s1=n+1,t1=n+2;
	for(int i=1;i<=n;i++){
		if(!Excess[i])continue;
		Excess[i]>0?Insert(s1,i,Excess[i],0,0,0):Insert(i,t1,-Excess[i],0,0,0);
	}
	Insert(t2,s2,Inf<flowtype>,0,0,0);
	Solve(s1,t1,s2,t2);
	printf("%lld %lld",flow,cost);
	return 0;
}
```

后缀自动机

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
long long ans;
template<int MaxN>
struct SAutomatons{
	int Link[MaxN];
	int Size[MaxN],Len[MaxN];
	int Son[MaxN][30];
	int cnt,last;
	int tot,Last[MaxN],To[MaxN],Next[MaxN];
	SAutomatons(){
		cnt=last=0;Link[last]=-1;
		tot=0;memset(Last,-1,sizeof(Last));
	}
	inline void Insert(int from,int to){
		To[tot]=to;
		Next[tot]=Last[from];Last[from]=tot++;
	}
    inline void Add(int c){
    	int now=last;Size[last=++cnt]=1;Len[last]=Len[now]+1;
    	for(;now!=-1&&Son[now][c]==0;now=Link[now])
    		Son[now][c]=cnt;
    	if(now==-1)Link[last]=0;
    	else{
    		int tmp=Son[now][c];
    		if(Len[tmp]==Len[now]+1)Link[last]=tmp;
    		else{
    			int newtmp=++cnt;
    			Len[newtmp]=Len[now]+1;
        		for(int i=0;i<=25;i++){Son[newtmp][i]=Son[tmp][i];}
    			Link[newtmp]=Link[tmp];
    			Link[tmp]=newtmp;
    			Link[last]=newtmp;
    			for(;now!=-1&&Son[now][c]==tmp;now=Link[now])Son[now][c]=newtmp;
    		}
    	}
    }
	
	inline void Build(){
		for(int i=1;i<=cnt;i++)Insert(Link[i],i);
	}
	inline void Dfs(int from){
		for(int k=Last[from];k!=-1;k=Next[k]){
			Dfs(To[k]);
			Size[from]+=Size[To[k]];
		}
		if(Size[from]!=1){
			ans=max(ans,1ll*Size[from]*Len[from]);
		}
	}
};
SAutomatons<3000000+10>SAM;
int n;char St[1100000];
int main(){
	scanf("%s",St+1);
	n=strlen(St+1);
	for(int i=1;i<=n;i++)SAM.Add(St[i]-'a');
	SAM.Build();
	SAM.Dfs(0);
	printf("%lld",ans);
	return 0;
}
```

Km算法

```cpp
#include<cmath>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const long long LLInf=0x3f3f3f3f3f3f3f3f;

const int MaxN=510;

int Match1[MaxN],Match2[MaxN],Pre[MaxN];
long long Expect1[MaxN],Expect2[MaxN],Weight[MaxN][MaxN],Slack[MaxN];

inline long long Calc(int from,int to){
	return Expect1[from]+Expect2[to]-Weight[from][to];
}
int size1,size2,st;
bool Visit1[MaxN],Visit2[MaxN];
inline bool Dfs(int from){
	Visit1[from]=true;
	for(int to=1;to<=size2;to++){
		if(Visit2[to]==true)continue;
		if(Calc(from,to)<Slack[to]){
			Slack[to]=Calc(from,to);
			Pre[to]=from;
			if(Calc(from,to)==0){
				Visit2[to]=true;
				if(!Match2[to]){
					st=to;
					return true;
				}
				else if(Dfs(Match2[to]))return true;
			}
		}
	}
	return false;
}

inline void KuhnMunkres(int start){
	memset(Visit1,false,sizeof(Visit1));
	memset(Visit2,false,sizeof(Visit2));
	memset(Slack,0x3f,sizeof(Slack));
	
	st=0;Match2[st]=start;
	
	while(Match2[st]){
		if(Dfs(Match2[st]))break;
		long long delta=LLInf;
		for(int i=1;i<=size2;i++){
			if(!Visit2[i]){
				if(delta>Slack[i]){
					delta=Slack[i];
					st=i;
				}
			}
		}
		for(int i=1;i<=size2;i++)
			if(Visit2[i])Expect2[i]+=delta;
			else Slack[i]-=delta;
		for(int i=1;i<=size1;i++)
			if(Visit1[i])Expect1[i]-=delta;
		Visit2[st]=true;
	}
	while(st){
		int tmp=Match1[Pre[st]];
		Match1[Pre[st]]=st;
		Match2[st]=Pre[st];
		st=tmp;
	}
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	size1=size2=n;
	memset(Weight,0xcf,sizeof(Weight));
	memset(Expect1,0xcf,sizeof(Expect1));
	memset(Expect2,0,sizeof(Expect2));
	for(int i=1;i<=m;i++){
		int x,y;long long c;
		scanf("%d%d%lld",&x,&y,&c);
		Weight[x][y]=c;
		Expect1[x]=max(Expect1[x],c);
	}
	for(int i=1;i<=n;i++)
		KuhnMunkres(i);
	long long ans=0;
	for(int i=1;i<=n;i++)
		ans+=Weight[i][Match1[i]];
	printf("%lld\n",ans);
	for(int i=1;i<=n;i++)
		printf("%d ",Match2[i]);
	return 0;
}
```

exgcd

```cpp
#include<cstdio> 
#include<cstring>
#include<algorithm>

inline __int128 Gcd(const __int128&a,const __int128&b){
	if(b==0)return a;
	return Gcd(b,a%b);
}
inline void ExGcd(const __int128&a,const __int128&b,__int128&x,__int128&y){
	if(b==0){x=1,y=0;return;}
	ExGcd(b,a%b,y,x);y-=(a/b)*x;
}
long long Ib,Im;
__int128 x,y,g,b1,b2,m1,m2;
int n;
int main(){
	scanf("%d",&n);
	scanf("%lld%lld",&Im,&Ib);
	
	b1=Ib;m1=Im;
	
	bool Is=true;
	for(int i=2;i<=n;i++){
		scanf("%lld%lld",&Im,&Ib);
		b2=Ib;m2=Im;
		//Ax+By=C,A=m1,B=-m2,C=b2-b1
		g=Gcd(m1,m2);
		if((b2-b1)%g){
			Is=false;
			for(int j=i+1;j<=n;j++)
				scanf("%lld%lld",&Im,&Ib);
			break;
		}
		ExGcd(m1,m2,x,y);
		x*=(b2-b1)/g;
		x=(x%(m2/g)+m2/g)%(m2/g);
		b1=x*m1+b1;
		m1=m1*m2/g;
	}
	if(Is)printf("%lld",(long long)b1);
	return 0;
}
```

exlucas

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

inline void ExGcd(long long a,long long b,long long&x,long long&y){
	if(a==0)puts("Error");
	if(b==0){x=1,y=0;return ;}
	ExGcd(b,a%b,y,x);y-=(a/b)*x;
}
inline long long GetInv(long long a,long long p){
	long long x,y;
	ExGcd(a,p,x,y);
	return (x%p+p)%p;
}

inline long long GetPow(long long x,long long n,long long p){
	long long r=1;r%=p;
	while(n){
		if(n&1)r=r*x%p;
		x=x*x%p;n>>=1;
	}
	return r;
}
inline long long GetV(long long x,long long p){
	long long ans=0;
	while(x){ans+=(x/=p);}
	return ans;
}
long long Save[1100000];
inline long long GetR(long long x,long long p,long long mod){
	if(x==0)return 1;
	return GetR(x/p,p,mod)*GetPow(Save[mod-1],x/mod,mod)%mod*Save[x%mod]%mod;
}
inline long long CalcC(long long n,long long m,long long p,long long mod){
	long long c=GetV(n,p)-GetV(m,p)-GetV(n-m,p);
	long long ans=GetPow(p,c,mod);
	if(!ans)return 0;
	Save[0]=1;
	for(int i=1;i<mod;i++){
		if(i%p==0)Save[i]=Save[i-1];
		else Save[i]=Save[i-1]*i%mod;
	}
	ans=ans*GetR(n,p,mod)%mod;
	ans=ans*GetInv(GetR(m,p,mod),mod)%mod;
	ans=ans*GetInv(GetR(n-m,p,mod),mod)%mod;
	return ans;
}

long long res,tmod=1;
inline void Insert(long long now,long long mod){
	long long newmod=mod*tmod;
	res=(res*mod%newmod*GetInv(mod,tmod)%newmod+now*tmod%newmod*GetInv(tmod,mod)%newmod)%newmod;
	tmod=newmod;
}

long long n,m,p;
int main(){
	scanf("%lld%lld%lld",&n,&m,&p);
	for(long long i=2;i*i<=p;i++){
		if(p%i==0){
			long long mod=1;
			while(p%i==0){
				mod*=i;
				p/=i;
			}
			Insert(CalcC(n,m,i,mod),mod);
		}
	}
	if(p>1)Insert(CalcC(n,m,p,p),p);
	printf("%lld\n",res);
	return 0;
}
```

线段树分治

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>
#include<vector>

template<typename datatype>
inline void Swap(datatype&x,datatype&y){datatype t;t=x;x=y;y=t;}
template<typename datatype>
inline datatype Max(const datatype&x,const datatype&y){return(x>y?x:y);}
template<typename datatype>
inline datatype Min(const datatype&x,const datatype&y){return(x<y?x:y);}

template<typename datatype>
inline void ClearStl(datatype&x){
	datatype t;x.swap(t);
}

using std::vector;
using std::pair;

namespace Chx{
	const int MaxN=110000;
	
	pair<int,int> Sta[210000];int top;
	struct UnionSets{//可撤销并查集
		int Dad[MaxN],Size[MaxN],Dist[MaxN];
		inline int GetDad(int x){
			if(x==Dad[x])return Dad[x];
			return GetDad(Dad[x]);
		}
		inline int GetDist(int x){
			if(x==Dad[x])return Dist[x];
			return GetDist(Dad[x])^Dist[x];
		}
		inline bool Union(int a,int b){
			int x=GetDad(a),y=GetDad(b);
			if(x==y)return false;
			else{
				if(Size[x]>Size[y])Swap(x,y);
				Size[y]+=Size[x];
				Dist[x]=GetDist(a)^GetDist(b)^1;
				Dad[x]=y;
				Sta[++top]={x,y};
				return true;
			}
		}
		inline void UnDo(){
			int x=Sta[top].first,y=Sta[top].second;
			Size[y]-=Size[x];
			Dist[x]=0;
			Dad[x]=x;
			top--;
		}
	};UnionSets US;
	
	struct Questions{
		int x,y;
	};Questions Qry[210000];
	
	int Son[MaxN<<1][2],cn;
	vector<int>Opt[MaxN<<1];
	inline void Add(int&now,int Left,int Right,int left,int right,int id){
		if(!now){
			now=++cn;
			ClearStl(Opt[now]);
		}
		if(left<=Left&&Right<=right){
			Opt[now].push_back(id);
			return ;
		}
		else{
			int mid=(Left+Right)>>1;
			if(left<=mid)Add(Son[now][0],Left,mid,left,right,id);
			if(mid+1<=right)Add(Son[now][1],mid+1,Right,left,right,id);
		}
	}
	
	inline void Solve(int now,int Left,int Right){
		if(!now){
			for(int i=Left;i<=Right;i++)
				puts("Yes");
			return ;
		}
		int tmp=top;
		bool flag=false;
		for(auto o:Opt[now]){
			int x=Qry[o].x,y=Qry[o].y;
			if(!US.Union(x,y))
				if(US.GetDist(x)==US.GetDist(y))
					{flag=true;break;}
		}
		if(!flag){
			if(Left==Right){
				puts("Yes");
			}
			else{
				int mid=(Left+Right)>>1;
				Solve(Son[now][0],Left,mid);
				Solve(Son[now][1],mid+1,Right);
			}
		}
		else{
			for(int i=Left;i<=Right;i++)
				puts("No");
		}
		while(top!=tmp)US.UnDo();
	}
	
	int root,n,m,k;
	inline void Main(){
		scanf("%d%d%d",&n,&m,&k);
		for(int i=1;i<=n;i++)
			US.Dad[i]=i,US.Size[i]=1,US.Dist[i]=0;
		for(int i=1;i<=m;i++){
			int a,b,c,d;scanf("%d%d%d%d",&a,&b,&c,&d);
			Qry[i]={b,a};Add(root,1,k,c+1,d,i);
		}
		Solve(root,1,k);
	}
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("In.txt","r",stdin);
	#endif
	Chx::Main();
	return 0;
}
```

快速沃尔什变换

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int Mod=998244353;
const int Inv2=499122177;

inline int A(int a,int b){
	int t=a+b;
	return t>=Mod?t-Mod:t;
}
inline int S(int a,int b){
	int t=a-b;
	return t<0?t+Mod:t;
}
inline int M(int a,int b){
	return 1ll*a*b%Mod;
}

int Arr[131072],Brr[131072];
int TmpA[131072],TmpB[131072];
int limit,n;
inline void Copy(){
	for(int i=0;i<=limit-1;i++)TmpA[i]=Arr[i];
	for(int i=0;i<=limit-1;i++)TmpB[i]=Brr[i];
}

inline void FwtOr(int*Tmp,bool flag){
	for(int i=1;i<limit;i<<=1)
		for(int j=0;j<limit;j+=(i<<1))
			for(int k=0;k<i;k++){
				int x=Tmp[j+k],y=Tmp[j+k+i];
				Tmp[j+k]=x;
				Tmp[j+k+i]=flag?A(x,y):S(y,x);
			}
}
inline void FwtAnd(int*Tmp,bool flag){
	for(int i=1;i<limit;i<<=1)
		for(int j=0;j<limit;j+=(i<<1))
			for(int k=0;k<i;k++){
				int x=Tmp[j+k],y=Tmp[j+k+i];
				Tmp[j+k]=flag?A(x,y):S(x,y);
				Tmp[j+k+i]=y;
			}
}
inline void FwtXor(int*Tmp,bool flag){
	for(int i=1;i<limit;i<<=1){
		for(int j=0;j<limit;j+=(i<<1)){
			for(int k=0;k<i;k++){
				int x=Tmp[j+k],y=Tmp[j+k+i];
				Tmp[j+k]=M(flag?1:Inv2,A(x,y));
				Tmp[j+k+i]=M(flag?1:Inv2,S(x,y));
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	limit=(1<<n);
	for(int i=0;i<=limit-1;i++)
		scanf("%d",&Arr[i]);
	for(int i=0;i<=limit-1;i++)
		scanf("%d",&Brr[i]);
	Copy();
	FwtOr(TmpA,1);FwtOr(TmpB,1);
	for(int i=0;i<=limit-1;i++)TmpA[i]=M(TmpA[i],TmpB[i]);
	FwtOr(TmpA,0);
	for(int i=0;i<=limit-1;i++)printf("%d ",TmpA[i]);
	puts("");
	Copy();
	FwtAnd(TmpA,1);FwtAnd(TmpB,1);
	for(int i=0;i<=limit-1;i++)TmpA[i]=M(TmpA[i],TmpB[i]);
	FwtAnd(TmpA,0);
	for(int i=0;i<=limit-1;i++)printf("%d ",TmpA[i]);
	puts("");
	Copy();
	FwtXor(TmpA,1);FwtXor(TmpB,1);
	for(int i=0;i<=limit-1;i++)TmpA[i]=M(TmpA[i],TmpB[i]);
	FwtXor(TmpA,0);
	for(int i=0;i<=limit-1;i++)printf("%d ",TmpA[i]);
	puts("");
	
	return 0;
}
```

快速莫比乌斯变换

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;

const int Mod=998244353;
const int Inv2=499122177;

inline int A(int a,int b){
	int t=a+b;
	return t>=Mod?t-Mod:t;
}
inline int S(int a,int b){
	int t=a-b;
	return t<0?t+Mod:t;
}
inline int M(int a,int b){
	return 1ll*a*b%Mod;
}

int Arr[131072],Brr[131072];
int TmpA[131072],TmpB[131072];
int limit,n;
inline void Copy(){
	for(int i=0;i<=limit-1;i++)TmpA[i]=Arr[i];
	for(int i=0;i<=limit-1;i++)TmpB[i]=Brr[i];
}

inline void FmtOr(int*Tmp,bool flag){
	for(int i=1;i<limit;i<<=1)
		for(int j=0;j<limit;j++)
			if(j&i)
				Tmp[j]=A(Tmp[j],flag?Tmp[j^i]:Mod-Tmp[j^i]);
}
inline void FmtAnd(int*Tmp,bool flag){
	for(int i=1;i<limit;i<<=1)
		for(int j=0;j<limit;j++)
			if(!(j&i))
				Tmp[j]=A(Tmp[j],flag?Tmp[j^i]:Mod-Tmp[j^i]);
}
inline void FwtXor(int*Tmp,bool flag){
	for(int i=1;i<limit;i<<=1){
		for(int j=0;j<limit;j+=(i<<1)){
			for(int k=0;k<i;k++){
				int x=Tmp[j+k],y=Tmp[j+k+i];
				Tmp[j+k]=M(flag?1:Inv2,A(x,y));
				Tmp[j+k+i]=M(flag?1:Inv2,S(x,y));
			}
		}
	}
}

int main(){
	scanf("%d",&n);
	limit=(1<<n);
	for(int i=0;i<=limit-1;i++)
		scanf("%d",&Arr[i]);
	for(int i=0;i<=limit-1;i++)
		scanf("%d",&Brr[i]);
	Copy();
	FmtOr(TmpA,1);FmtOr(TmpB,1);
	for(int i=0;i<=limit-1;i++)TmpA[i]=M(TmpA[i],TmpB[i]);
	FmtOr(TmpA,0);
	for(int i=0;i<=limit-1;i++)printf("%d ",TmpA[i]);
	puts("");
	Copy();
	FmtAnd(TmpA,1);FmtAnd(TmpB,1);
	for(int i=0;i<=limit-1;i++)TmpA[i]=M(TmpA[i],TmpB[i]);
	FmtAnd(TmpA,0);
	for(int i=0;i<=limit-1;i++)printf("%d ",TmpA[i]);
	puts("");
	Copy();
	FwtXor(TmpA,1);FwtXor(TmpB,1);
	for(int i=0;i<=limit-1;i++)TmpA[i]=M(TmpA[i],TmpB[i]);
	FwtXor(TmpA,0);
	for(int i=0;i<=limit-1;i++)printf("%d ",TmpA[i]);
	puts("");
	
	return 0;
}
```

二维凸包

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;

const int MaxN=110000;

struct Points{
	double x,y;
	Points(double _x=0.0,double _y=0.0):x(_x),y(_y){}
	inline void Reader(){scanf("%lf%lf",&x,&y);}
	inline Points operator+(const Points&p)const{return Points(x+p.x,y+p.y);}
	inline Points operator-(const Points&p)const{return Points(x-p.x,y-p.y);}
};
inline double Cross(const Points&a,const Points&b){return a.x*b.y-a.y*b.x;}
inline double Multi(const Points&a,const Points&b){return a.x*b.x+a.y*b.y;}
inline double GetDist(const Points&a,const Points&b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

inline bool Cmp(const Points&a,const Points&b){return a.x==b.x?a.y<b.y:a.x<b.x;}
Points Now[MaxN];
Points Ans[MaxN];
int top,n;
inline void Andrew(){
	sort(Now+1,Now+n+1,Cmp);
	int tmp;
	tmp=top=1;Ans[1]=Now[1];
	for(int i=1+1;i<=n;i++){
		while(top>tmp&&Cross(Ans[top]-Ans[top-1],Now[i]-Ans[top-1])<=0)
			top--;
		Ans[++top]=Now[i];
	}
	tmp=top;
	for(int i=n-1;i>=1;i--){
		while(top>tmp&&Cross(Ans[top]-Ans[top-1],Now[i]-Ans[top-1])<=0)
			top--;
		Ans[++top]=Now[i];
	}
}
double ans;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		Now[i].Reader();
	if(n<3){puts("0");return 0;}
	Andrew();
	for(int i=1;i<=top-1;i++)
		ans+=GetDist(Ans[i],Ans[i+1]);
	printf("%.2lf\n",ans);
	return 0;
}
```

CRT

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

inline void ExGcd(long long a,long long b,long long&x,long long&y){
	if(b==0){x=1,y=0;return ;}
	ExGcd(b,a%b,y,x);y-=(a/b)*x;
}

inline long long Gcd(long long a,long long b){
	return b==0?a:Gcd(b,a%b);
}

inline long long GetInv(long long a,long long p){
	long long x,y;ExGcd(a,p,x,y);
	return (x%p+p)%p;
}

long long b1=0,m1=1,b2,m2;
int n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld%lld",&m2,&b2);
		long long sp=m1*m2;
		b1=(b1*m2%sp*GetInv(m2,m1)%sp+b2*m1%sp*GetInv(m1,m2)%sp)%sp;
		m1=sp;
	}
	printf("%lld\n",b1);
	return 0;
}
```

Scc

```cpp
```cpp
#include<bits/stdc++.h>

namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
}
using namespace Wql;

namespace Tarjan{
	using namespace std;
	
	int cnt;
	vector<int>Last,To,Next;
	int scc;
	vector<int>Bel;
	vector<vector<int>>Scc;
	int dfn;
	vector<int>Dfn,Low;
	vector<bool>ISt;
	int nn,nm;
	
	void Init(int n,int m){
		Clear(Last);Clear(To);Clear(Next);
		Clear(Bel);Clear(Scc);
		Clear(Dfn);Clear(Low);Clear(ISt);
		cnt=0;
		Last=vector<int>(n+1,-1);
		To=vector<int>(m+1,0);
		Next=vector<int>(m+1,0);
		scc=0;
		Bel=vector<int>(n+1,0);
		Scc=vector<vector<int>>(n+1,vector<int>());
		ISt=vector<bool>(n+1,false);
		dfn=0;
		Dfn=vector<int>(n+1,0);
		Low=vector<int>(n+1,0);
		nn=n;nm=m;
	}
	void Insert(int from,int to){
		To[cnt]=to;
		Next[cnt]=Last[from];Last[from]=cnt++;
	}
	
	int top;
	vector<int>Sta;
	void Tarjan(int from){
		Dfn[from]=Low[from]=++dfn;
		Sta[++top]=from;ISt[from]=true;
		for(int k=Last[from];k!=-1;k=Next[k]){
			int to=To[k];
			if(!Dfn[to]){
				Tarjan(to);
				Low[from]=min(Low[from],Low[to]);
			}
			else if(ISt[to])
				Low[from]=min(Low[from],Dfn[to]);
		}
		if(Dfn[from]==Low[from]){
			scc++;
			int tmp;
			do{
				tmp=Sta[top--];
				Scc[scc].push_back(tmp);
				ISt[tmp]=false;
				Bel[tmp]=scc;
			}while(tmp!=from);
		}
	}
	void Solve(){
		Clear(Sta);
		top=0;
		Sta=vector<int>(nn+1,0);
		for(int i=1;i<=nn;i++)
			if(!Dfn[i])Tarjan(i);
	}
}

namespace TopSort{
	using namespace std;
	int cnt;
	vector<int>Last,To,Next;
	int nn,nm;
	vector<int>Val,Ans,Deg;
	
	void Init(int n,int m){
		Clear(Last);Clear(To);Clear(Next);Clear(Val);
		cnt=0;
		Last=vector<int>(n+1,-1);
		To=vector<int>(m+1,0);
		Next=vector<int>(m+1,0);
		nn=n;nm=m;
		Val=vector<int>(n+1);
		Ans=vector<int>(n+1);
		Deg=vector<int>(n+1);
	}
	void Insert(int from,int to){
		To[cnt]=to;Deg[to]++;
		Next[cnt]=Last[from];Last[from]=cnt++;
	}
	void TopSort(){
		queue<int,list<int>>Q;
		for(int i=1;i<=nn;i++){
			Ans[i]=-0x3f3f3f3f;
			if(Deg[i]==0){
				Ans[i]=Val[i];
				Q.push(i);
			}
		}
		while(!Q.empty()){
			int from=Q.front();Q.pop();
			for(int k=Last[from];k!=-1;k=Next[k]){
				int to=To[k];
				Ans[to]=max(Ans[to],Ans[from]+Val[to]);
				if(--Deg[to]==0)Q.push(to);
			}
		}
	}
}

int Arr[11000];
int Xrr[110000],Yrr[110000];
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	Tarjan::Init(n,m);
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&Xrr[i],&Yrr[i]);
		Tarjan::Insert(Xrr[i],Yrr[i]);
	}
	Tarjan::Solve();
	TopSort::Init(Tarjan::scc,m);
	for(int i=1;i<=Tarjan::scc;i++){
		for(auto x:Tarjan::Scc[i])
			TopSort::Val[i]+=Arr[x];
	}
	for(int i=1;i<=m;i++){
		if(Tarjan::Bel[Xrr[i]]!=Tarjan::Bel[Yrr[i]])
			TopSort::Insert(Tarjan::Bel[Xrr[i]],Tarjan::Bel[Yrr[i]]);
	}
	TopSort::TopSort();
	int ans=0;
	for(int i=1;i<=Tarjan::scc;i++)
		ans=std::max(ans,TopSort::Ans[i]);
	printf("%d\n",ans);
	return 0;
}
```

vdcc

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>

using std::vector;

namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
	template<typename T>
	T Min(T a,T b){return(a<b?a:b);}
	template<typename T>
	T Max(T a,T b){return(a>b?a:b);}
}
using namespace Wql;

namespace Tarjan{
	int nn,nm;
	int dfn;
	vector<int>Dfn,Low;
	int cnt;
	vector<int>Last,To,Next;
	int num;
	vector<bool>Cut;
	void Init(int n,int m){
		cnt=num=dfn=0;
		Clear(Dfn);Clear(Low);
		Clear(Last);Clear(To);Clear(Next);
		Clear(Cut);
		Dfn=vector<int>(n+1,0);
		Low=vector<int>(n+1,0);
		Last=vector<int>(n+1,-1);
		To=vector<int>(m+1,0);
		Next=vector<int>(m+1,0);
		Cut=vector<bool>(n+1,false);
		nn=n;nm=m;
	}
	void Insert(int from,int to){
		To[cnt]=to;
		Next[cnt]=Last[from];Last[from]=cnt++;
	}
	int root;
	void Tarjan(int from){
		Dfn[from]=Low[from]=++dfn;
		int flag=0;
		for(int k=Last[from];k!=-1;k=Next[k]){
			int to=To[k];
			if(!Dfn[to]){
				Tarjan(to);
				Low[from]=Min(Low[from],Low[to]);
				if(Low[to]>=Dfn[from]){
					flag++;
					if(root!=from||flag>1)num+=!Cut[from],Cut[from]=true;//注意可能会多次被判为割点 计数小心
				}
			}
			else
				Low[from]=Min(Low[from],Dfn[to]);
		}
	}
	void Solve(){
		for(int i=1;i<=nn;i++)
			if(!Dfn[i])root=i,Tarjan(i);
		printf("%d\n",num);
		for(int i=1;i<=nn;i++)
			if(Cut[i])printf("%d ",i);
	}
}

int n,m;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	
	scanf("%d%d",&n,&m);
	Tarjan::Init(n,2*m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		Tarjan::Insert(x,y);
		Tarjan::Insert(y,x);
	}
	Tarjan::Solve();
	
	return 0;
}
```

edcc

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>

using std::vector;

namespace Wql{
	template<typename T>
	void Clear(T&x){T y;y.swap(x);}
	template<typename T>
	T Min(T a,T b){return(a<b?a:b);}
	template<typename T>
	T Max(T a,T b){return(a>b?a:b);}
}
using namespace Wql;

namespace Tarjan{
	int nn,nm;
	int dfn;
	vector<int>Dfn,Low;
	int edcc;
	vector<int>Bel;
	vector<vector<int>>Edcc;
	int cnt;
	vector<int>Last,To,Next;
	vector<bool>Bri;
	void Init(int n,int m){
		cnt=edcc=dfn=0;
		Clear(Dfn);Clear(Low);
		Clear(Bel);Clear(Edcc);
		Clear(Last);Clear(To);Clear(Next);
		Clear(Bri);
		Dfn=vector<int>(n+1,0);
		Low=vector<int>(n+1,0);
		Bel=vector<int>(n+1,0);
		Edcc=vector<vector<int>>(n+1);
		Last=vector<int>(n+1,-1);
		To=vector<int>(m+1,0);
		Next=vector<int>(m+1,0);
		Bri=vector<bool>(m+1,false);
		nn=n;nm=m;
	}
	void Insert(int from,int to){
		To[cnt]=to;
		Next[cnt]=Last[from];Last[from]=cnt++;
	}
	void Tarjan(int from,int tk){
		Dfn[from]=Low[from]=++dfn;
		for(int k=Last[from];k!=-1;k=Next[k]){
			int to=To[k];
			if(!Dfn[to]){
				Tarjan(to,k);
				Low[from]=Min(Low[from],Low[to]);
				if(Low[to]>Dfn[from])
					Bri[k]=Bri[k^1]=true;
			}
			else if(k!=(tk^1))
				Low[from]=Min(Low[from],Dfn[to]);
		}
	}
	void Dfs(int from){
		Bel[from]=edcc;
		Edcc[edcc].push_back(from);
		for(int k=Last[from];k!=-1;k=Next[k]){
			if(Bri[k]||Bel[To[k]])continue;
			Dfs(To[k]);
		}
	}
	void Solve(){
		for(int i=1;i<=nn;i++)
			if(!Dfn[i])Tarjan(i,-1);
		for(int i=1;i<=nn;i++)
			if(!Bel[i])edcc++,Dfs(i);
		printf("%d\n",edcc);
		for(int i=1;i<=edcc;i++){
			printf("%d ",(int)Edcc[i].size());
			for(auto x:Edcc[i])
				printf(" %d",x);
			puts("");
		}
	}
}

int n,m;
int main(){
	#ifndef ONLINE_JUDGE
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	
	scanf("%d%d",&n,&m);
	Tarjan::Init(n,2*m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		Tarjan::Insert(x,y);
		Tarjan::Insert(y,x);
	}
	Tarjan::Solve();
	
	return 0;
}
```

整除分块

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n,k;
long long ans;
int main(){
	scanf("%d%d",&n,&k);
	ans=1ll*n*k;
	for(int l=1,r;l<=n;l=r+1){
		if(k/l==0)break;
		r=min(k/(k/l),n);
		ans-=1ll*(k/l)*(l+r)*(r-l+1)/2;
	}
	printf("%lld",ans);
	return 0;
}
```

2-Sat

#  模型
有 $N$ 个变量 $,$ 每个变量只有两种可能的取值 $.$ 在给定 $M$ 个条件 $,$ 每个条件都是对两个变量的取值限制 $.$ 求解 $:$ 是否存在对 $N$ 个变量的合法赋值 $,$ 使 $M$ 个条件均得到满足 $.$

设一个变量 $A_i(1\le i\le N)$ 的两种取值分别是 $A_{i,0}$ 和 $A_{i,1}.$ 在 $2-Sat$ 问题中 $,$ $M$ 个条件都可以转化成统一的形式 $- -$ **若变量 $A_i$ 赋值为 $A_{i,p},$ 则变量 $A_j$ 必须赋值为 $A_{j,q},$ 其中 $p,q\in\{1,0\}.$**

# 判定
1. 建立 $2N$ 个节点的有向图 $,$ 每个变量 $A_i$ 对应两个节点 $,$ 记为 $i,i+N.$
2. 考虑每一个条件 $,$ 形如 $"$ 若变量 $A_i$ 赋值为 $A_{i,p},$ 则变量 $A_j$ 必须赋值为 $A_{j,q},$ 其中 $p,q\in\{1,0\}.$ $"$ 从 $i+p*N$ 到 $j+q*N$ 连一条有向边 $.$
注意 $:$ 上述条件蕴含了它的**逆反命题** $,$ 即 $"$ 若变量 $A_j$ 赋值为 $A_{j,1-q},$ 则变量 $A_i$ 必须赋值为 $A_{i,1-p},$ 其中 $p,q\in\{1,0\}.$ $"$ 若给出的条件不包含它的**逆反命题** $,$ 应该从 $j+(1-q)*N$ 到 $i+(1-p)*N$ 连一条有向边 $.$
3. 用 $Tarjan$ 算法求出当前的有向图的所有强连通分量 $.$
4. 若存在 $i\in [1,N],$ 满足 $i$ 和 $i+N$ 属于同一个强连通分量 $,$ 这说明若变量 $A_i$ 赋值为 $A_{i,p},$ 则变量 $A_i$ 必须赋值为 $A_{i,1-p},$ 显然不可能 $.$
5. 根据 $Tarjan$ 算法的特性 $,$ 编号更小的 $Scc$ 显然处于缩点后拓扑序的末尾 $,$ 同时 $,$ 在一个 $Scc$ 中 $,$ 只要确定了一个变量的取值 $,$ 其他 $Scc$ 的取值也确定了 $,$ 其次 $,$ 在缩点后的 $Dag$ 中 $,$ 如果一个点有出度 $,$ 会使出边的点被强制更新 $,$ 所以我们应该选择**出度为零**的点 $.$ 
综上两 $,$ 如果 $Belong_i>Belong_{i+N}(i\in[1,N])$ $,$ 我们令变量 $A_i$ 赋值成 $A_{i+N}.$
# 构图方法
1.如果有一个变量的取值直接导致无解 $,$ 则把这个取值和另一个取值连**有向边** $,$ 这样如果被迫选择了这个变量 $,$ 直接无解 $.$
2.如果某个变量必须取某个取值 $,$ 那么把另一个取值直接和这个取值连**有向边** $.$

欧拉回路

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;

const int MaxN=1e5+1e4;
const int MaxM=1e6+1e5;

int To[MaxM],Next[MaxM],Last[MaxN],cnt;

inline void Insert(int from,int to){
	To[cnt]=to;
	Next[cnt]=Last[from];Last[from]=cnt++;
}

int Ans[MaxM],tot;
bool Visit[MaxM];
inline void Dfs(int from){
    for(int k=Last[from];k!=-1;k=Last[from]){
        Last[from]=Next[k];
        Dfs(To[k]);
    }
    Ans[++tot]=from;
}
int n,m;
int main(){
	cnt=0;memset(Last,-1,sizeof(Last));
	scanf("%d%d",&n,&m);
	for(register int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		Insert(x,y);Insert(y,x);
	}
	Dfs(1);
	for(int i=tot;i>=1;i--)
		printf("%d\n",Ans[i]);
	return 0;
}
```

整体二分

```cpp
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
template<int MaxN>
struct FanwickTrees{
	long long Data[MaxN];
	int limit;
	FanwickTrees(){
		Init();
	}
	inline void Init(int _limit=0){
		limit=_limit;
		Clear();
	}
	inline void Clear(){
		memset(Data,0,sizeof(int)*(limit+1));
	}
	inline void Modify(int x,long long k){
		while(x<=limit){
			Data[x]+=k;
			x+=(x&-x);
		}
		return;
	}
	inline long long Query(int x,long long k=0){
		while(x>=1){
			k+=Data[x];
			x-=(x&-x);
		}
		return k;
	}
};

const int MaxN=310000;
const int Inf=0x3f3f3f3f;
FanwickTrees<MaxN>TAT;

vector<int>Station[MaxN];

struct Stones{
	int left,right;
	long long val;
	Stones(int _left=0,int _right=0,long long _val=0):
		left(_left),right(_right),val(_val){}
	inline void Reader(){
		scanf("%d%d%lld",&left,&right,&val);
	}
};Stones Stone[MaxN];

int TmpL[MaxN],TmpR[MaxN],Arr[MaxN],Ans[MaxN],Need[MaxN];
inline void Solve(int left,int right,int begin,int end){
	if(begin>end)return;
	if(left==right){
		for(int i=begin;i<=end;i++){
			Ans[Arr[i]]=left;
		}
		return;
	}
	int mid=(left+right)>>1;
	for(int i=left;i<=mid;i++){
		long long val=Stone[i].val;
		if(Stone[i].left<=Stone[i].right){
			TAT.Modify(Stone[i].left,val);
			TAT.Modify(Stone[i].right+1,-val);
		}
		else{
			TAT.Modify(Stone[i].left,val);
			TAT.Modify(1,val);
			TAT.Modify(Stone[i].right+1,-val);
		}
	}
	int ls=0,rs=0;
	for(int i=begin;i<=end;i++){
		long long cnt=0;
		int size=(int)Station[Arr[i]].size();
		for(int j=0;j<size;j++){
			cnt+=TAT.Query(Station[Arr[i]][j]);//差分树状数组数组
			if(cnt>=Need[Arr[i]])break;
		}
		if(cnt<Need[Arr[i]])Need[Arr[i]]-=cnt,TmpR[++rs]=Arr[i];
		else TmpL[++ls]=Arr[i];
	}
	for(int i=left;i<=mid;i++){
		long long val=Stone[i].val;
		if(Stone[i].left<=Stone[i].right){
			TAT.Modify(Stone[i].left,-val);
			TAT.Modify(Stone[i].right+1,val);
		}
		else{
			TAT.Modify(Stone[i].left,-val);
			TAT.Modify(1,-val);
			TAT.Modify(Stone[i].right+1,val);
		}
	}
	for(int i=1;i<=ls;i++)
		Arr[begin+i-1]=TmpL[i];
	for(int i=1;i<=rs;i++)
		Arr[begin+ls+i-1]=TmpR[i];
	Solve(left,mid,begin,begin+ls-1);
	Solve(mid+1,right,begin+ls,end);
}

int n,m,k;
int main(){
	scanf("%d%d",&n,&m);
	TAT.Init(m+10);
	for(int i=1,x;i<=m;i++){
		scanf("%d",&x);
		Station[x].push_back(i);
	}
	for(int i=1;i<=n;i++){
		scanf("%d",&Need[i]);
		Arr[i]=i;
	}
	scanf("%d",&k);
	for(int i=1;i<=k;i++)
		Stone[i].Reader();
	Stone[k+1]=Stones(1,m,Inf);
	Solve(1,k+1,1,n);
	for(int i=1;i<=n;i++)
		if(Ans[i]>k)puts("NIE");
		else printf("%d\n",Ans[i]);
	return 0;
}
```

$Cdq$ 能直接处理的当且仅当操作的维度独立 $,$ 不能改同一个维度的两个东西 $,$ 不然就做不了或者需要变形 $.$

分治的意义是只有 $left\sim mid$ 的修改能对 $mid+1\sim right$ 产生影响 $.$

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int IoSize=1<<10;

char InPut[IoSize];int inpos=IoSize;
inline char GetChar(){
	if(inpos==IoSize)fread(InPut,1,IoSize,stdin),inpos=0;
	return InPut[inpos++];
} 

template<typename datatype>
inline void ReadInt(datatype&s){
	static bool f;f=false;s=0;
	static char c;c=GetChar();
	while(c>57||c<48){if(c=='-')f=true;c=GetChar();}
	while(!(c>57||c<48)){s=(s<<3)+(s<<1)+c-48;c=GetChar();}
	if(f)s=-s;
}
template<typename datatype>
inline void ReadInt(datatype&x,datatype&y){
	ReadInt(x);ReadInt(y);
}
template<typename datatype>
inline void ReadInt(datatype&x,datatype&y,datatype&z){
	ReadInt(x,y);ReadInt(z);
}

template<typename datatype>
inline datatype Max(const datatype&x,const datatype&y){
	return(x>y?x:y);
}
template<typename datatype>
inline datatype Min(const datatype&x,const datatype&y){
	return(x<y?x:y);
}

const int MaxN=1e6+5;
const int IInf=0x3f3f3f3f;

int n,m;

int limit,Data[MaxN]; //树状数组维护区间最值 
inline void Clear(int x){
	for(int i=x;i<=limit;i+=(i&-i))
		if(Data[i]!=-1)Data[i]=-1;
		else break;
	return;
}
inline int Query(int x,int s=-1){
	for(int i=x;i>=1;i-=(i&-i))
		s=Max(s,Data[i]);
	return s;
}
inline void Modify(int x,int s){
	for(int i=x;i<=limit;i+=(i&-i))
		Data[i]=Max(Data[i],s);
	return;
}

struct Questions{
	int x,y,t;
	Questions(int _x=0,int _y=0,int _t=0):
		x(_x),y(_y),t(_t){}
	inline bool operator<(const Questions&q)const{
		return x<q.x;
	}
};Questions Arr[MaxN],Tmp[MaxN],Qry[MaxN];

int Ans[MaxN],top;
inline void CdqSolve(int left,int right){
	if(left==right)return ;
	int mid=(left+right)>>1;
	CdqSolve(left,mid);CdqSolve(mid+1,right);//分治 
	int ls=left,lk=mid,rs=mid+1,rk=right;top=0;
	while(rs<=rk){
		while(ls<=lk&&Arr[ls].x<=Arr[rs].x){
			if(Arr[ls].t==0){
				Modify(Arr[ls].y,Arr[ls].x+Arr[ls].y);//y值 大于 ls 的点 可以用 ls 更新了 
			}
			Tmp[top++]=Arr[ls++];//归并 按 x 值排序 
		}
		if(Arr[rs].t!=0){//ls 不用处理询问,在前一次递归已经求了,而且 rs 不可能更新 ls 
			int t=Query(Arr[rs].y);
			if(t!=-1)Ans[Arr[rs].t]=Min(Ans[Arr[rs].t],Arr[rs].x+Arr[rs].y-t);
		} 
		Tmp[top++]=Arr[rs++];
	}
	for(int i=left;i<=lk;i++)
		if(Arr[i].t==0)Clear(Arr[i].y);//删光他 
	while(ls<=lk)Tmp[top++]=Arr[ls++];
	while(rs<=rk)Tmp[top++]=Arr[rs++];
	for(int i=left;i<=right;i++)Arr[i]=Tmp[i-left];
}
int cnt;
inline void Init(int direct){
	int maxx=0,maxy=0;cnt=0;
	for(int i=1;i<=n+m;i++){
		if(direct==1)Qry[i].x=limit-Qry[i].x;
		else if(direct==2)Qry[i].y=limit-Qry[i].y;
		
		if(Qry[i].t!=0){
			maxx=Max(maxx,Qry[i].x);
			maxy=Max(maxy,Qry[i].y);
		}
	}
	for(int i=1;i<=n+m;i++)
		if(Qry[i].x<=maxx&&Qry[i].y<=maxy)
			Arr[++cnt]=Qry[i];
} 

int main(){
	//freopen("Test.in","r",stdin);
	ReadInt(n,m);
	for(int i=1;i<=n;i++){
		ReadInt(Qry[i].x,Qry[i].y);
		Qry[i].x++;Qry[i].y++;
		limit=Max(limit,Qry[i].x);
		limit=Max(limit,Qry[i].y);
	}
	memset(Ans,0x3f,sizeof(Ans));
	
	Ans[0]=0;
	for(int i=n+1,t;i<=n+m;i++){
		ReadInt(t,Qry[i].x,Qry[i].y);
		Qry[i].x++;Qry[i].y++;
		if(t==2)Qry[i].t=++Ans[0];
		limit=Max(limit,Qry[i].x);
		limit=Max(limit,Qry[i].y);
	}
	limit++;
	
	memset(Data,-1,sizeof(Data));
	Init(0);CdqSolve(1,cnt);
	Init(1);CdqSolve(1,cnt);
	Init(2);CdqSolve(1,cnt);
	Init(1);CdqSolve(1,cnt);
	
	for(int i=1;i<=Ans[0];i++)
		printf("%d\n",Ans[i]);
	return 0;
}
```

莫队

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>

const int MaxN=51000;

inline int Gcd(int a,int b){return b==0?a:Gcd(b,a%b);}

int size;
struct Opts{
	int l,r,id;
	inline bool operator<(const Opts&o){return l/size==o.l/size?r<o.r:l<o.l;}
};Opts Q[MaxN];
int Ans[MaxN][2];

int A,B,len,Cnt[MaxN],Arr[MaxN];
inline void Add(int pos){
	A+=Cnt[Arr[pos]];
	Cnt[Arr[pos]]++;
	B+=len;
	len++;
}
inline void Del(int pos){
	Cnt[Arr[pos]]--;
	A-=Cnt[Arr[pos]];
	len--;
	B-=len;
}

int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&Arr[i]);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&Q[i].l,&Q[i].r),Q[i].id=i;
	size=n/sqrt(m);//最优块长
	std::sort(Q+1,Q+m+1);//排序询问
	int l=1,r=0;//只要保证是个空区间就行
	for(int i=1;i<=m;i++){
		if(Q[i].l==Q[i].r){
			Ans[Q[i].id][0]=0;
			Ans[Q[i].id][1]=1;
		}
		while(l>Q[i].l)Add(--l);
		while(r<Q[i].r)Add(++r);
		while(l<Q[i].l)Del(l++);
		while(r>Q[i].r)Del(r--);//先加后减保证区间长度不为负数
		int g=Gcd(A,B);
		Ans[Q[i].id][0]=A/g;
		Ans[Q[i].id][1]=B/g;
	}
	for(int i=1;i<=m;i++)
		printf("%d/%d\n",Ans[i][0],Ans[i][1]);
	return 0;
}

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>

using std::sort;

template<typename datatype>
inline void Swap(datatype&x,datatype&y){datatype t=x;x=y;y=t;}

namespace Chx{
	const int MaxN=110000;
	const int MaxM=210000;
	
	int Last[MaxN],cm;
	int To[MaxM],Next[MaxM];
	inline void Insert(int from,int to){
		To[cm]=to;
		Next[cm]=Last[from];Last[from]=cm++;
	}
	
	int Sta[MaxN],top;
	int Bel[MaxN],tot,size;
	
	int Dad[MaxN][18],Dep[MaxN];
	inline void Dfs(int from){
		int tmp=top;
		for(int k=Last[from];k!=-1;k=Next[k]){
			if(To[k]==Dad[from][0])continue;
			Dep[To[k]]=Dep[from]+1;
			Dad[To[k]][0]=from;
			Dfs(To[k]);
			if(top-tmp>=size){
				++tot;
				while(top!=tmp)Bel[Sta[top--]]=tot;
			}
		}
		Sta[++top]=from;
	}
	
	struct Opts{
		int a,b,t,id;
		inline bool operator<(const Opts&o)const{return Bel[a]==Bel[o.a]?(Bel[b]==Bel[o.b]?t<o.t:Bel[b]<Bel[o.b]):Bel[a]<Bel[o.a];}
	};Opts Q[MaxN];int qcnt;
	struct Changes{
		int pos,val;
	};Changes C[MaxN];int ccnt;
	
	bool Visit[MaxN];
	int Num[MaxN],Arr[MaxN];
	long long Ans[MaxN],Vi[MaxN],Wi[MaxN],ans;
	inline void Reverse(int x){
		if(Visit[x])ans-=Vi[Arr[x]]*Wi[Num[Arr[x]]--];
		else ans+=Vi[Arr[x]]*Wi[++Num[Arr[x]]];
		Visit[x]^=true;
	}
	inline int GetLca(int x,int y){
		if(Dep[x]<Dep[y])Swap(x,y);
		for(int i=17;i>=0;i--)
			if(Dep[Dad[x][i]]>=Dep[y])
				x=Dad[x][i];
		if(x==y)return x;
		for(int i=17;i>=0;i--)
			if(Dad[x][i]!=Dad[y][i])
				x=Dad[x][i],y=Dad[y][i];
		return Dad[x][0];
	}
	inline void PathModify(int x,int y){
		if(Dep[x]<Dep[y])Swap(x,y);
		while(Dep[x]>Dep[y]){
			Reverse(x);
			x=Dad[x][0];
		}
		while(x!=y){
			Reverse(x);
			Reverse(y);
			x=Dad[x][0];
			y=Dad[y][0];
		}
	}
	inline void Modify(int x){
		if(Visit[C[x].pos]){
			Reverse(C[x].pos);
			Swap(Arr[C[x].pos],C[x].val);
			Reverse(C[x].pos);
		}
		else Swap(Arr[C[x].pos],C[x].val);
	}
	
	int n,m,q;
	inline void Main(){
		memset(Last,-1,sizeof(Last));
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=m;i++)scanf("%lld",&Vi[i]);
		for(int j=1;j<=n;j++)scanf("%lld",&Wi[j]);
		for(int i=1;i<=n-1;i++){
			int x,y;scanf("%d%d",&x,&y);
			Insert(x,y);Insert(y,x);
		}
		for(int i=1;i<=n;i++)scanf("%d",&Arr[i]);
		for(int i=1;i<=q;i++){
			int opt,x,y;scanf("%d%d%d",&opt,&x,&y);
			if(opt==0){
				ccnt++;
				C[ccnt]={x,y};
			}
			else{
				qcnt++;
				Q[qcnt]={x,y,ccnt,qcnt};
			}
		}
		size=ceil(pow(n,2.0/3.0));
		Dep[1]=1;
		Dfs(1);
		if(top){
		    tot++;
		    while(top)Bel[Sta[top--]]=tot;
		}
		for(int i=1;i<=17;i++)
			for(int j=1;j<=n;j++)
				Dad[j][i]=Dad[Dad[j][i-1]][i-1];
		sort(Q+1,Q+qcnt+1);
		
		int a=1,b=1,now=0;
		for(int i=1;i<=qcnt;i++){
			PathModify(a,Q[i].a);
			PathModify(b,Q[i].b);
			a=Q[i].a;
			b=Q[i].b;
			while(now<Q[i].t)Modify(++now);
			while(now>Q[i].t)Modify(now--);
			int lca=GetLca(Q[i].a,Q[i].b);
			Reverse(lca);
			Ans[Q[i].id]=ans;
			Reverse(lca);
		}
		for(int i=1;i<=qcnt;i++)
			printf("%lld\n",Ans[i]);
	}
}

int main(){
	Chx::Main();
	return 0;
}

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<ctime>

const int MaxN=200000;
int size;
struct Opts{
	int l,r,t,id;
	inline bool operator<(const Opts&o){
		return l/size==o.l/size?(r/size==o.r/size?t<o.t:r<o.r):l<o.l;
	}
};Opts Q[MaxN];int qcnt;
struct Changes{
	int pos,val;
};Changes C[MaxN];int ccnt;
int Arr[MaxN];

const int MaxS=1100000;
int Num[MaxS],ans;
inline void Add(int c){
	if(Num[c]==0)ans++;
	Num[c]++;
}
inline void Del(int c){
	Num[c]--;
	if(Num[c]==0)ans--;
}
inline void Modify(int i,int j){
	if(Q[i].l<=C[j].pos&&C[j].pos<=Q[i].r){
		Del(Arr[C[j].pos]);
		Add(C[j].val);
	}
	std::swap(Arr[C[j].pos],C[j].val);//下次修改一定是撤回
}

char O[10];int n,m,Ans[MaxN];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&Arr[i]);
	for(int i=1;i<=m;i++){
		scanf("%s",O);
		if(O[0]=='R'){
			int x,y;scanf("%d%d",&x,&y);++ccnt;
			C[ccnt]={x,y};
		}
		else{
			int x,y;scanf("%d%d",&x,&y);++qcnt;
			Q[qcnt]={x,y,ccnt,qcnt};
		}
	}
	size=pow(n,2.0/3.0);//最优块长
	std::sort(Q+1,Q+qcnt+1);
	int l=2,r=1,now=0;
	for(int i=1;i<=qcnt;i++){
		while(l>Q[i].l)Add(Arr[--l]);
		while(r<Q[i].r)Add(Arr[++r]);
		while(l<Q[i].l)Del(Arr[l++]);
		while(r>Q[i].r)Del(Arr[r--]);
		while(now<Q[i].t)Modify(i,++now);//看时间线判断是修改还是撤回
		while(now>Q[i].t)Modify(i,now--);
		Ans[Q[i].id]=ans;
	}
	for(int i=1;i<=qcnt;i++)
		printf("%d\n",Ans[i]);
	return 0;
}

#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>

const int MaxN=110000;

int size;
struct Querys{
	int l,r,id;
	inline bool operator<(const Querys&q)const{
		return l/size==q.l/size?r<q.r:l<q.l;
	}
};Querys Q[MaxN];

int Arr[MaxN],Num[MaxN],Copy[MaxN],tot;
long long ans,tmp,Ans[MaxN];
inline void Add(int t){
	Num[t]++;
	ans=std::max(ans,1ll*Num[t]*Copy[t]);
}

int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&Arr[i]),Copy[++tot]=Arr[i];
	std::sort(Copy+1,Copy+tot+1);
	tot=std::unique(Copy+1,Copy+tot+1)-Copy-1;
	
	for(int i=1;i<=n;i++)
		Arr[i]=std::lower_bound(Copy+1,Copy+tot+1,Arr[i])-Copy;
	
	size=n/sqrt(m)+1;
	
	for(int i=1;i<=m;i++){
		scanf("%d%d",&Q[i].l,&Q[i].r);
		Q[i].id=i;
		if(Q[i].l/size==Q[i].r/size){//同块暴力
			for(int j=Q[i].l;j<=Q[i].r;j++){
				++Num[Arr[j]];
				Ans[i]=std::max(Ans[i],1ll*Num[Arr[j]]*Copy[Arr[j]]);
			}
			for(int j=Q[i].l;j<=Q[i].r;j++)--Num[Arr[j]];
		}
	}
	
	std::sort(Q+1,Q+m+1);
	
	int bl=-1,l,r;
	for(int i=1;i<=m;i++){
		if(Q[i].l/size==Q[i].r/size)continue;
		if(Q[i].l/size!=bl){//换块归位
			ans=0;
			bl=Q[i].l/size;
			memset(Num,0,sizeof(Num));
			l=(bl+1)*size;
			r=(bl+1)*size-1;//右端点递增
		}
		while(r<Q[i].r)Add(Arr[++r]);//右端点递增
		tmp=ans;//记录以备撤销
		while(l>Q[i].l)Add(Arr[--l]);//左端点增加
		Ans[Q[i].id]=ans;
		while(l<(bl+1)*size)--Num[Arr[l++]];//回滚
		ans=tmp;//撤销
	}
	
	for(int i=1;i<=m;i++)
		printf("%lld\n",Ans[i]);
	
	return 0;
}
```

