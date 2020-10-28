/*
    mysys.c
    
    Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: mfp & hhw
*/
#include "headers.h"

void Delaytime(int time)
{
    int i,j,k;
 	for(i=0;i<time;i++)
	{for(j=0;j<1100;j++)
	for(k=0;k<100;k++);}
}

void swap(int *x,int *y)
{
	int t=0;
	t=*x, *x=*y, *y=t;
}

void nocombo()
{
    Delaytime(100);
}

int sign(int x)
{
    if(x>0) return 1;
    if(x<0) return -1;
    return 0;
}

int randin(int x)
{
    int t;
    srand((unsigned)time(NULL));
    t=rand()%x;
    return t;
}