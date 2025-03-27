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



template<typename T>
void DebugP(T x){
	std::cout<<x<<'\n';
	fflush(stdout);
}
template<typename...Args>
void DebugP(Args...x){
	(DebugP(x),...);
}

#define lb(x) (x&-x)
struct FanwickTrees{
	vector<ll>Da;
	vector<pair<int,ll>>Sa;
	int tp,L;
	void Init(int _tp,int _L){
		tp=_tp;L=_L;
		Clear(Da);Da.resize(L+10);
		Clear(Sa);
	}
	void Add(int x,ll v,bool f=false){
		if(!f)Sa.push_back({x,v});
		x+=tp;
		for(;x<=L;x+=lb(x))
			Da[x]+=v;
	}
	ll Qry(int x,ll v=0){
		x+=tp;
		for(;x>=1;x-=lb(x))
			v+=Da[x];
		return v;
	}
	void Roll(int top){
		while(top!=Sa.size()){
			Add(Sa.back().fi,-Sa.back().se,true);
			Sa.pop_back();
		}
	}
};FanwickTrees T1,T2;

void Main(int Case){
	int n;
	scanf("%d",&n);
	
	vector<vector<int>>To(n+10);
	T1.Init(n+1,3*n);
	T2.Init(n+1,3*n);
	for(int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		To[x].push_back(y);To[y].push_back(x);
	}
	
	vector<int>Siz(n+10),Ma(n+10);
	ll anss=0;
	std::function<void(int,int)>Dfs=[&](int from,int dad){
		Siz[from]=1;Ma[from]=0;
		for(int to:To[from]){
			if(to==dad)continue;
			Dfs(to,from);
			Siz[from]+=Siz[to];
			if(Ma[from]==0||Siz[Ma[from]]<Siz[to])
				Ma[from]=to;
		}
		anss+=Siz[from]-1;
	};
	Dfs(1,0);
	//2*Min({a,b}) Min({a,b})
	int nowpos=0;ll ans=0;
	std::function<void(int,int,int)>Dfs3=[&](int from,int dad,int dis){
		ans+=T1.Qry(dis-nowpos)+1ll*nowpos*T2.Qry(dis-nowpos);
		ans+=(T2.Qry(n)-T2.Qry(dis-nowpos))*dis;
		for(auto to:To[from]){
			if(to==dad)continue;
			Dfs3(to,from,dis+1);
		}
	};
	std::function<void(int,int,int)>Dfs4=[&](int from,int dad,int dis){
		T1.Add(dis-nowpos,dis-nowpos);
		T2.Add(dis-nowpos,1);
		for(auto to:To[from]){
			if(to==dad)continue;
			Dfs4(to,from,dis+1);
		}
	};
	std::function<void(int,int,bool)>Dfs1=[&](int from,int dad,bool flag){
		int top1=T1.Sa.size();
		int top2=T2.Sa.size();
		for(auto to:To[from]){
			if(to==dad||to==Ma[from])continue;
			Dfs1(to,from,false);
		}
		if(Ma[from]){//重儿子储存信息
			Dfs1(Ma[from],from,true);
			nowpos++;
		}
		for(auto to:To[from]){
			if(to==dad||to==Ma[from])continue;
			Dfs3(to,from,1);//计算轻儿子
			Dfs4(to,from,1);
		}
		T1.Add(-nowpos,-nowpos);
		T2.Add(-nowpos,1);
		if(!flag){
			T1.Roll(top1);
			T2.Roll(top2);
			//Roll Back
		}
	};
	Dfs1(1,1,false);
	printf("%lld\n",2*ans+anss-1ll*n*(n-1)/2);
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
/*
1 1-> (0 2) 1

不存在0的情况

2 0-> (2 2) -1

全加后减的思路

先给轻儿子全部放进去,

然后重儿子统计自己为min的答案

然后重儿子放进去

轻儿子删除自己
*/