#pragma GCC optimize ("O3")
#include<stdio.h>
#include<stack>
using namespace std;

int main()
{
	stack<int> deci,zero;//decision,unfilled 
	int link[81][20];
	int limit[81][9]={};
	int num[81];
	int n,i,j,r,c,prep=-1,p;//tmp
	bool pass;//flow judge

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
	
	while(~scanf("%d-%d %d", &r, &c, &n))
	{
		p=(r-1)*9+c-1;
		for(prep++;prep<p;prep++)
			zero.push(prep);
		num[p]=n-1;
		for(i=0;i!=20;i++)//constraint propagation
			limit[link[p][i]][n-1]++;
	}
	for(prep++;prep<81;prep++)
		zero.push(prep);
	
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
	{
		p=deci.top();deci.pop();
		printf("%d-%d %d\n", p/9+1, p%9+1, num[p]+1);
	}
	
	return 0;
}
