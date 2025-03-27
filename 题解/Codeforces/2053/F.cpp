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

const int MaxN=610000;

struct ModifyTable{
	ll tag,ma,adtag;
	ll Arr[MaxN];//Arr[i]+tag=Real[i]
	void AllAdd(ll val){
		adtag+=val;
		ma+=val;
		tag+=val;
	}
	void AllUp(ll val){
		tag=std::max(tag,val);
		if(ma<tag)ma=tag;
	}
	void Add(int pos,ll val){
		if(Arr[pos]+adtag<tag)Arr[pos]=tag-adtag;
		Arr[pos]+=val;
		if(ma<Arr[pos]+adtag){
			ma=Arr[pos]+adtag;
		}
	}
	void Modify(int pos,ll val){
		if(Arr[pos]+adtag<tag)Arr[pos]=tag-adtag;
		Arr[pos]=std::max(val,Arr[pos]+adtag)-adtag;
		if(ma<Arr[pos]+adtag){
			ma=Arr[pos]+adtag;
		}
	}
};ModifyTable MT;

int n,m,k;
ll Kos[MaxN];
void Main(int Case){
	scanf("%d%d%d",&n,&m,&k);
	
	vector<vector<int>>Arr;
	Arr.resize(n+10);
	std::for_each(Arr.begin(),Arr.end(),[&](vector<int>&x){x.resize(m+10);});
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&Arr[i][j]);
	
	ll ans=0;
	for(int i=1;i<=n-1;i++){//nmlogm
		std::map<int,ll>M;
		for(int j=1;j<=m;j++)
			M[Arr[i][j]]++;
		for(int j=1;j<=m;j++)
			if(Arr[i+1][j]!=-1)ans+=M[Arr[i+1][j]];
		Kos[i]=M[-1];
	}
	Kos[n]=0;
	for(int i=1;i<=m;i++)Kos[n]+=(Arr[n][i]==-1);
	
	MT.ma=ans;MT.tag=0;MT.adtag=0;
	for(int i=1;i<=k;i++)
		MT.Arr[i]=ans;
	
	for(int i=1;i<=n;i++){
		std::map<int,ll>M;
		for(int j=1;j<=m;j++){
			if(i-1>=1)M[Arr[i-1][j]]++;
			if(i+1<=n)M[Arr[i+1][j]]++;
		}
		
		ll t=MT.ma;
		MT.AllAdd(Kos[i]*Kos[i-1]);
		MT.AllUp(t);
		
		for(auto t:M){
			int x=t.first;
			if(x==-1)continue;
			MT.Add(t.first,M[x]*Kos[i]);
		}
	}
	
	printf("%lld\n",MT.ma);
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