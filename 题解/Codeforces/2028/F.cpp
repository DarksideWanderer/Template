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

const std::bitset<10001>I=[](){
	std::bitset<10001>t;
	t|=1;
	return t;
}();
const std::bitset<10001>O;

template<const int L>
void BitsetPrint(std::bitset<L>B,int len,char *s=nullptr){
	if(s!=nullptr){
		printf("%s",s);
	}
	for(int i=0;i<=len;i++){
		putchar(B[i]+48);
	}
	puts("");
}

int n,m,Arr[210000];
void Main(int Case){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	std::list<pair<std::bitset<10001>,ll>>L;
	L.push_back({I,1});
	auto F=O;
	for(int i=1;i<=n;i++){
		std::bitset<10001>S=O;
		if(Arr[i]==0){
			for(auto it=L.begin();it!=L.end();it++){
				S|=(*it).first;
			}
			L.clear();
			L.push_back({S|F,0});
			L.push_back({S|F,1});F=O;
		}
		else if(Arr[i]==1){
			for(auto p=L.begin();p!=L.end();p++)
				if((*p).se==1)(*p).first=((*p).first<<1)|(*p).first;
		}
		else{
			for(auto it=L.begin();it!=L.end();){
				(*it).second*=Arr[i];
				if((*it).second>m)F|=(*it).first,it=L.erase(it);
				else it++;
			}
			for(auto it=L.begin();it!=L.end();it++){
				S|=(*it).first<<(*it).second;
			}
			L.push_back({S,1});
		}
		#ifdef Debug
		printf("%d:\n",i);
		for(auto t:L)
			BitsetPrint<10001>(t.first,5);
		#endif
	}
	auto p=L.end();
	p--;
	if((*p).first[m])puts("Yes");
	else puts("No");
}

void Print(int Case){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	if(Case==176){
		printf("%d %d\n",n,m);
		for(int i=1;i<=n;i++){
			printf("%d ",Arr[i]);
		}
		puts("");
	}
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		if(Task==1000000){
			Print(Case);
		}
		else{
			Main(Case);
		}
	}
	return 0;
}