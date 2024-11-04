#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 998244353
#define N 2000000

int i,j,k,n,m,t,d,a[N+50],mn;
ll jc[N+50],inv[N+50],res,tot,g[N+50],sb;

ll su(ll a,ll b){a+=b;return (a>=M)?a-M:a;}
ll ksm(ll a,ll p){ll res=1;while(p){if(p&1){res=res*a%M;}a=a*a%M;p>>=1;}return res;}
ll c(ll n,ll m){if(n<m||n<0||m<0){return 0;}return jc[n]*inv[m]%M*inv[n-m]%M;}

int main(){
	ios::sync_with_stdio(0); cin.tie(0);
	jc[0]=inv[0]=1;
	for(i=1;i<=N;i++)jc[i]=jc[i-1]*i%M;
	inv[N]=ksm(jc[N],M-2);
	for(i=N-1;i>=1;i--)inv[i]=inv[i+1]*(i+1)%M;
	
	cin>>t;
	while(t--){
		cin>>n; res=0; mn=n;
		for(i=0;i<=n;i++){
			a[i]=0; g[i]=1;
		}
		for(i=1;i<=n;i++){
			cin>>k; a[k]++;
		}
		tot=n;
		for(i=0;i<=n;i++){
			mn=min(mn,a[i]); tot-=a[i];
			sb=ksm(2,a[i])-1;
			for(j=1;j<=mn;j++){
				g[j]=g[j]*sb%M;
				res+=g[j]*ksm(2,tot)%M; res%=M;
				sb+=M-c(a[i],j); sb%=M;
				//cout<<"NMSL "<<i<<' '<<j<<' '<<res<<endl;
			}
		}
		
		cout<<res<<'\n';
	}
}