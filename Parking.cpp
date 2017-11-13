#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define N 10                    //停车场内最多的停车数
#define M 10                    //便道内最多的停车数
#define Price 5             //一个单位时间收费5元

typedef struct
{
	int ChePaiHao2[N];           //车牌号
	int JinChangShiJian[N];         //进场时间
	int top;                //栈指针
} TingCheChang;                  

typedef struct
{
	int ChePai[M];           //车牌号
	int front, rear;         //队首和队尾指针
} BianDao;                  

							
void ChuangJiang(TingCheChang *&s)		//创建顺序栈
{
	s = (TingCheChang *)malloc(sizeof(TingCheChang));
	s->top = -1;
}
int Kong(TingCheChang *s)		//停车场为空
{
	return(s->top == -1);
}
int Mang(TingCheChang *s)		//停车场为满
{
	return(s->top == N - 1);
}
int TingRu(TingCheChang *&s, int e1, int e2)	  //将车停入
{
	if (s->top == N - 1)
		return 0;
	s->top++;
	s->ChePaiHao2[s->top] = e1;
	s->JinChangShiJian[s->top] = e2;
	return 1;
}
int LiKai(TingCheChang *&s, int &e1, int &e2)	 //汽车离开
{
	if (s->top == -1)
		return 0;
	e1 = s->ChePaiHao2[s->top];
	e2 = s->JinChangShiJian[s->top];
	s->top--;
	return 1;
}
void ChaXunZhan(TingCheChang *s)
{
	int i;
	for (i = s->top; i >= 0; i--)
		printf("%d ", s->ChePaiHao2[i]);
	printf("\n");
}

/*以下为循环队列的基本运算算法*/
void Dui(BianDao *&q)		//创建队列
{
	q = (BianDao *)malloc(sizeof(BianDao));
	q->front = q->rear = 0;
}
int DuiKong(BianDao *q)		//	判断队空
{
	return(q->front == q->rear);
}
int DuiMan(BianDao *q)       //判断队满
{
	return ((q->rear + 1) % M == q->front);
}
int JinDui(BianDao *&q, int e)      //进队
{
	if ((q->rear + 1) % M == q->front)    //队满
		return 0;
	q->rear = (q->rear + 1) % M;
	q->ChePai[q->rear] = e;
	return 1;
}
int ChuDui(BianDao *&q, int &e)     //出队
{
	if (q->front == q->rear)          //队空的情况
		return 0;
	q->front = (q->front + 1) % M;
	e = q->ChePai[q->front];
	return 1;
}
void ChaXunDui(BianDao *q)      //输出队中元素
{
	int i;
	i = (q->front + 1) % M;
	printf("%d ", q->ChePai[i]);
	while ((q->rear - i + M) % M>0)
	{
		i = (i + 1) % M;
		printf("%d ", q->ChePai[i]);
	}
	printf("\n");
}

//main函数用于模拟停车场的工作
 int main()
{
	int comm;
	int no, e1, time, e2;
	int i, j, t;
	TingCheChang *St, *St1;  //St是停车场，St1是在有车离开时，记录为该车移开位置的车辆
	BianDao *Qu;   //Qu是候车场
	ChuangJiang(St);
	ChuangJiang(St1);
	Dui(Qu);
	do
	{
		printf("输入指令(1:到达 2:离开 3:显示停车场 0:退出):");
		scanf_s("%d", &comm);
		switch (comm)
		{
		case 1:     /*汽车到达*/
			printf("输入车号和时间(设车号和时间均为整数): ");
			scanf_s("%d%d", &no, &time);
			if (!Mang(St))         //停车场不满
			{
				TingRu(St, no, time);
				printf("  >>停车场位置:%d\n", St->top + 1);
			}
			else                        //停车场满
			{
				if (!DuiMan(Qu))     //候车场不满
				{
					JinDui(Qu, no);
					printf("  >>候车场位置:%d\n", Qu->rear);
				}
				else
					printf("  >>候车场已满,不能停车\n");
			}
			break;
		case 2:     //汽车离开
			printf("输入车号和时间(车号和时间均为整数): ");
			scanf_s("%d%d", &no, &time);
			for (i = 0; i <= St->top && St->ChePaiHao2[i] != no; i++);  //在栈中找
			if (i>St->top)
				printf("  没有这辆车\n");
			else
			{
				t = St->top - i;  //需要出栈的车辆数目
				for (j = 0; j<t; j++) 
				{
					LiKai(St, e1, e2);
					TingRu(St1, e1, e2);        //倒车到临时栈St1中
				}
				LiKai(St, e1, e2);              //该汽车离开
				printf("%d停车费为:%d\n", no, (time - e2)*Price);
				while (!Kong(St1))    //将临时栈St1重新回到St中
				{
					LiKai(St1, e1, e2);
					TingRu(St, e1, e2);
				}
				if (!DuiKong(Qu))				//队不空时,将队头进栈St
				{
					ChuDui(Qu, e1);
					TingRu(St, e1, time);       //以当前时间开始计费
				}
			}
			break;
		case 3:     //显示停车场情况
			if (!Kong(St))
			{
				printf("  >>停车场中的车辆:");
				ChaXunZhan(St);//输出停车场中的车辆
				
			}
			else
				printf("  >>停车场中无车辆\n");
			break;
		case 0:     //结束
			if (!Kong(St))
			{
				printf("  >>停车场中的车辆:"); //输出停车场中的车辆
				
			}
			if (!DuiKong(Qu))
			{
				printf("  >>候车场中的车辆:"); //输出候车场中的车辆
				ChaXunDui(Qu);
			}
			break;
		default:    //其他情况
			printf("  >>输入的命令错误\n");
			break;

		}
	} while (comm != 0);
	printf("time函数莫名报错，无法显示时间\n");
	system("pause");

	return 0;
}