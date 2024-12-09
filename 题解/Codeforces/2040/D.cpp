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

const int MaxN=210000;

vector<int>To[MaxN];

vector<int>Un;

int now;
int Dad[MaxN];
int Ans[MaxN];

void Bfs(){
	std::queue<int>Q;
	
	Q.push(1);Dad[1]=0;
	Ans[1]=2;now=4;Clear(Un);
	while(!Q.empty()){
		int from=Q.front(),dad=Dad[from];
		Q.pop();
		
		for(auto to:To[from]){
			if(to==dad)continue;
			Dad[to]=from;
			bool flag=false;
			Q.push(to);
			for(auto t=Un.begin();t!=Un.end();t++){
				if(abs(Ans[from]-(*t))!=2){
					Ans[to]=(*t);
					t=Un.erase(t);
					flag=true;
					break;
				}
			}
			if(flag)continue;
			
			if(abs(Ans[from]-now)==2){
				Un.push_back(now);
				now+=2;
				Ans[to]=now;
			}
			else Ans[to]=now;
			now+=2;
		}
	}
}

int n;
int Is[MaxN];
void Main(int Case){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		Clear(To[i]);
		Is[i]=0;
	}
	for(int i=1;i<=n-1;i++){
		int x,y;scanf("%d%d",&x,&y);
		To[x].push_back(y);
		To[y].push_back(x);
	}
	Bfs();
	int tmp=0;
	for(int i=1;i<=n;i++){
		if(Ans[i]>2*n){
			if(!Is[Dad[i]])Ans[i]=Ans[Dad[i]]-1,Is[Dad[i]]=true;
			else Ans[i]=Ans[Dad[i]]+1;
		}
		printf("%d ",Ans[i]);
	}
	//if(tmp>1)while (true);
	
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