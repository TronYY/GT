#include <stdio.h>
#include <stdlib.h>
#define MAXN 999999999
#define MAXV 100

int w[MAXV][MAXV],c[MAXV][MAXV],n,VS,VT,d;
int X[MAXV],n,LAM[MAXV],VS,L[MAXV][MAXV],wD[MAXV][MAXV],insert[MAXV][MAXV],LD[MAXV],SP[MAXV];
//L[MAXV][MAXV]��G�м�¼��L[i][j]��ʾ��(i,j)�п����������γɵ����·��
//LD[MAXV]��D�м�¼��LD[i]��ʾi��ǰ���ڵ�
//wD[MAXV][MAXV]ΪD�ı�Ȩֵ

void input() {
	int i,j;
	freopen("HSCSP.in", "r", stdin);
	printf("������G�Ķ������n=");
	scanf("%d",&n);
	printf("������G��w����:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) {
			scanf("%d",&w[i][j]);
			if (w[i][j]==0) w[i][j]=MAXN;//û�б���������Ȩֵ��Ϊ�㹻��
		}
	printf("������G��c����:\n");
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			scanf("%d",&c[i][j]);
	printf("���Vs=");
	scanf("%d",&VS);
	printf("�յ�Vt=");
	scanf("%d",&VT);
	printf("d=");
	scanf("%d",&d);

}


void shortestPathInitial() {
	int i;
	for (i=1;i<=n;i++) {
		X[i]=0; 
		LAM[i]=MAXN;
	}
	X[VS]=1;
	LAM[VS]=0;
	

}

/*��(X)�Ƿ�Ϊ��?  ��:����0;��:����1*/
int PHi(int M[MAXV][MAXV]) {
	int i,j;
	for(i=1;i<=n;i++)
		for (j=1;j<=n;j++)
			if ((i!=j)&&(X[i])&&(X[j]==0)&&(M[i][j]<MAXN)) return(1);
	return(0);
}

void primAllSP(int M[MAXV][MAXV]) {
	int i,j,min;
	int now[MAXV];//��ʾĳ�����Ƿ�����һ�ַ�Ȧ��ѡ��ʱ������X����; 

	for (i=1;i<=n;i++) now[i]=0;
	min=MAXN;

	for(i=1;i<=n;i++)
		if (X[i])
			for(j=1;j<=n;j++)
				if (!X[j]  && i!=j && LAM[i]+M[i][j]<min )
					min=LAM[i]+M[i][j];
					
	if (min!=MAXN) {
		for(i=1;i<=n;i++)
			if (X[i])
				for(j=1;j<=n;j++)
					if ( (!X[j] || now[j]) && i!=j && LAM[i]+M[i][j]==min ) {
						LAM[j]=min;
						X[j]=1;
						now[j]=1;
						//X[0]++;
						L[j][i]=1;//��ʾ��(i,j)�п����������γɵ����·��
					}	
	}
}


int buildD(int v) {
	int i;
	if (v==VS) return 0;
	for (i=1;i<=n;i++) 
		if (L[v][i]) {
			buildD(i);
			insert[i][v]=(w[i][v]+d-1)/d-1;//������������,a/b����ȡ��ֻ�� (a+b-1)/b
			wD[i][v]=insert[i][v]*c[i][v];	
		}
	return 0;
}


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
		LD[y]=x;
		LAM[y]=min;
	}
}

int getSP(int v) {
	int i;
	if (v==VS) {
		SP[0]=1;
		SP[1]=VS;
		return 0;

	}
	for (i=1;i<=n;i++) 
		if (LD[v]==i) {
			getSP(i);
			SP[0]++;
			SP[SP[0]]=v;
			return 0;
		}
}

void main() {
	int i,j,total;
	//freopen("test.in", "r", stdin);
	input();
	shortestPathInitial();
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			L[i][j]=0;

	while (!X[VT] && PHi(w)) primAllSP(w);
	buildD(VT);
	for (i=1;i<=n;i++)
		for (j=1;j<=n;j++) 
			if (wD[i][j]==0) wD[i][j]=MAXN;
	
	shortestPathInitial();
	while (!X[VT] && PHi(wD)) prim(wD);
	getSP(VT);

	printf("\n\n���·Ϊ:");
	for (i=1;i<=SP[0];i++) printf("%d ",SP[i]);
	printf("\n���·��ÿ�����ϵĲ����ĿΪ:\n");

	total=0;
	for (i=1;i<=SP[0]-1;i++) {
		printf("%d %d:%d\n",SP[i],SP[i+1],insert[SP[i]][SP[i+1]]);
		total+=wD[SP[i]][SP[i+1]];
	}
	printf("���·�Ĳ�����Ϊ:%d\n",total);
	getch();
}