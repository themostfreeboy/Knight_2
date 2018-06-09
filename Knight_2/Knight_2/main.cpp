/*
此程序每次选择方向时均选择下一步方向选择数最少的那一个方向，这样可以降低回溯次数，提高效率(此程序的横纵坐标整个弄反了，此处不修改了，就把所有x以及注释中说明为横坐标的部分当做纵坐标，所有y以及注释中说明为纵坐标的部分当做横坐标即可)(此程序中的x和y实际指的是第x行第y列(从0开始)，并不是指坐标)
*/

#include <stdio.h>
#include <stdlib.h>

#define num 100

const int dx[8]={1,1,-1,-1,2,2,-2,-2};
const int dy[8]={2,-2,2,-2,1,-1,1,-1};
int data[8][8];//用于记录某点是否已经走过或者走过的顺序
int direction_k[8];//用于记录每一步的方向(对应于dx和dy的数组下标)是否已经探测过

class mydata
{
public:
	int x;//横坐标
	int y;//纵坐标
	int direction[8];//记录下一步的方向(即dx和dy数组的数组下标)哪些已经试探完毕
	mydata(){};
	mydata(int i,int j,const int dir[8]):x(i),y(j){for(int k=0;k<8;k++)    direction[k]=dir[k];}
};

class stack
{
public:
	mydata data[num];
	int top;
	void push(mydata x);//入栈
	mydata pop();//出栈
	bool Full();//栈满
	bool Empty();//栈空
	stack():top(-1){};
	void copy(stack *s);//栈内内容复制
};

void stack::push(mydata x)//入栈
{
	if(top<num-1)    data[++top]=x;
}

mydata stack::pop()//出栈
{
	if(top>-1)    return data[top--];
}

bool stack::Full()//栈满
{
	return (top==num-1)?true:false;
}

bool stack::Empty()//栈空
{
	return (top==-1)?true:false;
}

void stack::copy(stack *s)//栈内内容复制
{
	for(int i=0;i<=s->top;i++)
	{
		push(s->data[i]);
	}
}

int CalculateCount(int x,int y)//计算下一步可行的方向数
{
	int count=0;
	for(int k=0;k<8;k++)
	{
		if(x+dx[k]>=0 && x+dx[k]<8 && y+dy[k]>=0 && y+dy[k]<8 && data[x+dx[k]][y+dy[k]]==0)//此方向可行
		{
			count++;
		}
	}
	return count;
}

int CalculateDirection(int x,int y)//计算下一步最小方向数的方向
{
	int direction=-1;
	int mincount=9;
	for(int k=0;k<8;k++)
	{
		if(x+dx[k]>=0 && x+dx[k]<8 && y+dy[k]>=0 && y+dy[k]<8 && data[x+dx[k]][y+dy[k]]==0 && direction_k[k]==0)//此方向可行且未被试探过
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
	int position_x=0;//初始横坐标
	int position_y=0;//初始纵坐标
	bool result=false;//用于记录是否能够完成遍历
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			data[i][j]=0;
	for(int i=0;i<8;i++)
		direction_k[i]=0;
	data[position_x][position_y]=1;
	int i=0;//横坐标
	int j=0;//纵坐标
	int step=0;//用于记录步数
	int tempdir=-1;
	stack *s=new stack;
    i=position_x;
	j=position_y;
	step++;
	data[i][j]=step;
	while(true)
	{
		if(s->Empty() && CalculateDirection(i,j)==-1)//如果栈已弹空且下一步的所有方向均不符合条件，则说明无法完成遍历，退出循环
		{
			result=false;
			break;
		}
		if((tempdir=CalculateDirection(i,j))!=-1)//找到了拥有最小方向数的方向
		{
			direction_k[tempdir]=1;//必须先将此方向设置为已经探测过再进行压栈，否则弹栈后无法获知该方向是否已经探测过
			mydata md(i,j,direction_k);
		    s->push(md);
			i=i+dx[tempdir];
			j=j+dy[tempdir];
			step++;
			data[i][j]=step;
			for(int k=0;k<8;k++)    direction_k[k]=0;//必须将所有方向均设置为未探测，才可以进行下一步的探测
		}
		else if(step==64)//下一步的所有方向均不符合条件(CalculateDirection(i,j)==-1)，但是已经遍历完整个棋盘，可以退出循环
		{
			result=true;
			break;
		}
		else//下一步的所有方向均不符合条件(CalculateDirection(i,j)==-1)，但是尚未遍历完整个棋盘，则回溯，弹栈
		{
			data[i][j]=0;//必须先将此位置的data置为0，再弹栈，否则弹栈后无法再次找到此位置
			mydata md=s->pop();
			i=md.x;
			j=md.y;
			for(int k=0;k<8;k++)    direction_k[k]=md.direction[k];//弹栈后，必须将所有方向均设置为未探测，才可以进行下一步的探测
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
		printf("无法完成遍历\n");
	}
	system("pause");
	return 0;
}