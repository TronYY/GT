#include <stdio.h>
#include <string.h>
#define MAXN 999999999
#define MAXV 100

int n;//������
int f;//��¼����ͨ��
int C[MAXV][MAXV],F[MAXV][MAXV];//C,F�ֱ��¼N������������
int Cf[MAXV][MAXV];//ʣ������Ȩֵ
int LAM[MAXV],L[MAXV],X[MAXV];



void input() {
	int i,j;
	freopen("ArcConnectivity.in", "r", stdin);
	printf("����������ͼD�Ķ������n=");
	scanf("%d",&n);
	printf("����������ͼD���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			scanf("%d",&C[i][j]);
	
}



/*����ʣ������*/
void buildNf() {
	int i,j;

	memset(Cf, 0, sizeof(Cf));
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
void shortestPathInitial(int VS) {
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
int PHi(int M[MAXV][MAXV]) {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXN)) return(1);
	return(0);
}

/*���·*/
void prim(int M[MAXV][MAXV]) {
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
void changeFlow(int VT) {
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
	int i,j,k,tempVf;
	input();
	f=MAXN;//��¼����ͨ��
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (i!=j) {
				memset(F, 0, sizeof(F));//������ʼΪȫ0
				while (1) {
					buildNf();
					shortestPathInitial(i);//���·����ʼ��
					while (!X[j] && PHi(Cf)) prim(Cf);
					if (X[j]) changeFlow(j);
					else break;
				}
				tempVf=0;
				for(k=1;k<=n;k++) tempVf+=F[i][k];
				if (tempVf<f) f=tempVf;
			}
	printf("D�Ļ���ͨ��Ϊ%d\n",f);
	getch();
}