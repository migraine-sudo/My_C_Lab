/*
分治法求最近对
Author：Migraine
Data：2019.12
*/

#include<stdio.h>
#include<math.h>
#include <time.h>
/*定义测试变量*/
#define MAX_RANGE 200  //测试点范围
#define MAX_DISTANCE 99999 //初始化距离
#define POINT_NUM 100 //测试点数量
/*定义Alogorthm的宏*/
#define FORCE 0
#define EFFICIENT 1
typedef int Algorthm;

/*POINT结构*/
struct POINT
{
	double x,y;//coordinate
};


/*计算两点之间的距离*/
double dis(struct POINT p1,struct POINT p2)
{
	return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}

/*暴力法*/
double force(struct POINT p[POINT_NUM],int LEN)
{
	double min=MAX_DISTANCE;
	struct POINT Pmin[2];
	for(int i=0;i<LEN;i++)
	{
		for(int j=i+1;j<LEN;j++)
			{
				if(min>=dis(p[i],p[j]))
				{
					min=dis(p[i],p[j]);
					Pmin[1].x=p[i].x;
					Pmin[1].y=p[i].y;
					Pmin[0].x=p[j].x;
					Pmin[0].y=p[j].y;
				}
			}
	}
	//printf("Minest Point (x=%f,y=%f) (x=%f,y=%f) min=%f \n",Pmin[0].x,Pmin[0].y,Pmin[1].x,Pmin[1].y,min);
	return min;
}
/*求最小*/
double min(double d1,double d2)
{
	if(d1<=d2)
		return d1;
	else
		return d2;
}

/*将点按照Y轴升序排列,重载（假的 */
double POINT_SORT_y(struct POINT p[POINT_NUM],struct POINT p_y[POINT_NUM],int LEN)//结构体数组本身就是一个指针，直接传指针就行了
{
	/*拷贝p到p_y数组*/
	for(int i=0;i<LEN;i++)
	{
			p_y[i].x=p[i].x;
			p_y[i].y=p[i].y;
	}
	/*按照y的升序排序*/
	double temp;
	for(int i=0;i<LEN;i++)
	{
		for(int j=i+1;j<LEN;j++)
		{
			if(p_y[i].y>p_y[j].y)
			{
				temp=p_y[j].x;
				p_y[j].x=p_y[i].x;
				p_y[i].x=temp;
				temp=p_y[j].y;
				p_y[j].y=p_y[i].y;
				p_y[i].y=temp;
			}
		}
	}
	return 0;
}

/*将点按照Y轴升序排列 */
double POINT_SORT_Y(struct POINT p[POINT_NUM],struct POINT p_y[POINT_NUM])//结构体数组本身就是一个指针，直接传指针就行了
{
	/*拷贝p到p_y数组*/
	for(int i=0;i<POINT_NUM;i++)
	{
			p_y[i].x=p[i].x;
			p_y[i].y=p[i].y;
	}
	/*按照y的升序排序*/
	double temp;
	for(int i=0;i<POINT_NUM;i++)
	{
		for(int j=i+1;j<POINT_NUM;j++)
		{
			if(p_y[i].y>p_y[j].y)
			{
				temp=p_y[j].x;
				p_y[j].x=p_y[i].x;
				p_y[i].x=temp;
				temp=p_y[j].y;
				p_y[j].y=p_y[i].y;
				p_y[i].y=temp;
			}
		}
	}
	return 0;
}
/*将点按照X轴升序排列 */
double POINT_SORT_X(struct POINT p[POINT_NUM],struct POINT p_x[POINT_NUM])//结构体数组本身就是一个指针，直接传指针就行了
{
	/*拷贝p到p_x数组*/
	for(int i=0;i<POINT_NUM;i++)
	{
			p_x[i].x=p[i].x;
			p_x[i].y=p[i].y;
	}
	/*按照x的升序排序*/
	double temp;
	for(int i=0;i<POINT_NUM;i++)
	{
		for(int j=i+1;j<POINT_NUM;j++)
		{
			if(p_x[i].x>p_x[j].x)
			{
				temp=p_x[j].x;
				p_x[j].x=p_x[i].x;
				p_x[i].x=temp;
				
				temp=p_x[j].y;
				p_x[j].y=p_x[i].y;
				p_x[i].y=temp;
			}
		}
	}
	return 0;
}

/*分治发求最近对*/
double EfficientClosestPair(struct POINT P[POINT_NUM],struct POINT Q[POINT_NUM],int LEN)
{
	struct POINT P_r[LEN/2],Q_r[LEN/2];
	struct POINT P_l[LEN/2],Q_l[LEN/2];
	double Dmin,d1,d2,m;
	int k,count=0;
	struct POINT S[POINT_NUM];

	if(LEN<=3)
	{
		return force(P,LEN);
	}
	/*将P和Q分别储存到P_l P_r和Q_l Q_r*/
	/*需要注意的是Q存储到左右的数据要和P保持一致，顺序保持不变*/
	for(int i=0;i<LEN;i++)
	{
			if(i<LEN/2)
			{
				P_l[i].x=P[i].x;
				P_l[i].y=P[i].y;		
			}
			else{
				P_r[i-LEN/2].x=P[i].x;
				P_r[i-LEN/2].y=P[i].y;
			}
	}
	POINT_SORT_y(P_l,Q_l,LEN/2);
	POINT_SORT_y(P_r,Q_r,LEN/2);

	/*递归调用*/
	d1=EfficientClosestPair(P_l,Q_l,LEN/2);
	d2=EfficientClosestPair(P_r,Q_r,LEN/2);
	Dmin=min(d1,d2);
	//printf("Dmin=%f ",Dmin);
	/* 计算相邻区间是否存在更近距离的点*/
	
	m=P[LEN/2-1].x;
	//printf("m=%f",m);
	for(int i=0;i<LEN;i++)
	{
		if(abs(Q[i].x-m)<Dmin)
		{
			S[count].x=Q[i].x;
			S[count].y=Q[i].y;
			count++;
		}
	}
	
	//printf("count=%d\n",count);
	for(int i=0;i<count;i++)
	{
		k=i+1;
		while(k<=count&&(S[k].y-S[i].y)<Dmin)
		{
				Dmin=min(dis(S[k],S[i]),Dmin);
				k+=1;
		}
	}
	
	return Dmin;
}

void TimeComplexity(Algorthm mode,struct POINT p[MAX_RANGE])
{
	char *algorthm[]={"暴力法","分治法"};
	double time;
	clock_t start,finish;
	double Total_time;
	struct POINT P[POINT_NUM];
	struct POINT Q[POINT_NUM];
	printf("[*]正在使用%s解决问题...\n",algorthm[mode]);
	switch(mode){
		case FORCE:
		time=force(p,POINT_NUM);
		break;
		case EFFICIENT:
		/*排序*/
		POINT_SORT_X(p,P);
		POINT_SORT_Y(p,Q);

		time=EfficientClosestPair(P,Q,POINT_NUM);
		break;
	}
	start=clock();
	printf("%s求最近对距离为= %f \n",algorthm[mode],time);
	finish=clock();
	Total_time=(double)(finish-start)/CLOCKS_PER_SEC;
	printf("%s耗时 ：%f\n\n",algorthm[mode],Total_time);
}

int main()
{
	printf("====Edited by Xiaolinfeng====\n");
	printf("Z09317120\n");
	printf("[+]生成点个数:%d\n",POINT_NUM);
	printf("[+]生成范围[%dx%d]\n\n",MAX_RANGE,MAX_RANGE);
	struct POINT p[POINT_NUM];

	for(int i=0;i<POINT_NUM;i++)
	{
		p[i].x=rand()%MAX_RANGE;
		p[i].y=rand()%MAX_RANGE;
	}

/*时间复杂对测试框架 参数1:选择算法mode 参数2 输入点的结构体数组*/
	TimeComplexity(FORCE,p);
	TimeComplexity(EFFICIENT,p);



}