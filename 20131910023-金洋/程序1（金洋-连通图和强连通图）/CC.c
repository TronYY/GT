#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int M[MAXV][MAXV],X[MAXV],n;
int flag=0;//连通分支个数


/* φ(X)是否为空?  是:返回0;否:返回1*/
int Phi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==0)&&(M[i][j])) return(1);
	return(0);
}
void prim() {
	int i,j;	
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==0)&&(M[i][j])) {
				X[j]=flag;
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
		X[0]++;
	
		while ( (X[0]<n) && Phi()) prim();

		for (j=i;j<=n;j++)
			if (X[j]==flag) printf("%d ",j);
		printf("\n");
	}
	printf("共%d个连通分支\n",flag);
}


void main() {  
	int i,j;
	freopen("CC.in", "r", stdin);
	printf("请输入G的顶点个数n=");
	scanf("%d",&n);
	printf("请输入G的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			scanf("%d",&M[i][j]);
	printf("连通分支为:\n");
	CC();
	if (flag==1) printf("G是连通图\n");
	else printf("G不是连通图\n");
	getch();
}