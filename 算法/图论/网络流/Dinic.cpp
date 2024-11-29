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

template<typename T>
struct Inf{const static T val;};

template<>
const int Inf<int>::val=[](){return 1000000000;}();

struct Graphs{
	vector<int>Last;
	vector<int>To;
	vector<int>Next;
};

template<typename fty>
struct FlowGraphs:Graphs{
	int source,sink;
	vector<fty>Flow;
};

template<typename fty,typename cty>
struct CostFlowGraphs:FlowGraphs<fty>{
	vector<cty>Cost;
};

template<typename fty,typename cty,typename gty>
struct Dinics{
	gty*G;
	
	std::vector<int>High;
	bool Bfs(){
		std::queue<int>Q;
		std::fill(High.begin(),High.end(),0);
		High[(*G).sink]=1;
		while(!Q.empty()){
			auto from=Q.front();
			for(int k=(*G).Last[from];k!=-1;k=(*G).Next[k]){
				if((*G).Flow[k^1]&&High[(*G).To[k]]==0){
					High[(*G).To[k]]=High[from]+1;
					if((*G).To[k]==source)return true;
				}
			}
		}
		return false;
	}
	
	std::vector<int>Cur;
	int Dfs(int from,fty flow){
		std::function<int(int,int)>Solve(int from,fty flow){
			if(flow==sink)return flow;
			fty used=0,test;
			for(int k=Cur[from];k!=-1;k=(*G).Next[k]){
				
				if((*G).Flow[k]&&used<flow&&High[])
			}
		}
	}
	
};

CostFlowGraphs<int,int>G;

Dinics<int,int,CostFlowGraphs<int,int>>D;

void Main(){
	D.G=&G;
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;
	for(int Case=1;Case<=Task;Case++){
		Main();
	}
	return 0;
}