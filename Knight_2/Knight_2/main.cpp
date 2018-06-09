/*
�˳���ÿ��ѡ����ʱ��ѡ����һ������ѡ�������ٵ���һ�������������Խ��ͻ��ݴ��������Ч��(�˳���ĺ�����������Ū���ˣ��˴����޸��ˣ��Ͱ�����x�Լ�ע����˵��Ϊ������Ĳ��ֵ��������꣬����y�Լ�ע����˵��Ϊ������Ĳ��ֵ��������꼴��)(�˳����е�x��yʵ��ָ���ǵ�x�е�y��(��0��ʼ)��������ָ����)
*/

#include <stdio.h>
#include <stdlib.h>

#define num 100

const int dx[8]={1,1,-1,-1,2,2,-2,-2};
const int dy[8]={2,-2,2,-2,1,-1,1,-1};
int data[8][8];//���ڼ�¼ĳ���Ƿ��Ѿ��߹������߹���˳��
int direction_k[8];//���ڼ�¼ÿһ���ķ���(��Ӧ��dx��dy�������±�)�Ƿ��Ѿ�̽���

class mydata
{
public:
	int x;//������
	int y;//������
	int direction[8];//��¼��һ���ķ���(��dx��dy����������±�)��Щ�Ѿ���̽���
	mydata(){};
	mydata(int i,int j,const int dir[8]):x(i),y(j){for(int k=0;k<8;k++)    direction[k]=dir[k];}
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//��ջ
	mydata pop();//��ջ
	bool Full();//ջ��
	bool Empty();//ջ��
	stack():top(-1){};
	void copy(stack *s);//ջ�����ݸ���
};

void stack::push(mydata x)//��ջ
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//��ջ
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//ջ��
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//ջ��
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//ջ�����ݸ���
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int CalculateCount(int x,int y)//������һ�����еķ�����
{
	int count=0;
	for(int k=0;k<8;k++)
	{
		if(x+dx[k]>=0 && x+dx[k]<8 && y+dy[k]>=0 && y+dy[k]<8 && data[x+dx[k]][y+dy[k]]==0)//�˷������
		{
			count++;
		}
	}
	return count;
}

int CalculateDirection(int x,int y)//������һ����С�������ķ���
{
	int direction=-1;
	int mincount=9;
	for(int k=0;k<8;k++)
	{
		if(x+dx[k]>=0 && x+dx[k]<8 && y+dy[k]>=0 && y+dy[k]<8 && data[x+dx[k]][y+dy[k]]==0 && direction_k[k]==0)//�˷��������δ����̽��
		{
			if(mincount>CalculateCount(x+dx[k],y+dy[k]))
			{
				mincount=CalculateCount(x+dx[k],y+dy[k]);
				direction=k;
			}
		}
	}
	return direction;
}

int main()
{
	int position_x=0;//��ʼ������
	int position_y=0;//��ʼ������
	bool result=false;//���ڼ�¼�Ƿ��ܹ���ɱ���
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			data[i][j]=0;
	for(int i=0;i<8;i++)
		direction_k[i]=0;
	data[position_x][position_y]=1;
	int i=0;//������
	int j=0;//������
	int step=0;//���ڼ�¼����
	int tempdir=-1;
	stack *s=new stack;
    i=position_x;
	j=position_y;
	step++;
	data[i][j]=step;
	while(true)
	{
		if(s->Empty() && CalculateDirection(i,j)==-1)//���ջ�ѵ�������һ�������з������������������˵���޷���ɱ������˳�ѭ��
		{
			result=false;
			break;
		}
		if((tempdir=CalculateDirection(i,j))!=-1)//�ҵ���ӵ����С�������ķ���
		{
			direction_k[tempdir]=1;//�����Ƚ��˷�������Ϊ�Ѿ�̽����ٽ���ѹջ������ջ���޷���֪�÷����Ƿ��Ѿ�̽���
			mydata md(i,j,direction_k);
		    s->push(md);
			i=i+dx[tempdir];
			j=j+dy[tempdir];
			step++;
			data[i][j]=step;
			for(int k=0;k<8;k++)    direction_k[k]=0;//���뽫���з��������Ϊδ̽�⣬�ſ��Խ�����һ����̽��
		}
		else if(step==64)//��һ�������з��������������(CalculateDirection(i,j)==-1)�������Ѿ��������������̣������˳�ѭ��
		{
			result=true;
			break;
		}
		else//��һ�������з��������������(CalculateDirection(i,j)==-1)��������δ�������������̣�����ݣ���ջ
		{
			data[i][j]=0;//�����Ƚ���λ�õ�data��Ϊ0���ٵ�ջ������ջ���޷��ٴ��ҵ���λ��
			mydata md=s->pop();
			i=md.x;
			j=md.y;
			for(int k=0;k<8;k++)    direction_k[k]=md.direction[k];//��ջ�󣬱��뽫���з��������Ϊδ̽�⣬�ſ��Խ�����һ����̽��
			step--;
			continue;
		}
	}
	delete s;
	if(result==true)
	{
	    for(i=0;i<8;i++)
	    {
		    for(j=0;j<8;j++)
			{
				printf("%d\t",data[i][j]);
			}
		    printf("\n");
	    }
	}
	else if(result==false)
	{
		printf("�޷���ɱ���\n");
	}
	system("pause");
	return 0;
}