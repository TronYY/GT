#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int M[MAXV][MAXV],X[MAXV],n;
int flag=0;//��ͨ��֧����


/* ��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
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
	
	//�����е�δ����ʱ
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
	printf("��%d����ͨ��֧\n",flag);
}


void main() {  
	int i,j;
	freopen("CC.in", "r", stdin);
	printf("������G�Ķ������n=");
	scanf("%d",&n);
	printf("������G���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			scanf("%d",&M[i][j]);
	printf("��ͨ��֧Ϊ:\n");
	CC();
	if (flag==1) printf("G����ͨͼ\n");
	else printf("G������ͨͼ\n");
	getch();
}