/*
    drawbas.c

    Partly adapted by pervious version
	Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: Mengfp
*/
#include "headers.h"

#define PI 3.1415926

  void linelevel(int x0,int y0,int x1,int y1,int thick,int color)
  {
   int i,j,k;
   if(x0>x1)                                       /*确保x0为较小的一方*/
   {
	k=x0;
	x0=x1;
	x1=k;
   }

   if(x1<=0||x1>=1024||y1<=0||y1>=768||x1>=1024)  /*确保画线在屏幕范围之内*/
	{
		printf("the line is beyond the screen!");
		return;
	}

   for(i=0;i<thick;i++)
   {
	for(j=0;j<x1-x0;j++)
	{
		Putpixel64k(x0+j,y0+i,color);
	}
   }
 }

void linever(int x0,int y0,int x1,int y1,int thick,int color)
  {
	int   i = 0;
	int   j = 0;
	//int   k=0;
   int high;
   high = y1 - y0;
  	/* if(y0>y1)                                       确保y0为较小的一方
   	{
		k=y0;
		y0=y1;
		y1=k;
   	}  
   	*/
   	if(x1<=0||x1>=1024||y1<=0||y1>=768||x1>=1024)  /*确保画线在屏幕范围之内*/
	{
		printf("the line is beyond the screen!");
		return;
	}

   	for(i=0;i<thick;i++)
   	for(j=0;j<high;j++)
		Putpixel64k(x0+i,y0+j,color);	
}



void Horizline(int x, int y, int width, int  color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int  far * const video_buffer = (unsigned int  far *)0xa0000000L;

	/*要切换的页面号*/
	unsigned char new_page = 0;

//	unsigned char old_page = 0;
	/*对应显存地址偏移量*/
	unsigned long int page;

	/*i是x的临时变量，后作循环变量*/
	int i;

	/*判断延伸方向，让起始点靠左*/
	if (width < 0)
	{
		x = x + width;
		width = -width;
	}

	i = x;

	/*省略超出屏幕左边部分*/
	if (x < 0)
	{
		x = 0;
		width += i;
	}

	/*整条线在屏幕外时退出*/
	if (x >= 1024)
	{
		return;
	}

	/*整条线在屏幕外时退出*/
	if (y < 0 || y >= 768)
	{
		return;
	}

	/*省略超出屏幕右边部分*/
	if (x + width > 1024)
	{
		width = 1024 - x;
	}

	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	new_page = page >> 15;
	
		SelectPage(new_page);
	
	/*向显存写入颜色，水平线画出*/
	for(i=0;i<width;i++)
	{
		*(video_buffer + page + i) = color;
	}
}

void bar(int x0, int y0, int x1, int y1, int color)
{

	int i;

	int wide;                /*计算矩形的长和宽*/
	wide = x1 - x0;


	for (i = y0; i <= y1; i++)
	{
		Horizline(x0, i, wide, color);
	}
}

 void circle(int x0,int y0,int radius,int color)
 {
  
	int x, y, d;
	y = radius;
	d = 3 - radius << 1;
	
	for (x = 0; x <= y; x++)
	{
		Putpixel64k(x0 + x, y0 + y, color);
		Putpixel64k(x0 + x, y0 - y, color);
		Putpixel64k(x0 - x, y0 - y, color);
		Putpixel64k(x0 - x, y0 + y, color);
		Putpixel64k(x0 + y, y0 + x, color);
		Putpixel64k(x0 + y, y0 - x, color);
		Putpixel64k(x0 - y, y0 - x, color);
		Putpixel64k(x0 - y, y0 + x, color);
		
		if (d < 0)
		{
			d += x * 4 + 6;
		}
		
		else
		{
			d += (x - y) * 4 + 10;
			y--;
		}
	}
}



 void FillCircle(/*int x, int y, int r, int color*/int xc, int yc, int radius, int color)
{
	/*画圆圈的定位变量和决策变量*/
	int x = 0,
		y = radius,
		dx = 3,
		dy = 2 - radius - radius,
		d = 1 - radius;
	
	
	/*半径必须为正，否则退出*/
	if (radius <= 0)
	{
		return;
	}
	
	/************************************
	以下运用Bresenham算法生成实心圆。
	该算法是得到公认的成熟的快速算法。
	具体细节略去。
	************************************/
	while (x <= y)
	{
		Horizline(xc - x, yc - y, x + x, color);
        Horizline(xc - y, yc - x, y + y, color);
        Horizline(xc - y, yc + x, y + y, color);
        Horizline(xc - x, yc + y, x + x, color);
        
        if (d < 0)
        {
            d += dx;
            dx += 2;
        }
        
        else
        {
            d += (dx + dy);
            dx += 2;
            dy += 2;
            y--;
		}

        x++;
	}
 } 
 
 
void bow(int x0,int y0,int r,int color)//弧度固定
{
	int x,y,d;
	y = r;
	d = 3-r<<1;
	
	for(x=0;x<=y/4;x++)
	{
		Putpixel64k(x0 + x, y0 + y, color);
		Putpixel64k(x0 - x, y0 + y, color);
	    if(d<0)
		{
			d+=x*4+6;
		}
		else{
			d+=(x-y)*4+10;
			y--;
		}
	}
}




//画竖直方向实心椭圆
void HER_Fillellipse(int x1,int y1,int x2,int y2,int r,int color) 
{
	FillCircle(x1,y1,r,color);
	FillCircle(x2,y2,r,color);
	bar(x1-r,y1,x2+r,y2,color);
}//参数：两个圆心坐标，半径，颜色

//画水平方向实心椭圆
void HOR_Fillellipse(int x1,int y1,int x2,int y2,int r,int color)
{
	FillCircle(x1,y1,r,color);
	FillCircle(x2,y2,r,color);
	bar(x1,y1-r,x2,y2+r,color);
}//参数：两个圆心坐标，半径，颜色

//画空心椭圆
void ellipse(int x1,int y1,int x2,int y2,int r,int color)
{
	semicircle_up(x2,y2,r,color);
	semicircle_down(x1,y1,r,color);
	linever(x1-r,y1,x1-r,y2,1,color);
	linever(x2+r,y1,x2+r,y2,1,color);
}//参数：两个圆心坐标，半径，颜色

//画空心上半圆
void semicircle_up(int x0,int y0,int r,int color)
{
	int x,y,d;
	y=r, d=3-r<< 1;
	for(x=0;x<=y;x++)
	{
		Putpixel64k(x0+x,y0+y,color);
		Putpixel64k(x0-x,y0+y,color);
		Putpixel64k(x0+y,y0+x,color);
		Putpixel64k(x0-y,y0+x,color);
		if(d<0) d+=x*4+6;
		else d+=(x-y)*4+10, y--;
	}
}

//画空心下半圆
void semicircle_down(int x0,int y0,int r,int color)
{
	int x,y,d;
	y=r, d=3-r<<1;
	for(x=0;x<=y;x++)
	{
		Putpixel64k(x0+x,y0-y,color);
		Putpixel64k(x0-x,y0-y,color);
		Putpixel64k(x0+y,y0-x,color);
		Putpixel64k(x0-y,y0-x,color);
		if(d<0) d+=x*4+6;
		else d+=(x-y)*4+10, y--;
	}
}

//实心上半圆
void Half_Circle(int xc,int yc,int rad,unsigned int color)
{
	int x=0, y=rad, dx=3, dy=2-2*rad, d=1-rad;
	if(rad<= 0) return;

	//运用Bresenham算法生成实心圆。
	while(x<=y)
	{
		linelevel(xc-x,yc-y,xc+x,yc-y,1,color);
		linelevel(xc-y,yc-x,xc+y,yc-x,1,color);
		if(d<0) d+=dx, dx+=2;
		else
		{
			d+=(dx+dy);
			dx+=2;
			dy+=2;
			y--;
		}
		x++;
	}
}

//四个画四分之一弧，空心
void bow_right_up(int x,int y,int r,int color)
{
	int tx=0,d;
	while(tx<=r)
	{
		d=sqrt(r*r-tx*tx);
		Putpixel64k(x+d,y-tx,color);
		tx++;
	}
}

void bow_right_down(int x,int y,int r,int color)
{
	int tx=0,d;
	while(tx<=r)
	{
		d=sqrt(r*r-tx*tx);
		Putpixel64k(x+d,y+tx,color);
		tx++;
	}
}

void bow_left_up(int x,int y,int r,int color)
{
	int tx=0,d;
	while(tx<=r)
	{
		d=sqrt(r*r-tx*tx);
		Putpixel64k(x-d,y-tx,color);
		tx++;
	}
}

void bow_left_down(int x,int y,int r,int color)
{
	int tx=0,d;
	while(tx<=r)
	{
		d=sqrt(r*r-tx*tx);
		Putpixel64k(x-d,y+tx,color);
		tx++;
	}
}

//画实心四分之一圆
void fill_bow_right_up(int x,int y,int r,int color)
{
	int tx=0, ty=r, d=3-2*r, i;
	while(tx<ty)
	{
		//画水平两点连线(<45度)
		for(i=x;i<=x+ty;i++)
			Putpixel64k(i, y-tx,color);
		if(d<0) d+=4*tx+6;
		else
		{
			//画水平两点连线(>45度)
			for(i=x;i<=x+tx;i++)
				Putpixel64k(i,y-ty,color);
			d+=4*(tx-ty)+10, ty--;
		}
		tx++;
	}
	if(tx==ty) //画水平两点连线(=45度)
		for(i=x;i<=x+ty;i++)
			Putpixel64k(i,y-tx,color);
}

void fill_bow_left_up(int x,int y,int r,int color)
{
	int tx=0,ty=r,i;
	double sx;
	while(tx<ty)
	{
		sx=sqrt(r*r-tx*tx);
		for(i=x-sx;i<=x;i++)
			Putpixel64k(i,y-tx,color);
		tx++;
	}
}

void fill_bow_right_down(int x,int y,int r,int color)
{
	int tx=0,ty=r,i;
	double sx;
	while(tx<ty)
	{
		sx=sqrt(r*r-tx*tx);
		for(i=x;i<=x+sx;i++)
			Putpixel64k(i,y+tx,color);
		tx++;
	}
}

void fill_bow_left_down(int x,int y,int r,int color)
{
	int tx=0,ty=r,i;
	double sx;
	while(tx<ty)
	{
		sx=sqrt(r*r-tx*tx);
		for(i=x-sx;i<=x;i++)
			Putpixel64k(i,y+tx,color);
		tx++;
	}
}

void fill_bow_down(int x,int y,int r,int color)
{
	int tx=0,ty=r,i;
	float d=r/1.414;
	double sx;
	while(tx<ty)
	{
		if(tx<d)
			for(i=x-tx;i<=x+tx;i++)
			    Putpixel64k(i,y+tx,color);
        else
			for(i=x-sx;i<=x+sx;i++)
				Putpixel64k(i,y+tx,color);
		tx++;
		sx=sqrt(r*r-tx*tx);
	}
}

void fill_bow_up(int x,int y,int r,int color)
{
	int tx = 0, ty = r,i;
	float d = r/1.414;
	double sx;
	while(tx<ty)
	{
		if(tx<d)
			for(i=x-tx;i<=x+tx;i++)
			    Putpixel64k(i,y-tx,color);
        else
			for(i=x-sx;i<=x+sx;i++)
				Putpixel64k(i,y-tx,color);
		tx++;
		sx = sqrt(r*r-tx*tx);
	}
}

void fill_bow_left(int x,int y,int r,int color)
{
	int ty = 0, tx = r,i;
	float d = r/1.414;
	double sy;
	while(ty<tx)
	{
		if(ty<d)
			for(i=y-ty;i<=y+ty;i++)
			    Putpixel64k(x-ty,i,color);
        else
			for(i=y-sy;i<=y+sy;i++)
				Putpixel64k(x-ty,i,color);
		ty++;
		sy = sqrt(r*r-ty*ty);
	}
}

void fill_bow_right(int x,int y,int r,int color)
{
	int ty = 0, tx = r,i;
	float d = r/1.414;
	double sy;
	while(ty<tx)
	{
		if(ty<d)
			for(i=y-ty;i<=y+ty;i++)
			    Putpixel64k(x+ty,i,color);
        else
			for(i=y-sy;i<=y+sy;i++)
				Putpixel64k(x+ty,i,color);
		ty++;
		sy = sqrt(r*r-ty*ty);
	}
}

//圆角矩形
void bar_round(int x,int y,int length,int height,int r,int thick,int color)
{
	bar(x-length/2+r,y-height/2,x+length/2-r,y+height/2,color);
	bar(x-length/2,y-height/2+r,x+length/2,y+height/2-r,color);
	fill_bow_left_up(x-length/2+r,y-height/2+r,r,color);
	fill_bow_left_down(x-length/2+r,y+height/2-r,r,color);
	fill_bow_right_up(x+length/2-r,y-height/2+r,r,color);
	fill_bow_right_down(x+length/2-r,y+height/2-r,r,color);
	linelevel(x-length/2+r,y-height/2,x+length/2-r,y-height/2,thick,color);
	linelevel(x-length/2+r,y+height/2,x+length/2-r,y+height/2,thick,color);
	linever(x-length/2,y-height/2+r,x-length/2,y+height/2-r,thick,color);
	linever(x+length/2,y-height/2+r,x+length/2,y+height/2-r,thick,color);
    bow_right_up(x+length/2-r,y-height/2+r,r,color);
	bow_left_up(x-length/2+r,y-height/2+r,r,color);
	bow_left_down(x-length/2+r,y+height/2-r,r,color);
	bow_right_down(x+length/2-r,y+height/2-r,r,color);
}

void bar_round_2(int x0,int y0,int x1,int y1,int r,int thick,int color)
{
	int length, height, x, y;
	length=x1-x0;
	height=y1-y0;
	x=(x1+x0)/2;
	y=(y1+y0)/2;
	bar_round(x,y,length,height,r,thick,color);
}

void bar_round_with_shadow(int x,int y,int length,int height,int r,int thick,int color)
{
	bar(x-length/2+r,y-height/2,x+length/2-r,y+height/2,color);
	bar(x-length/2,y-height/2+r,x+length/2,y+height/2-r,color);
	fill_bow_left_up(x-length/2+r,y-height/2+r,r,color);
	fill_bow_left_down(x-length/2+r,y+height/2-r,r,color);
	fill_bow_right_up(x+length/2-r,y-height/2+r,r,color);
	fill_bow_right_down(x+length/2-r,y+height/2-r,r,color);
	linelevel(x-length/2+r,y-height/2,x+length/2-r,y-height/2,thick,65535);
	linelevel(x-length/2+r,y+height/2,x+length/2-r,y+height/2,thick*3,0);
	linever(x-length/2,y-height/2+r,x-length/2,y+height/2-r,thick,65535);
	linever(x+length/2,y-height/2+r,x+length/2,y+height/2-r,thick*2,0);
    bow_right_up(x+length/2-r,y-height/2+r,r,0);
	bow_left_up(x-length/2+r,y-height/2+r,r,65535);
	bow_left_down(x-length/2+r,y+height/2-r,r,65535);
	bow_right_down(x+length/2-r,y+height/2-r,r,0);
}

//斜线
void lean_line(int x,int y,int length,int theta,int color) //x,y为线段的起点
{
	double right_x;
	double i,y0;
	double theta0=((double)(theta))/180*PI;
	right_x=x+cos(theta0)*(length), y0=y;
	if((int)(theta)<=90)
	{
		for(i=x;i<=right_x;i++)
	    {
		    Putpixel64k(i,y0,color);
		    y0+=tan(theta0);
	    }
	}
	else
	{
		for(i=x;i>=right_x;i--)
	    {
		    Putpixel64k(i,y0,color);
		    y0+=tan(theta0);
	    }
	}
}

//通过加粗斜线画出平行四边形
void lean_line_thick(int x,int y,int length,int theta,int thick,int color) //x,y为矩形左上角坐标
{
	int i;
	for(i=0;i<thick;i++)
		lean_line(x+i,y,length,theta,color);
}