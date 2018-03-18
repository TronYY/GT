#include <stdio.h>
#include <string.h>
#include <windows.h>

#define MAXN 999999999
#define MAXV 100
void input(int S[MAXV],int T[MAXV],int C[MAXV][MAXV]) {
	int i,e,a,b;
	freopen("Matching2.in", "r", stdin);
	printf("������S���ϵĶ������|S|=");
	scanf("%d",&S[0]);
	printf("������S���ϵĶ���:");
	for (i=1;i<=S[0];i++)	scanf("%d",&S[i]);
	printf("������T���ϵĶ������|T|=");
	scanf("%d",&T[0]);
	printf("������T���ϵĶ���:");
	for (i=1;i<=T[0];i++)	scanf("%d",&T[i]);
	
	printf("���������ͼG�ı���:\n");
	scanf("%d",&e);

	printf("�������������ͼG��%d����:\n",e);
	for (i=1;i<=e;i++) {
		scanf("%d %d",&a,&b);
		C[a][b]=1;
	}	
}

void buildN(int n,int S[MAXV],int T[MAXV],int C[MAXV][MAXV]) {
	int i;
	for (i=1;i<=S[0];i++)
		C[n+1][S[i]]=1;//��n+1Ϊ��㣬�����S���϶�����������Ϊ1;
	for (i=1;i<=T[0];i++)
		C[T[i]][n+2]=1;//��n+2Ϊ�յ㣬T�������յ㶼����������Ϊ1;

}

/*����ʣ������*/
void buildNf(int n,int C[MAXV][MAXV],int Cf[MAXV][MAXV],int F[MAXV][MAXV]) {
	int i,j;

	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			if (C[i][j]) {
				Cf[i][j]=C[i][j]-F[i][j];
				Cf[j][i]=F[i][j];
		}
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (Cf[i][j]==0) 
				Cf[i][j]=MAXN;//ȥ��Nf������ֵΪ0�����л�
}


/*���·����ʼ��*/
void shortestPathInitial(int n,int VS,int X[MAXV],int LAM[MAXV],int L[MAXV]) {
	int i;
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXN;
	}
	LAM[VS]=0;

	X[VS]=1;
	X[0]=1;//X[0]��¼X�����ж������,��ʼʱVs����X����	
	for (i=1;i<=n;i++) L[i]=0;
}



/*��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi(int M[MAXV][MAXV],int X[MAXV],int n) {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXN)) return(1);
	return(0);
}

/*���·*/
void prim(int M[MAXV][MAXV],int X[MAXV],int LAM[MAXV],int L[MAXV],int n) {
	int i,j,min;
	int x,y;
	
	min=MAXN;

	for(i=1;i<=n;i++)
		if (X[i])
			for(j=1;j<=n;j++)
				if (!X[j]  && i!=j && LAM[i]+M[i][j]<min ) {
					min=LAM[i]+M[i][j];
					x=i;
					y=j;
				}					
	if (min!=MAXN) {		
		X[y]=1;
		X[0]++;
		L[y]=x;
		LAM[y]=min;
	}
}

/*�ı�N�е�����*/
void changeFlow(int VT,int L[MAXV],int Cf[MAXV][MAXV],int F[MAXV][MAXV],int C[MAXV][MAXV]) {
	int theta=MAXN;
	int y=VT;
	while (L[y]!=0) {
		if (theta>Cf[L[y]][y] ) theta=Cf[L[y]][y];
		if (theta>Cf[y][L[y]] ) theta=Cf[y][L[y]];
		y=L[y];	
	}

	y=VT;
	while (L[y]!=0) {
		if (F[L[y]][y]<C[L[y]][y]) F[L[y]][y]+=theta;
		if (F[y][L[y]]>0) F[y][L[y]]-=theta;
		y=L[y];
	}
}


void main() { 
	int n;//������
	
	int S[MAXV],T[MAXV];
	int C[MAXV][MAXV],F[MAXV][MAXV];//C,F�ֱ��¼N������������
	int Cf[MAXV][MAXV];//ʣ������Ȩֵ
	int LAM[MAXV],L[MAXV],X[MAXV];
	int VS,VT,m;

	int i,j;
	memset(C, 0, sizeof(C));//������ʼΪȫ0
	memset(F, 0, sizeof(F));//������ʼΪȫ0
	memset(Cf, 0, sizeof(Cf));	
	input(S,T,C);
	n=S[0]+T[0];//ԭͼ�������
	buildN(n,S,T,C);
	
	VS=n+1;//���
	VT=n+2;//�յ�
	n=n+2;
	while (1) {
		buildNf(n,C,Cf,F);
		shortestPathInitial(n,VS,X,LAM,L);//���·����ʼ��
		while (!X[VT] && PHi(Cf,X,n)) prim(Cf,X,LAM,L,n);
		if (X[VT]) changeFlow(VT,L,Cf,F,C);
			else break;
		//printf("Jin");
	}

	m=0;
	printf("����ͼG�����ƥ��MΪ:\n");
	for (i=1;i<=S[0];i++)
		for (j=1;j<=T[0];j++)
			if (F[S[i]][T[j]]>0) {
				printf("v%d v%d\n",S[i],T[j]);
				m++;
			}
	printf("���ƥ����|M|=%d\n",m);
	getch();
}