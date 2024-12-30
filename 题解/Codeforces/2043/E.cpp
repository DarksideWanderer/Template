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

const int MaxN=3100*31*2;

vector<int>To[MaxN];

int Gb(int x,int b){return (x>>b)&1;}

int n,m;

int Enc(int i,int b,bool r){
	if(!r)return (i-1)*31+b;
	else return (i+n-1)*31+b;
}

bool Is[MaxN];

void Main(int Case){
	scanf("%d%d",&n,&m);
	
	int SI=Enc(m,30,1);
	for(int i=0;i<=SI;i++)
		Clear(To[i]),Is[i]=0;
	
	vector<vector<int>>Arr,Brr;
	For_each([&](vector<vector<int>>&x){
		x.resize(n+10);
		std::for_each(x.begin(),x.end(),[&](vector<int>&y){
			y.resize(m+10);
		});
	},Arr,Brr);
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&Arr[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&Brr[i][j]);
	for(int i=1;i<=n;i++)//And
		for(int j=0;j<=30;j++)
			for(int k=1;k<=m;k++)
				if(Gb(Brr[i][k],j))To[Enc(i,j,0)].push_back(Enc(k,j,1));
	for(int i=1;i<=m;i++)//Or
		for(int j=0;j<=30;j++)
			for(int k=1;k<=n;k++)
				if(!Gb(Brr[k][i],j))To[Enc(i,j,1)].push_back(Enc(k,j,0));
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			for(int k=0;k<=30;k++){
				if(Gb(Arr[i][j],k)==0&&Gb(Brr[i][j],k)==1)Is[Enc(j,k,1)]=true;
				if(Gb(Arr[i][j],k)==1&&Gb(Brr[i][j],k)==0)Is[Enc(i,k,0)]=true;
			}
		}
	}
	
	vector<int>Dfn,Low,InSta,Sta;
	For_each([&](vector<int>&x){x.resize(SI+10);},Dfn,Low,InSta,Sta);
	int dfn=0,flag=0,top=0;
	std::function<void(int)>Tarjan=[&](int from){
		InSta[from]=true;Sta[++top]=from;
		Dfn[from]=Low[from]=++dfn;
		for(auto to:To[from]){
			if(!Dfn[to]){
				Tarjan(to);
				Low[from]=std::min(Low[from],Low[to]);
			}
			else if(InSta[to])
				Low[from]=std::min(Low[from],Dfn[to]);
		}
		if(Low[from]==Dfn[from]){
			int now;
			do{
				now=Sta[top--];
				InSta[now]=false;
			}while(now!=from);
		}
		else flag=true;
	};
	
	for(int i=0;i<=SI;i++)
		if(Is[i]&&!Dfn[i])Tarjan(i);
	if(flag)puts("No");
	else puts("Yes");
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}