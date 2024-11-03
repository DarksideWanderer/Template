void Main(){
	/*Definition*/
	const ll Inf=1000000000000ll;
	const ll Mod=1000000007;
	int n,m;
	vector<vector<ll>>D;
	vector<vector<ll>>P;
	vector<ll>A;
	vector<ll>B;
	vector<ll>S;
	vector<ll>Ss;
	/*Init*/
	scanf("%d%d",&n,&m);
	D.resize(m+10);
	std::fill(D.begin(),D.end(),[&n](){vector<ll>Tmp;Tmp.resize(n+10);return Tmp;}());
	P.resize(m+10);
	std::fill(P.begin(),P.end(),[&n](){vector<ll>Tmp;Tmp.resize(n+10);return Tmp;}());
	A.resize(n+10);
	B.resize(m+10);
	S.resize(n+10);
	Ss.resize(n+10);
	
	for(int i=1;i<=n;i++)scanf("%lld",&A[i]),S[i]=S[i-1]+A[i];
	for(int i=1;i<=m;i++)scanf("%lld",&B[i]);
	for(int i=0;i<=m;i++)
		for(int j=0;j<=n;j++)
			D[i][j]=Inf;
	for(int i=1;i<=m;i++){
		D[i][0]=0;P[i][0]=1;
		for(int l=1,r=1,r1=0;r<=n;r++){
			D[i][r]=D[i-1][r],P[i][r]=P[i-1][r];
			while(l<=r&&S[r]-S[l-1]>B[i])l++;
			if(l<=r){
				r1=std::max(r1,l-1);
				while(r1<r-1&&D[i][r1+1]==D[i][l-1])r1++;//r1!=r
				if(D[i][r]>D[i][l-1]+m-i){
					D[i][r]=D[i][l-1]+m-i;
					P[i][r]=(Ss[r1]-Ss[l-1]+Mod+P[i][l-1])%Mod;
				}
				else if(D[i][r]==D[i][l-1]+m-i){
					P[i][r]=(P[i][r]+Ss[r1]-Ss[l-1]+Mod+P[i][l-1])%Mod;
				}
			}
			Ss[r]=(Ss[r-1]+P[i][r])%Mod;
		}
	}
	if(D[m][n]==Inf)puts("-1");
	else printf("%lld %lld\n",D[m][n],P[m][n]);
}