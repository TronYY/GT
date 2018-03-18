#include <stdio.h>
#include <string.h>
#define MAXN 999999999
#define MAXV 100

int n;//顶点数
int f;//记录弧连通度
int C[MAXV][MAXV],F[MAXV][MAXV];//C,F分别记录N的容量、流量
int Cf[MAXV][MAXV];//剩余网络权值
int LAM[MAXV],L[MAXV],X[MAXV];



void input() {
	int i,j;
	freopen("ArcConnectivity.in", "r", stdin);
	printf("请输入有向图D的顶点个数n=");
	scanf("%d",&n);
	printf("请输入有向图D的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			scanf("%d",&C[i][j]);
	
}



/*构造剩余网络*/
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
				Cf[i][j]=MAXN;//去掉Nf中容量值为0的所有弧
}


/*最短路径初始化*/
void shortestPathInitial(int VS) {
	int i;
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXN;
	}
	LAM[VS]=0;

	X[VS]=1;
	X[0]=1;//X[0]记录X集合中顶点个数,初始时Vs进入X集合	
	for (i=1;i<=n;i++) L[i]=0;
}



/*φ(X)是否为空?  是:返回0;否:返回1*/
int PHi(int M[MAXV][MAXV]) {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXN)) return(1);
	return(0);
}

/*最短路*/
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

/*改变N中的流量*/
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
	f=MAXN;//记录弧连通度
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (i!=j) {
				memset(F, 0, sizeof(F));//流量初始为全0
				while (1) {
					buildNf();
					shortestPathInitial(i);//最短路径初始化
					while (!X[j] && PHi(Cf)) prim(Cf);
					if (X[j]) changeFlow(j);
					else break;
				}
				tempVf=0;
				for(k=1;k<=n;k++) tempVf+=F[i][k];
				if (tempVf<f) f=tempVf;
			}
	printf("D的弧连通度为%d\n",f);
	getch();
}