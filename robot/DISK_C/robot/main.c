#include<stdio.h>
#include"test1.h"
int main()
{
	int a,b,c,d;
	scanf("%d%d",&a,&b);
	c=add(a,b);
	d=sub(a,b);
	printf("%d %d\n",c,d);
	return 0;
}