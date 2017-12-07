#pragma GCC optimize ("O3")
#include<stdio.h>
#include<stack>
using namespace std;
struct NODE
{
	NODE* link[20];
	int limit[9],n;
};

int main()
{
	stack<NODE*> deci,zero;//decision,unfilled 
	NODE node[81],*p;//nodes,tmp
	int n,i,j;//tmp
	bool pass;//flow judge
	char c;//tmp

	for(i=0;i!=81;i++)//link
	{
		n=0;
		for(j=0;j!=9;j++)
		{
			if(j!=i/9)//column
				node[i].link[n++]=node+j*9+i%9;
			if(j!=i%9)//row
				node[i].link[n++]=node+i/9*9+j;
			if(i/27*3+j/3 != i/9 && i%9/3*3+j%3 != i%9)//block
				node[i].link[n++]=node+i/27*27+j/3*9+i%9/3*3+j%3;
		}
	}
		
	scanf("%d",&n);
	while(n--)
	{
		for(i=0;i!=81;i++)//initial
		{
			node[i].limit[0]=0;
			node[i].limit[1]=0;
			node[i].limit[2]=0;
			node[i].limit[3]=0;
			node[i].limit[4]=0;
			node[i].limit[5]=0;
			node[i].limit[6]=0;
			node[i].limit[7]=0;
			node[i].limit[8]=0;
		}
				
		for(i=0;i!=81;i++)
		{
			scanf(" %c",&c);
			c-='1';
			node[i].n=c;
			if(c!=-1)
				for(j=0;j!=20;j++)//constraint propagation
					node[i].link[j]->limit[c]++;
			else//unfiiled store
				zero.push(node+i);
		}
		
		while(!zero.empty())//until fulfill
		{
			pass=false;
			p=zero.top();

			for(i=0;i!=9;i++)//greed coloring
				if(!p->limit[i])
				{
					zero.pop();
					pass=true;
					for(j=0;j!=20;j++)
						p->link[j]->limit[i]++;
					p->n=i;
					deci.push(p);//decision store
					break;
				}
			while(!pass)
			{
				p=deci.top();deci.pop();//backtrack
				for(j=0;j!=20;j++)
					p->link[j]->limit[p->n]--;
				for(i=p->n+1;i!=9;i++)
					if(!p->limit[i])
					{
						pass=true;
						for(j=0;j!=20;j++)
							p->link[j]->limit[i]++;
						p->n=i;
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
			printf("%d%d%d%d%d%d%d%d%d\n",node[i].n+1,node[i+1].n+1,node[i+2].n+1,node[i+3].n+1,node[i+4].n+1,node[i+5].n+1,node[i+6].n+1,node[i+7].n+1,node[i+8].n+1);
	}
	return 0;
}
