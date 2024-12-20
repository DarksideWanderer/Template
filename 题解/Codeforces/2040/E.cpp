#include<bits/stdc++.h>
//#define Debug
using std::vector;
using std::pair;
using std::array;
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

const int MaxN=31000;
const int Mod=998244353;

array<vector<int>,MaxN>To;
array<int,MaxN>Deg;
array<int,MaxN>Dad;

void Insert(int from,int to){
	To[from].push_back(to);
	Deg[from]++;
}


void Main(int Case){
	int n,q;
	scanf("%d%d",&n,&q);
	
	for(int i=1;i<=n;i++){
		Deg[i]=0;
		Clear(To[i]);
	}
	
	for(int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		Insert(x,y);
		Insert(y,x);
	}
	
	std::function<void(int,int)>Init=[&](int from,int dad){
		Dad[from]=dad;
		for(auto to:To[from])
			if(to!=dad)Init(to,from);
	};
	Init(1,0);
	
	for(int i=1;i<=q;i++){
		int p,t;
		scanf("%d%d",&p,&t);
		std::priority_queue<int>Q;
		int ans=0;
		while(p!=1){
			if(Dad[p]==1){
				ans++;
				p=Dad[p];
			}
			else{
				Q.push(2*(Deg[Dad[p]]-1));
				ans=(ans+2*(Deg[Dad[p]]))%Mod;
				p=Dad[Dad[p]];
			}
		}
		for(int j=1;j<=t;j++)
			if(Q.size())ans=(ans+Mod-Q.top())%Mod,Q.pop();
			else break;
		printf("%d\n",ans);
	}
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