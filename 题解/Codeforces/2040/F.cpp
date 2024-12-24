#include<bits/stdc++.h>

using std::array,std::vector,std::set,std::bitset;
#define ll long long

const int Mod=998244353;
const int MaxN=3010000;

array<int,MaxN>F,IF,I;

int Pow(int a,int b){
	int r=1;
	while(b){
		if(b&1){r=1ll*r*a%Mod;}
		a=1ll*a*a%Mod;b>>=1;
	}
	return r;
}
int Inv(int a){return Pow(a,Mod-2);}

ll Gcd(ll a,ll b){
	return (a==0||b==0)?a+b:Gcd(b,a%b);
}
ll Lcm(ll a,ll b){
	return a*b/Gcd(a,b);
}

vector<int>Pri;
array<int,MaxN>Phi;
std::bitset<MaxN>Vis;
void Init(){
	const int L=3000000;
	F[0]=1;
	for(int i=1;i<=L;i++)F[i]=1ll*F[i-1]*i%Mod;
	IF[L]=Inv(F[L]);
	for(int i=L-1;i>=0;i--)IF[i]=1ll*IF[i+1]*(i+1)%Mod;
	for(int i=1;i<=L;i++)I[i]=1ll*IF[i]*F[i-1]%Mod;
	Vis[1]=true;
	Phi[1]=1;
	for(int i=2;i<=L;i++){
		if(!Vis[i]){
			Pri.push_back(i);
			Phi[i]=i-1;
		}
		for(auto j:Pri){
			if(i*j>L)break;
			Vis[i*j]=true;
			if(i%j==0){
				Phi[i*j]=1ll*Phi[i]*j%Mod;
				break;
			}
			Phi[i*j]=1ll*Phi[i]*(j-1)%Mod;
		}
	}
}

array<int,MaxN>Arr;
int a,b,c,k;
int Calc(int t){
	int l=0;
	for(int i=1;i<=k;i++)
		l+=Arr[i]/t;
	int ans=F[l];
	for(int i=1;i<=k;i++)
		ans=1ll*ans*IF[Arr[i]/t]%Mod;
	return ans;
}

array<int,MaxN>Ans;

void Main(int Case){
	scanf("%d%d%d%d",&a,&b,&c,&k);
	for(int i=1;i<=k;i++)
		scanf("%d",&Arr[i]);
	int g=0;
	for(int i=1;i<=k;i++)
		g=Gcd(g,Arr[i]);
	for(int i=1;i<=g;i++){
		Ans[i]=0;
		if(g%i==0)Ans[i]=Calc(i);
	}
	vector<int>Sg1,Sg2,Sg3;
	auto Transer=[&](int t,vector<int>&Sg){
		for(int i=1;i<=t;i++)if(t%i==0)Sg.push_back(i);
	};
	Transer(a,Sg1);Transer(b,Sg2);Transer(c,Sg3);
	int ans=0;
	for(auto i:Sg1){
		for(auto j:Sg2){
			for(auto k:Sg3){
				ll t=Lcm(Lcm(i,j),k);
				if(g%t!=0)continue;
				ans=(ans+1ll*Ans[t]*Phi[i]%Mod*Phi[j]%Mod*Phi[k]%Mod)%Mod;
			}
		}
	}
	printf("%lld\n",1ll*ans*Inv(1ll*a*b%Mod*c%Mod)%Mod);
}

int main(){
	#ifdef LOCAL
	freopen("In.txt","r",stdin);
	freopen("Out.txt","w",stdout);
	#endif
	
	Init();
	int Task=1;scanf("%d",&Task);
	for(int Case=1;Case<=Task;Case++){
		Main(Case);
	}
	
	return 0;
}