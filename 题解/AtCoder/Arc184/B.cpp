int Pc[1<<21];
int Fi[1<<21];
int Gi[1<<21];
int Sc[35];
int Len[35];

int Solve(int len){
	int h=std::log2(len);
	for(int i=0;i<=h;i++){
		Len[i]=0;
		int now=(1<<i);
		for(int j=0;j<=i;j++){
			if(now>len)break;
			Len[i]++;
			now=now/2*3;
		}
	}
	for(int j=0;j<=Sc[Len[h]];j++){
		Fi[j]=Pc[j];
	}
	for(int i=h-1;i>=0;i--){
		int ss=Len[i+1]-1;
		for(int j=Sc[Len[i+1]];j>=0;j--){
			for(int k=0;k<=ss;k++)
				Fi[j]=std::min(Fi[j],Fi[j|(1<<k)]);
		}
		for(int j=Sc[Len[i]];j>=0;j--){
			int s=((j|(j<<1))&Sc[Len[i+1]])^Sc[Len[i+1]];
			Gi[j]=Fi[s]+Pc[j];
		}
		for(int j=Sc[Len[i]];j>=0;j--){
			Fi[j]=Gi[j];
		}
	}
	return Fi[1];
}

void Main(){
	int n;
	auto Init=[&](){
		scanf("%d",&n);
		for(int i=1;i<=30;i++)
			Sc[i]=(1<<i)-1;
		for(int i=0;i<=Sc[21];i++)
			Pc[i]=__builtin_popcount(i);
		return ;
	};
	
	Init();
	int ans=0;
	for(int l=1,r;l<=n;l=r+1){
		r=std::min(n,(n/(n/l)));
		int num=(r-l+1)-(r/2+r/3-r/6-(l-1)/2-(l-1)/3+(l-1)/6);
		ans+=num*Solve(n/l);
	}
	printf("%lld\n",ans);
}
