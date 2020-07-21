/*
    drawbas.c

	Initial version: 2020.7.13
    Lastest update: 2020.7.21
    Author: Mengfp
*/
#include "headers.h"

void setbkcol(int color)
{
    bar(0,0,1024,768,color);
}

void line(int x1,int y1,int x2,int y2,int color)
{
    int i;
    double k;
    if(x1==x2)
    {
        for(i=y1;i<=y2;i++)
            Putpixel64k(x1,i,color);
        return;
    }
    if(y1==y2)
    {
        for(i=x1;i<=x2;i++)
            Putpixel64k(i,y1,color);
        return;
    }
    k=(y2-y1)/(x2-x1);
    for(i=x1;i<=x2;i++)
        Putpixel64k(i,y1+(i-x1)*k,color);
    return;
}

void bar(int x1,int y1,int x2,int y2,int color)
{
    int i,j;
    if(x1>x2) swap(&x1,&x2);
    if(y1>y2) swap(&y1,&y2);
    for(i=x1;i<=x2;i++)
    for(j=y1;j<=y2;j++)
        Putpixel64k(i,j,color);
}

void rect(int x1,int y1,int x2,int y2,int color)
{
    if(x1>x2) swap(&x1,&x2);
    if(y1>y2) swap(&y1,&y2);
    line(x1,y1,x1,y2,color);
    line(x1,y1,x2,y1,color);
    line(x1,y2,x2,y2,color);
    line(x2,y1,x2,y2,color);
}

void fill_rect(int x1,int y1,int x2,int y2,int color)
{
    rect(x1,y1,x2,y2,BLACK);
    bar(x1,y1,x2,y2,color);
}

void fill_circle(int xc,int yc,int r,int color)
{
	int x=0, y=r, dx=3, dy=2-2*r, d=1-r;
	if(r<=0) return;
	
	//运用Bresenham算法生成实心圆。
	while(x<=y)
	{
        line(xc-x,yc-y,xc+x,yc-y,color);
        line(xc-y,yc-x,xc+y,yc-x,color);
        line(xc-y,yc+x,xc+y,yc+x,color);
        line(xc-x,yc+y,xc+x,yc+y,color);
    
        if(d<0)
        {
            d+=dx;
            dx+=2;
        }
        else
        {
            d+=(dx+dy);
            dx+=2, dy+=2;
            y--;
		}
        x++;
	}
 } 