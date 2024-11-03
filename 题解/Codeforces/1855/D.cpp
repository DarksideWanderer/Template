void Main(){
	static std::bitset<210000>T;
	static std::bitset<210000>A;
	
	int n;scanf("%d",&n);
	vector<ll>Sum;Sum.resize(2*n+10);
	for(int i=1;i<=2*n;i++)
		T[i]=A[i]=0;
	T[1]=true;
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		Sum[i]=Sum[i-1]+x;
		T|=(T<<x);
		A|=T;
		T[i]=0;
	}
	for(int i=n+1;i<=2*n;i++)
		Sum[i]=Sum[i-1];
	ll ans=0;
	for(int i=1;i<=2*n;i++){
		if(A[i]){
			ans=std::max(ans,Sum[i]-(i-1));
		}
	}
	printf("%lld\n",ans);
}