#pragma GCC optimize ("O3")
#include<stdio.h>
#include<stack>
using namespace std;
/*struct NODE
{
	NODE* link[20];
	int limit[9],n;
};*/

int main()
{
	stack<int> deci,zero;//decision,unfilled 
	//NODE node[81],*p;//nodes,tmp
	int link[81][20];
	int limit[81][9];
	int num[81];
	int n,i,j,p;//tmp
	bool pass;//flow judge
	char c;//tmp

	for(i=0;i!=81;i++)//link
	{
		n=0;
		for(j=0;j!=9;j++)
		{
			if(j!=i/9)//column
				link[i][n++]=j*9+i%9;
			if(j!=i%9)//row
				link[i][n++]=i/9*9+j;
			if(i/27*3+j/3 != i/9 && i%9/3*3+j%3 != i%9)//block
				link[i][n++]=i/27*27+j/3*9+i%9/3*3+j%3;
		}
	}
		
	scanf("%d",&n);
	while(n--)
	{
		for(i=0;i!=81;i++)//initial
		{
			limit[i][0]=0;
			limit[i][1]=0;
			limit[i][2]=0;
			limit[i][3]=0;
			limit[i][4]=0;
			limit[i][5]=0;
			limit[i][6]=0;
			limit[i][7]=0;
			limit[i][8]=0;
		}
				
		for(i=0;i!=81;i++)
		{
			scanf(" %c",&c);
			c-='1';
			num[i]=c;
			if(c!=-1)
				for(j=0;j!=20;j++)//constraint propagation
					limit[link[i][j]][c]++;
			else//unfiiled store
				zero.push(i);
		}
		
		while(!zero.empty())//until fulfill
		{
			pass=false;
			p=zero.top();

			for(i=0;i!=9;i++)//greed coloring
				if(!limit[p][i])
				{
					zero.pop();
					pass=true;
					for(j=0;j!=20;j++)
						limit[link[p][j]][i]++;
					num[p]=i;
					deci.push(p);//decision store
					break;
				}
			while(!pass)
			{
				p=deci.top();deci.pop();//backtrack
				for(j=0;j!=20;j++)
					limit[link[p][j]][num[p]]--;
				for(i=num[p]+1;i!=9;i++)
					if(!limit[p][i])
					{
						pass=true;
						for(j=0;j!=20;j++)
							limit[link[p][j]][i]++;
						num[p]=i;
						deci.push(p);
						break;
					}
				if(!pass)
					zero.push(p);
			}
		}
		while(!deci.empty())
			deci.pop();
		for(i=0;i!=81;i+=9)
			printf("%d%d%d%d%d%d%d%d%d\n",num[i]+1,num[i+1]+1,num[i+2]+1,num[i+3]+1,num[i+4]+1,num[i+5]+1,num[i+6]+1,num[i+7]+1,num[i+8]+1);
	}
	return 0;
}
