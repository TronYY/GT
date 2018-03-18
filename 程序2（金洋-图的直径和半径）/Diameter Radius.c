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
	X[0]=1;//X[0]��¼X�����ж������,��ʼʱVs����X����


}


/* ��(X)�Ƿ�Ϊ��?  ��:����0;��:����1
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
	printf("��������ͨͼG�Ķ������n=");
	scanf("%d",&n);
	printf("��������ͨͼG���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXN;//û�б���������Ȩֵ��Ϊ�㹻��
		}

	memset(d, 0, sizeof(d));
	/*�������������·,prim�㷨*/
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

	printf("ֱ��=%d\n�뾶=%d\n",diameter,radius);
	
}