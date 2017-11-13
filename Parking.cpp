#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define N 10                    //ͣ����������ͣ����
#define M 10                    //���������ͣ����
#define Price 5             //һ����λʱ���շ�5Ԫ

typedef struct
{
	int ChePaiHao2[N];           //���ƺ�
	int JinChangShiJian[N];         //����ʱ��
	int top;                //ջָ��
} TingCheChang;                  

typedef struct
{
	int ChePai[M];           //���ƺ�
	int front, rear;         //���׺Ͷ�βָ��
} BianDao;                  

							
void ChuangJiang(TingCheChang *&s)		//����˳��ջ
{
	s = (TingCheChang *)malloc(sizeof(TingCheChang));
	s->top = -1;
}
int Kong(TingCheChang *s)		//ͣ����Ϊ��
{
	return(s->top == -1);
}
int Mang(TingCheChang *s)		//ͣ����Ϊ��
{
	return(s->top == N - 1);
}
int TingRu(TingCheChang *&s, int e1, int e2)	  //����ͣ��
{
	if (s->top == N - 1)
		return 0;
	s->top++;
	s->ChePaiHao2[s->top] = e1;
	s->JinChangShiJian[s->top] = e2;
	return 1;
}
int LiKai(TingCheChang *&s, int &e1, int &e2)	 //�����뿪
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

/*����Ϊѭ�����еĻ��������㷨*/
void Dui(BianDao *&q)		//��������
{
	q = (BianDao *)malloc(sizeof(BianDao));
	q->front = q->rear = 0;
}
int DuiKong(BianDao *q)		//	�ж϶ӿ�
{
	return(q->front == q->rear);
}
int DuiMan(BianDao *q)       //�ж϶���
{
	return ((q->rear + 1) % M == q->front);
}
int JinDui(BianDao *&q, int e)      //����
{
	if ((q->rear + 1) % M == q->front)    //����
		return 0;
	q->rear = (q->rear + 1) % M;
	q->ChePai[q->rear] = e;
	return 1;
}
int ChuDui(BianDao *&q, int &e)     //����
{
	if (q->front == q->rear)          //�ӿյ����
		return 0;
	q->front = (q->front + 1) % M;
	e = q->ChePai[q->front];
	return 1;
}
void ChaXunDui(BianDao *q)      //�������Ԫ��
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

//main��������ģ��ͣ�����Ĺ���
 int main()
{
	int comm;
	int no, e1, time, e2;
	int i, j, t;
	TingCheChang *St, *St1;  //St��ͣ������St1�����г��뿪ʱ����¼Ϊ�ó��ƿ�λ�õĳ���
	BianDao *Qu;   //Qu�Ǻ򳵳�
	ChuangJiang(St);
	ChuangJiang(St1);
	Dui(Qu);
	do
	{
		printf("����ָ��(1:���� 2:�뿪 3:��ʾͣ���� 0:�˳�):");
		scanf_s("%d", &comm);
		switch (comm)
		{
		case 1:     /*��������*/
			printf("���복�ź�ʱ��(�賵�ź�ʱ���Ϊ����): ");
			scanf_s("%d%d", &no, &time);
			if (!Mang(St))         //ͣ��������
			{
				TingRu(St, no, time);
				printf("  >>ͣ����λ��:%d\n", St->top + 1);
			}
			else                        //ͣ������
			{
				if (!DuiMan(Qu))     //�򳵳�����
				{
					JinDui(Qu, no);
					printf("  >>�򳵳�λ��:%d\n", Qu->rear);
				}
				else
					printf("  >>�򳵳�����,����ͣ��\n");
			}
			break;
		case 2:     //�����뿪
			printf("���복�ź�ʱ��(���ź�ʱ���Ϊ����): ");
			scanf_s("%d%d", &no, &time);
			for (i = 0; i <= St->top && St->ChePaiHao2[i] != no; i++);  //��ջ����
			if (i>St->top)
				printf("  û��������\n");
			else
			{
				t = St->top - i;  //��Ҫ��ջ�ĳ�����Ŀ
				for (j = 0; j<t; j++) 
				{
					LiKai(St, e1, e2);
					TingRu(St1, e1, e2);        //��������ʱջSt1��
				}
				LiKai(St, e1, e2);              //�������뿪
				printf("%dͣ����Ϊ:%d\n", no, (time - e2)*Price);
				while (!Kong(St1))    //����ʱջSt1���»ص�St��
				{
					LiKai(St1, e1, e2);
					TingRu(St, e1, e2);
				}
				if (!DuiKong(Qu))				//�Ӳ���ʱ,����ͷ��ջSt
				{
					ChuDui(Qu, e1);
					TingRu(St, e1, time);       //�Ե�ǰʱ�俪ʼ�Ʒ�
				}
			}
			break;
		case 3:     //��ʾͣ�������
			if (!Kong(St))
			{
				printf("  >>ͣ�����еĳ���:");
				ChaXunZhan(St);//���ͣ�����еĳ���
				
			}
			else
				printf("  >>ͣ�������޳���\n");
			break;
		case 0:     //����
			if (!Kong(St))
			{
				printf("  >>ͣ�����еĳ���:"); //���ͣ�����еĳ���
				
			}
			if (!DuiKong(Qu))
			{
				printf("  >>�򳵳��еĳ���:"); //����򳵳��еĳ���
				ChaXunDui(Qu);
			}
			break;
		default:    //�������
			printf("  >>������������\n");
			break;

		}
	} while (comm != 0);
	printf("time����Ī�������޷���ʾʱ��\n");
	system("pause");

	return 0;
}