#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int M[MAXV][MAXV],X[MAXV],n,S[MAXV],T[MAXV];
int LAM[MAXV];
int V[MAXV];
int flag=0;//��ͨ��֧����


/* ��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int Phi() {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i]==flag)&&(X[j]==0)&&(M[i][j]<MAXN)) return(1);
	return(0);
}
void prim() {
	int i,j,min=MAXN;
	int now[MAXV];//��ʾĳ�����Ƿ�����һ�ַ�Ȧ��ѡ��ʱ������X����; 

	/*���·*/
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

	//�����е�δ����ʱ
	while (X[0]<n) {
		while (X[i]>0) i++;
		flag++;
		X[i]=flag;
		LAM[i]=0;//��i��Ϊ�����������·����


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
	
	return 1;//�Ƕ���ͼ


}



void main() {  
	int i,j;
	
	printf("������G�Ķ������n=");
	scanf("%d",&n);
	printf("������G���ڽӾ���:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&M[i][j]);
			if (M[i][j]==0) M[i][j]=MAXN;
		}

	
	for (i=1;i<=n;i++) LAM[i]=MAXN;


	CC();
	
	for (i=1;i<=S[0];i++) V[S[i]]=1;//��S���ϵĶ����Ϊ1
	for (i=1;i<=T[0];i++) V[T[i]]=-1;//��T���ϵĶ����Ϊ-1;����������һ��������˻�Ϊ1,���ڼ���
	
	if (check()) {
		printf("G�Ƕ���ͼ.\n");
		printf("S:");
		for (i=1;i<=S[0];i++) printf("%d ",S[i]);
		printf("\nT:");
		for (i=1;i<=T[0];i++) printf("%d ",T[i]);
		printf("\n");
	}
	else printf("G���Ƕ���ͼ");
}