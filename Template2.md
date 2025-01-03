### Basic

```cpp
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f);
```

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
//std::uniform_int_distribution<int>U(Down,Up);

void Main(int Case){
	
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
```

### Math

积性函数可以使用 $O(\sqrt{n})$ 或者 $O(n)$ 的做法来做.

$$
\varphi(x*p)=\begin{cases}
\varphi(x)*p &x\mod p=0\\
\varphi(x)*(p-1) &x\mod p \not=0 
\end{cases} 
$$

$$
\mu(x*p)=\begin{cases}
\mu(x)*(-1)&x\mod p \not=0\\
0 &otherwise
\end{cases}
$$