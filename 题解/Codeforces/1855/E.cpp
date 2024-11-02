void Main(){
	const ll Mod=1000000007;
	auto Pow=[&Mod](ll a,ll b){
		ll r=1;
		while(b){
			if(b&1){r=r*a%Mod;}
			a=a*a%Mod;b>>=1;
		}
		return r;
	};
	auto Inv=[&Pow,&Mod](ll a){
		return Pow(a,Mod-2);
	};
	
	const ll inv2=Inv(2);
	int n,m;
	scanf("%d%d",&n,&m);
	
	vector<vector<ll>>Dp;Dp.resize(m+10);
	std::fill(Dp.begin(),Dp.end(),vector<ll>(m+10));
	vector<int>Arr;Arr.resize(n+10);
	
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	Arr[n+1]=m+1;
	
	Dp[m+1][m+1]=0;
	for(int i=m;i>=1;i--){
		for(int j=m+1;j>=i+1;j--){
			if(j==m+1)Dp[i][j]=(Dp[i+1][j]+1)%Mod;
			else Dp[i][j]=(Dp[i+1][j]+Dp[i][j+1]+1)*inv2%Mod;
		}
	}
	
	ll ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+Dp[Arr[i]][Arr[i+1]])%Mod;
	}
	printf("%lld\n",ans);
}