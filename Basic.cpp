#include<bits/stdc++.h>
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

template<typename... Args>
std::istream& InPut(Args&... x) {
    return (cin>>...>>x); // fold expression for multiple arguments
}
template<typename...Args>
std::ostream& OutPut(Args&... x){
	return (cout<<...<<x);
}
template<typename...Args>
std::ostream& ErrPut(Args&...x){
	return (std::cerr<<...<<x);
}

void Main(int Case,bool flag=false){
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	freopen("Err.txt","w",stderr);
	#endif
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);std::cout.tie(nullptr);
	int Task=1;cin>>Task;
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}