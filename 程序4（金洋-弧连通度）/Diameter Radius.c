#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int M[MAXV][MAXV],X[MAXV],n,LAM[MAXV],VS,d[MAXV][MAXV],e[MAXV],diameter,radius;


void shortestPathInitial() {
	int i;
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXN;
	}
	LAM[VS]=0;
	X[VS]=1;
	X[0]=1;//X[0]记录X集合中顶点个数,初始时Vs进入X集合


}


/* φ(X)是否为空?  是:返回0;否:返回1
int Phi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==0)&&(M[i][j])) return(1);
	return(0);
}
*/

void prim() {
	int i,j,min;
	int y;	
	min=MAXN;
	for(i=1;i<=n;i++)
		if (X[i])
			for(j=1;j<=n;j++)
				if (!X[j]  && i!=j && LAM[i]+M[i][j]<min ) {
					min=LAM[i]+M[i][j];
					y=j;
				}					
	if (min!=MAXN) {		
		X[y]=1;
		X[0]++;
		LAM[y]=min;
	}
}





void main() {  
	int i,j;
	//freopen("test.in", "r", stdin);
	printf("请输入连通图G的顶点个数n=");
	scanf("%d",&n);
	printf("请输入连通图G的邻接矩阵:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXN;//没有边相连，将权值设为足够大
		}

	memset(d, 0, sizeof(d));
	/*求任意两点最短路,prim算法*/
	for (i=1;i<=n;i++) {
		VS=i;
		shortestPathInitial();
		while (X[0]<n) prim();
		for (j=1;j<=n;j++) 
			if (LAM[j]!=MAXN) d[i][j]=LAM[j];
	}


	diameter=0;
	radius=MAXN;
	for (i=1;i<=n;i++) {
		e[i]=0;
		for (j=1;j<=n;j++) {
			if (d[i][j]>diameter) diameter=d[i][j];
			if (d[j][i]>e[i]) e[i]=d[j][i];
		}
		if (e[i]<radius) radius=e[i];
	}

	printf("直径=%d\n半径=%d\n",diameter,radius);
	
}