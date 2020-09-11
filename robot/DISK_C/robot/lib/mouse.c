/*
    mouse.c
    
    Adapted by pervious version
    Initial version: 2020.7.19
    Lastest update: 2020.9.11 
*/
#include "headers.h"

int MouseX, MouseY, MouseS, press;
void *buffer;
union REGS regs;
int flag=0;
int mousesave[13][20];

void mouseinit()//初始化
{
	int retcode;
	int xmin, xmax, ymin, ymax;
	int x_max=1024, y_max=768, size;

	xmin=2, xmax=x_max-1, ymin=8, ymax=y_max-2;
	regs.x.ax=0;
	int86(51,&regs,&regs);
	retcode=regs.x.ax;
	if(retcode==0)
	{
		printf("Mouse or Mouse Driver Obsent,Please Install!");
		delay(5000);
	}
	else
	{
		regs.x.ax=7;
		regs.x.cx=xmin;
		regs.x.dx=xmax;
		int86(51,&regs,&regs);
		regs.x.ax=8;
		regs.x.cx=ymin;
		regs.x.dx=ymax;
		int86(51,&regs,&regs);
	}
	MouseS = 0;
	MouseX=320,MouseY=240;
	save_bk_mou(320,240);
	mouse(MouseX,MouseY);
	flag=1;
}

void mouse(int x,int y)
{
	switch(MouseS)
	{
		/*case 1:                                  //手势鼠标
		{
				setcolor(WHITE);
				line(x-1,y+9,x-1,y+8,WHITE);
				line(x,y+7,x,y+11,WHITE);
				line(x+1,y+6,x+1,y+13,WHITE);
				line(x+2,y+8,x+2,y+14,WHITE);
				line(x+3,y-1,x+3,y+15,WHITE);
				arc(x+4,y-1,0,180,1,WHITE);
				line(x+4,y-2,x+4,y+15,WHITE);
				line(x+5,y-1,x+5,y+16,WHITE);
				arc(x+6,y+3,0,180,1,WHITE);
				line(x+6,y+2,x+6,y+16,WHITE);
				line(x+7,y+3,x+7,y+17,WHITE);
				arc(x+8,y+5,0,180,1,WHITE);
				line(x+8,y+4,x+8,y+17,WHITE);
				line(x+9,y+5,x+9,y+16,WHITE);
				arc(x+10,y+7,0,180,1,WHITE);
				line(x+10,y+6,x+10,y+16,WHITE);
				line(x+11,y+7,x+11,y+13,WHITE);

				setcolor(DARKGRAY);
				line(x-1,y+9,x-1,y+8);
				line(x-1,y+8,x+1,y+6);
				line(x+1,y+6,x+3,y+10);
				line(x+3,y+10,x+3,y-1);
				arc(x+4,y-1,0,180,1);
				line(x+5,y-1,x+5,y+5);
				arc(x+6,y+3,0,180,1);
				line(x+7,y+3,x+7,y+7);
				arc(x+8,y+5,0,180,1);
				line(x+9,y+5,x+9,y+9);
				arc(x+10,y+7,0,180,1);
				line(x+11,y+7,x+11,y+13);
				arc(x+7,y+13,-90,0,4);
				line(x+7,y+17,x+3,y+15);
				line(x+3,y+15,x+1,y+13);
				line(x+1,y+13,x-1,y+9);
		}
			break;*/
		case 2:                        //光标
		{
			line(x+1,y-1,x+9,y-1,DARK_GRAY);
			line(x+1,y+15,x+9,y+15,DARK_GRAY);
			line(x+5,y-1,x+5,y+15,DARK_GRAY);
		}
			break;
		case 3:                        //十字
		{
			line(x-1,y+7,x+11,y+7,WHITE);
			line(x+5,y-1,x+5,y+15,WHITE);
		}
			break;
		default:              //默认鼠标
		{
			line(x,y,x,y+13,WHITE);
			line(x+1,y+1,x+1,y+12,WHITE);
			line(x+2,y+2,x+2,y+11,WHITE);
			line(x+3,y+3,x+3,y+10,WHITE);
			line(x+4,y+4,x+4,y+12,WHITE);
			line(x+5,y+5,x+5,y+9,WHITE);
			line(x+5,y+11,x+5,y+14,WHITE);
			line(x+6,y+6,x+6,y+9,WHITE);
			line(x+6,y+13,x+6,y+15,WHITE);
			line(x+7,y+7,x+7,y+9,WHITE);
			line(x+8,y+8,x+8,y+9,WHITE);
			line(x+9,y+9,x+9,y+9,WHITE);
			line(x-1,y-1,x-1,y+14,DARK_GRAY);
			line(x-1,y+14,x+3,y+11,DARK_GRAY);
			line(x+3,y+11,x+3,y+12,DARK_GRAY);
			line(x+3,y+12,x+4,y+13,DARK_GRAY);
			line(x+4,y+13,x+4,y+14,DARK_GRAY);
			line(x+4,y+14,x+7,y+17,DARK_GRAY);
			line(x+7,y+17,x+7,y+13,DARK_GRAY);
			line(x+7,y+13,x+6,y+12,DARK_GRAY);
			line(x+6,y+12,x+6,y+11,DARK_GRAY);
			line(x+6,y+11,x+5,y+10,DARK_GRAY);
			line(x+5,y+10,x+11,y+10,DARK_GRAY);
			line(x+11,y+10,x-1,y-2,DARK_GRAY);
		}
		break;
	}
}

void mread(int *nx,int *ny,int *nbuttons)  
{
	regs.x.ax=3;
	int86(51,&regs,&regs);
	*nx = regs.x.cx;
	*ny = regs.x.dx;
	*nbuttons = regs.x.bx;
}

void newmouse(int *nx,int *ny,int *nbuttons)
{
	int xn, yn, buttonsn;
	int x0=*nx ,y0=*ny, buttons0=*nbuttons;
	mread(&xn,&yn,&buttonsn);
	*nx=xn, *ny=yn, *nbuttons=buttonsn;
	if(buttons0==*nbuttons) *nbuttons=0;
	if(xn==x0 &&yn==y0 &&buttonsn==buttons0) return;
	clrmous(x0,y0);
	save_bk_mou(*nx,*ny);
	drawmous(*nx,*ny);
}

void save_bk_mou(int nx,int ny) //存鼠标背景
{
	int i,j;
	for(i=-1;i<=11;i++)
	for(j=-2;j<=17;j++)
		mousesave[i][j]=Getpixel64k(nx+i,ny+j);
}

void clrmous(int nx,int ny) //清除鼠标
{
	int i,j;
	if(flag==1)
	{
		for(i=-1;i<=11;i++)
		for(j=-2;j<=17;j++)
			Putpixel64k(nx+i,ny+j,mousesave[i][j]);
		flag=0;
	}
}

void drawmous(int nx,int ny)
{
	if(flag==0)
	{
	    mouse(nx,ny);
		flag=1;
	}
}

//如果在框中点击，则返回1；在框中未点击，则返回2；不在框中则返回0
int mouse_press(int x1, int y1, int x2, int y2)
{
	/*****
	在框中点击，则返回1
	在框中未点击，则返回2
	在框中点击右键，则返回3
	*****/
	if(MouseX>x1 &&MouseX<x2 &&MouseY>y1 &&MouseY<y2) return press;
	else return 0;
}

int mouse_press_out(int x1, int y1, int x2, int y2)
{
	/*****
	在框中点击，则返回1
	在框中未点击，则返回2
	在框中点击右键，则返回3
	*****/
	if(MouseX<x1 ||MouseX>x2 ||MouseY<y1 ||MouseY>y2) return press;
	else return 0;
}
