#include<iostream>
using namespace std;

void merge(int *b,int b_len,int *c,int c_len,int *a)
{
	int i=0,j=0,k=0;
	while(i<b_len&&j<c_len)
	{
		if(b[i]<=c[j])
		{
			a[k]=b[i];i++;
		}
		else
		{
			a[k]=c[j];j++;
		}
		k++;
	}
	if(i==b_len)
	{
		for(;j<c_len;j++)
		{
			a[k]=c[j];
			k++;
		}
	}
	else
	{
		for(;i<b_len;i++)
		{
			a[k]=b[i];
			k++;
		}
	}
}

void mergesort(int *a,int n)
{
	int i,j,half;
	int *b =NULL,*c=NULL;

	if(n>1)
	{
		half=n/2;
		b=(int *)malloc(sizeof(int)*half);
		c=(int *)malloc(sizeof(int)*(n-half));
		for(i=0;i<half;i++) b[i]=a[i];
		for(j=half;j<n;j++) c[j-half]=a[j];
		mergesort(b,half);
		mergesort(c,n-half);
		merge(b,half,c,n-half,a);
		if(b) free(b);
		if(c) free(c);

	}
}

int main()
{
	int i=0;
	int A[]={10,9,8,7,6,5,4,3,2,1};
	mergesort(A,sizeof(A)/sizeof(int));
	for(i=0;i<sizeof(A)/sizeof(int);i++)
		cout<<A[i]<<" "<<endl;
	return 0;


}