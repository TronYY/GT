#include <stdio.h>
#define MAXV 100
void sort(int d[2][MAXV],int n) {
	int i,j,t;
	for (i=1;i<=n-1;i++)
		for (j=i+1;j<=n;j++) 
			if (d[1][i]>d[1][j]) {
				t=d[0][i];d[0][i]=d[0][j];d[0][j]=t;
				t=d[1][i];d[1][i]=d[1][j];d[1][j]=t;
			}

}
void main() {  
	int i,j,n;
	int d[3][MAXV];//d[0]保存节点号，d[1]保存度
	int M[MAXV][MAXV];//邻接矩阵
	int color[MAXV];//记录已经使用过的颜色
	int result[MAXV];//记录已经使用过的颜色
	
	memset(d, 0, sizeof(d));
	freopen("VertexColoring.in", "r", stdin);
	printf("请输入连通图G的顶点个数n=");
	scanf("%d",&n);
	printf("请输入连通图G的邻接矩阵:\n");
	for (i=1;i<=n;i++) {
		d[0][i]=i;
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			d[1][i]+=M[i][j];//同时计算度
		}
	}

	sort(d,n);
	result[d[0][n]]=1;//最后一点颜色为1号
	
	for (i=n-1;i>=1;i--) {
		memset(color, 0, sizeof(color));
		for (j=n;j>=i+1;j--)
			if (M[d[0][i]][d[0][j]]) color[result[d[0][j]]]++;
		for (j=1;j<=n-1;j++)
			if (color[j]==0) break;
		result[d[0][i]]=j;
	}

	printf("染色方案为:\n");
	for (i=1;i<=n;i++)
		printf("v%d:%d\n",i,result[i]);
	getchar();

			
}