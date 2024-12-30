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

const int Mod=998244353;
const int Inf=1e9;
int Add(int x,int y){
	return x+y>=Mod?x+y-Mod:x+y;
}

int Dp1[64],Dp2[64],F1[64],F2[64];//最小步数,方案数
int Sum[110000][51],Arr[110000];
int n,q;
void Main(int Case){
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
		Sum[i][Arr[i]]++;
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<=50;j++)
			Sum[i][j]+=Sum[i-1][j];
	
	for(int i=1;i<=q;i++){
		int l,r;
		scanf("%d%d",&l,&r);
		if(Sum[r][0]-Sum[l-1][0]){
			printf("%d %d\n",r-l,Sum[r][0]-Sum[l-1][0]);
		}
		else{
			int ans=0;bool flag=false;
			for(int j=1;j<=50;j++){
				int t=Sum[r][j]-Sum[l-1][j];
				if(t>1)flag=true;
				ans=(ans+1ll*t*(t-1)/2%Mod)%Mod;
			}
			if(flag==0){
				for(int j=0;j<=63;j++)
					Dp1[j]=Inf,Dp2[j]=0;
				for(int j=l;j<=r;j++){
					for(int k=0;k<=63;k++)
						F1[k]=Dp1[k],F2[k]=Dp2[k];
					for(int k=0;k<=63;k++){
						if(F1[k^Arr[j]]>Dp1[k]+1){
							F1[k^Arr[j]]=Dp1[k]+1;
							F2[k^Arr[j]]=Dp2[k];
						}
						else if(F1[k^Arr[j]]==Dp1[k]+1){
							F2[k^Arr[j]]=Add(F2[k^Arr[j]],Dp2[k]);
						}
					}
					if(F1[Arr[j]]==1)F2[Arr[j]]=Add(F2[Arr[j]],1);
					else F1[Arr[j]]=1,F2[Arr[j]]=1;
					for(int k=0;k<=63;k++)
						Dp1[k]=F1[k],Dp2[k]=F2[k];
				}
				if(Dp1[0]==Inf)printf("-1\n");
				else printf("%d %d\n",r-l+1-Dp1[0],Dp2[0]);
			}
			else printf("%d %d\n",r-l-1,ans);
		}
	}
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	int Task=1;
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	return 0;
}