#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int M[MAXV][MAXV],X[MAXV],n,S[MAXV],T[MAXV];
int LAM[MAXV];
int V[MAXV];
int flag=0;//连通分支个数


/* φ(X)是否为空?  是:返回0;否:返回1*/
int Phi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==0)&&(M[i][j]<MAXN)) return(1);
	return(0);
}
void prim() {
	int i,j,min=MAXN;
	int now[MAXV];//表示某顶点是否在这一轮反圈中选边时被加入X集合; 

	/*最短路*/
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==0)&&(LAM[i]+M[i][j]<min)) 
				min=LAM[i]+M[i][j];

	if (min==MAXN) exit(0);

	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if ( (i!=j)&&(X[i]==flag)&&(X[j]==0 || now[j])&&(LAM[i]+M[i][j]==min)) {
				LAM[j]=min;
				X[j]=flag;
				now[j]=1;
				X[0]++;
			}

}


void CC() {
	int i=1,j;

	//当仍有点未访问时
	while (X[0]<n) {
		while (X[i]>0) i++;
		flag++;
		X[i]=flag;
		LAM[i]=0;//以i点为根，构造最短路径树


		X[0]++;
	
		while ( (X[0]<n) && Phi()) prim();

		for (j=i;j<=n;j++)
			if (X[j]==flag && LAM[j]!=MAXN)
				if (LAM[j]%2==1) S[++S[0]]=j;
				else T[++T[0]]=j;
				
	}
}


int check() {
	int i,j;
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if (M[i][j]==1 && V[i]*V[j]==1) return 0;
	
	return 1;//是二部图


}



void main() {  
	int i,j;
	
	printf("请输入G的顶点个数n=");
	scanf("%d",&n);
	printf("请输入G的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXN;
		}

	
	for (i=1;i<=n;i++) LAM[i]=MAXN;


	CC();
	
	for (i=1;i<=S[0];i++) V[S[i]]=1;//把S集合的顶点标为1
	for (i=1;i<=T[0];i++) V[T[i]]=-1;//把T集合的顶点标为-1;若两点属于一个集合则乘积为1,便于检验
	
	if (check()) {
		printf("G是二部图.\n");
		printf("S:");
		for (i=1;i<=S[0];i++) printf("%d ",S[i]);
		printf("\nT:");
		for (i=1;i<=T[0];i++) printf("%d ",T[i]);
		printf("\n");
	}
	else printf("G不是二部图");
}