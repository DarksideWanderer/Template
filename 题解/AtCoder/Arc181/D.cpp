const int MaxN=410000;

int LowBit(int x){return x&(-x);}
struct TreeArrays{
	int Arr[MaxN];
	int L;
	void Modify(int x,int v){
		for(;x<=L;x+=LowBit(x))
			Arr[x]+=v;
	}
	int Query(int x,int v=0){
		for(;x>=1;x-=LowBit(x))
			v+=Arr[x];
		return v;
	}
};TreeArrays T;

int A[MaxN],B[MaxN];
ll C[MaxN];
void Main(){
	
	int n;scanf("%d",&n);
	/*FanwickInit*/{
		for(int i=1;i<=n;i++)
			T.Arr[i]=0;
		T.L=n;
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	int m;scanf("%d",&m);
	for(int i=1;i<=m;i++)
		scanf("%d",&B[i]);
	B[m+1]=n;
	
	ll s=0;
	for(int i=1;i<=n;i++){
		ll t=T.Query(n)-T.Query(A[i]);
		s+=t;
		T.Modify(A[i],1);
		
		int L=1,R=m+1;
		while(L<R){
			int M=(L+R)>>1;
			if(B[M]>=i)R=M;
			else L=M+1;
		}
		
		if(L<=m)C[L]++;
		if(L+t<=m)C[L+t]--;
	}
	
	for(int i=1;i<=m;i++)
		C[i]+=C[i-1];
	for(int i=1;i<=m;i++)
		C[i]+=C[i-1];
	for(int i=1;i<=m;i++)
		printf("%lld\n",s-C[i]);
}