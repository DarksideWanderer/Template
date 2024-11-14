const int MaxN=210000;
const int Mod=998244353;
int A(int a,int b){return a+b>=Mod?a+b-Mod:a+b;}
int M(int a,int b){return 1ll*a*b%Mod;}
int Pow(int a,int b){
	int r=1;
	while(b){
		if(b&1){r=M(r,a);}
		a=M(a,a);b>>=1;
	}
	return r;
}
int Inv(int a){return Pow(a,Mod-2);}
int F[MaxN],IF[MaxN],I[MaxN];
int CalcC(int n,int m){
	if(m<0||m>n)return 0;
	return M(M(F[n],IF[n-m]),IF[m]);
}
int P2[MaxN];
void Init(){
	const int L=200000;
	F[0]=1;
	for(int i=1;i<=L;i++)F[i]=M(F[i-1],i);
	IF[L]=Pow(F[L],Mod-2);
	for(int i=L-1;i>=0;i--)IF[i]=M(IF[i+1],i+1);
	for(int i=1;i<=L;i++)I[i]=M(IF[i],F[i-1]);
	P2[0]=1;
	for(int i=1;i<=L;i++)P2[i]=M(2,P2[i-1]);
}

void Main(){
	//Def
	int n;
	vector<int>Arr;
	vector<int>S;
	vector<int>Sum;
	vector<vector<int>>F;
	//Init
	scanf("%d",&n);
	Arr.resize(n+10);
	S.resize(n+10);
	F.resize(n+10);
	Sum.resize(n+10);
	for(int i=1;i<=n;i++){
		int x;scanf("%d",&x);
		Arr[x]++;
	}
	for(int i=n-1;i>=0;i--){
		Sum[i]=Sum[i+1]+Arr[i];
	}
	int ans=0;
	for(int i=0;i<=Arr[0];i++){
		F[0].resize(std::max(Arr[1],Arr[0])+10);
		F[0][i]=CalcC(Arr[0],i);
		ans=A(ans,M(P2[Sum[1]],M(F[0][i],i)));
	}
			
	for(int i=1;i<=n-1;i++){
		F[i].resize(std::max(Arr[i],Arr[i+1])+10);
		int ss=0;
		for(int j=Arr[i-1];j>=0;j--)ss=A(ss,F[i-1][j]);
		
		for(int j=0,now=P2[Arr[i]];j<=Arr[i];j++){
			if(j<=Arr[i-1])ss=A(ss,Mod-F[i-1][j]);
			F[i][j]=M(F[i-1][j],now);
			F[i][j]=A(F[i][j],M(CalcC(Arr[i],j),ss));
			now=A(now,Mod-CalcC(Arr[i],j));
		}
		for(int j=0;j<=Arr[i];j++)
			ans=A(ans,M(P2[Sum[i+1]],M(F[i][j],j)));
	}
	printf("%d\n",ans);
}

/*Add at main()*/{
	Init();
}