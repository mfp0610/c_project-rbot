/*
    drawbas.c

	Initial version: 2020.7.13
    Lastest update: 2020.7.21
    Author: mfp
*/
#include "headers.h"

void setbkcol(int color)
{
    bar(0,0,1024,768,color);
}

void line(int x1,int y1,int x2,int y2,int color)
{
    unsigned int  far *const video_buffer=(unsigned int  far *)0xa0000000L;
	unsigned char new_page = 0;
	unsigned long int page;
	int i,wid,yt;
    double k;
    if(x1==x2)
    {
        if(y1>y2) swap(&y1,&y2);
        for(i=y1;i<=y2;i++)
            Putpixel64k(x1,i,color);
        return;
    }
    if(y1==y2)
    {
	    if(x1>x2) swap(&x1,&x2);
        page=((unsigned long int)y1<<10)+x1;
	    new_page=page>>15;
		SelectPage(new_page);
	    for(i=0;i<x2-x1;i++)
            *(video_buffer+page+i)=color;
        return;
    }
    if(x1>x2)
    {
        swap(&x1,&x2);
        swap(&y1,&y2);
    }
    k=(y2-y1)*1.00/(x2-x1);
    for(i=x1;i<=x2;i++)
        Putpixel64k(i,(int) y1+(i-x1)*k,color);
    return;
}

void thick_line(int x1,int y1,int x2,int y2,int thick,int color)
{
    unsigned int  far *const video_buffer=(unsigned int  far *)0xa0000000L;
	unsigned char new_page = 0;
	unsigned long int page;
	int i,j,wid,thi=thick/2;
    double k;
    if(x1==x2)
    {
        if(y1>y2) swap(&y1,&y2);
        for(i=y1;i<=y2;i++)
        for(j=-thi;j<=thi;j++)    
            Putpixel64k(x1+j,i,color);
        return;
    }
    if(y1==y2)
    {
	    if(x1>x2) swap(&x1,&x2);
        for(i=x1;i<=x2;i++)
        for(j=-thi;j<=thi;j++)    
            Putpixel64k(i,y1+j,color);
        return;
    }
    if(x1>x2)
    {
        swap(&x1,&x2);
        swap(&y1,&y2);
    }
    k=(y2-y1)*1.00/(x2-x1);
    for(j=-thi;j<=thi;j++)
    for(i=x1;i<=x2;i++)
        Putpixel64k(i,(int)y1+(i-x1)*k+j,color);
    return;
}

void bar(int x1,int y1,int x2,int y2,int color)
{
    int i;
    if(x1>x2) swap(&x1,&x2);
    if(y1>y2) swap(&y1,&y2);
    for(i=y1;i<=y2;i++)
        line(x1,i,x2,i,color);
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

void drcircle(int xc,int yc,int r,int color)
{
    int x=0, y=r, dx=3, dy=2-2*r, d=1-r;
	if(r<=0) return;
	
	//运用Bresenham算法生成空心圆。
	while(x<=y)
	{
        Putpixel64k(xc-x,yc-y,color);
        Putpixel64k(xc+x,yc-y,color);
        Putpixel64k(xc-y,yc-x,color);
        Putpixel64k(xc+y,yc-x,color);
        Putpixel64k(xc-y,yc+x,color);
        Putpixel64k(xc+y,yc+x,color);
        Putpixel64k(xc-x,yc+y,color);
        Putpixel64k(xc+x,yc+y,color);
    
        if(d<0) d+=dx, dx+=2;
        else d+=(dx+dy), dx+=2, dy+=2, y--;
        x++;
	}
}

void fill_rect(int x1,int y1,int x2,int y2,int color,int edgecolor)
{
    bar(x1,y1,x2,y2,color);
    rect(x1,y1,x2,y2,edgecolor);
}

void fill_circle(int xc,int yc,int r,int color,int edgecolor)
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
    
        if(d<0) d+=dx, dx+=2;
        else d+=(dx+dy), dx+=2, dy+=2, y--;
        x++;
	}

    drcircle(xc,yc,r,edgecolor);
 }
