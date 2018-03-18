#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int M[MAXV][MAXV],X[MAXV],n;
int flag=0;//强连通分支个数


/* φ+(X)是否为空?  是:返回0;否:返回1*/
int Phi_plus() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==-1)&&(X[j]==0)&&(M[i][j])) return(1);
	return(0);
}
void prim1() {
	int i,j;	
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==-1)&&(X[j]==0)&&(M[i][j])) {
				X[j]=-1;
				X[0]++;
			}
}


/* φ-(X)是否为空?  是:返回0;否:返回1*/
int Phi_minus() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==-1)&&(M[j][i])) return(1);
	return(0);
}
void prim2() {
	int i,j;
	for(i=1;i<=n;i++)		
		for(j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==-1)&&(M[j][i])) {
				X[j]=flag;
				X[0]++;
			}			
}



void SCC() {
	int i=1,j;
	int visited;
	//当仍有点未访问时
	while (X[0]<n) {
		while (X[i]>0) i++;
		flag++;

		X[i]=-1;
		X[0]++;
		visited=X[0];
		while ( (X[0]<n) && Phi_plus()) prim1();

		X[0]=visited;
		X[i]=flag;
		while ( (X[0]<n) && Phi_minus()) prim2();

		for (j=i;j<=n;j++)
			if (X[j]==flag) printf("%d ",j);
			else if (X[j]==-1) X[j]=0;
		printf("\n");
	}
	printf("共%d个强连通分支\n",flag);
}


void main() {  
	int i,j;
	//freopen("SCC.in", "r", stdin);
	printf("请输入D的顶点个数n=");
	scanf("%d",&n);
	printf("请输入D的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			scanf("%d",&M[i][j]);
	printf("强连通分支为:\n");
	SCC();
	if (flag==1) printf("D是强连通图\n");
	else printf("D不是强连通图\n");
}