### Basic

```cpp
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f);
```

`std::setw(n)`:设置字段宽度(类似于 `printf` 中的宽度).

`std::setfill(c)`:设置填充字符(默认填充空格).

`std::setprecision(n)`:设置小数的精度(类似于 `%.nf`).

`std::fixed`:设置固定小数点格式输出.

`std::scientific`:设置科学计数法格式输出.

`std::left`:设置左对齐输出.

`std::right`:设置右对齐输出.

`std::boolalpha` 和 std::`noboolalpha`:分别表示以 "true"/"false" 或数字(0 和 1)形式输出布尔值.

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