void Main(){
	int n,m;
	vector<int>F;
	vector<int>G;
	vector<int>Arr;
	
	scanf("%d%d",&n,&m);
	F.resize(m+10);
	G.resize(m+10);
	Arr.resize(n+10);
	for(int i=1;i<=n;i++){
		scanf("%d",&Arr[i]);
	}
	int last=1;
	for(int i=1;i<=n;i++){
		if(Arr[i]==0){
			if(last!=i)std::sort(Arr.begin()+last,Arr.begin()+i);
			last=i+1;
		}
	}
	if(last!=n+1)std::sort(Arr.begin()+last,Arr.begin()+n+1);
	
	int beg=1;
	while(beg<=n&&Arr[beg]!=0)beg++;
	if(beg==n+1){
		puts("0");
		return;
	}
	
	auto Calc=[&](int a,int b,int p,int q){
		int aa=std::lower_bound(Arr.begin()+a,Arr.begin()+b+1,0)-Arr.begin();
		int bb=0;
		if(aa!=b+1)bb=std::upper_bound(Arr.begin()+aa,Arr.begin()+b+1,p)-Arr.begin()-aa;
		int cc=0;
		if(aa!=a)cc=std::lower_bound(Arr.begin()+a,Arr.begin()+aa,-q)-Arr.begin()-a;
		int dd=aa-a-cc;
		return bb+dd;
	};
	
	int sum=0;
	int ans=0;
	for(int i=beg;i<=n;i++){
		int j=i,now=0;
		while(j<=n&&Arr[j]==0)j++,now++;
		//i~j-1:0
		if(j==n+1)break;
		int k=j;
		while(k<=n&&Arr[k]!=0)k++;
		
		for(int l=0;l<=now+sum;l++)
			F[l]=0;
		for(int l=0;l<=now;l++){//给正数的个数
			for(int p=0;p<=sum;p++){
				F[l+p]=std::max(F[l+p],G[p]+Calc(j,k-1,l+p,sum+now-l-p));
			}
		}
		sum+=now;
		for(int l=0;l<=sum;l++)
			G[l]=F[l],ans=std::max(ans,G[l]);
		i=k-1;
	}
	printf("%d\n",ans);
}