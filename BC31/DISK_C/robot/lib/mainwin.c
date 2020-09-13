/*
    mainwin.c

    Initial version: 2020.9.12
    Lastest update: 2020.9.12 
    Author: mfp
*/
#include "headers.h"
#define N 18
FILE *fpde;

void mainWindow()
{
    int mp1[N][N], px, py;
    char value, value1;
    
    fpde=fopen("debug\\debug.txt","w");

    press=0;
    clrmous(MouseX, MouseY);
    
    drawbasic();
    
    memset(mp1,0,sizeof(mp1));
    
    /****调试****/
    mp1[0][0]=1;
    mp1[3][17]=1;
    mp1[6][14]=1;
    mp1[12][4]=1;
    
    mp1[9][0]=2;
    px=9, py=0;

    paintmp(mp1,px,py);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(800,200,900,300)==1) {fclose(fpde);}
        if(kbhit())
        {
            value=getch();
            if(value=='W'||value=='w') //向上运动
            {
                fprintf(fpde,"1 %d %d\n",px,py);
                move(&px,&py,'u',mp1);
                paintmp(mp1,px,py);
            }    
            else if(value=='S'||value=='s') //向下运动
            {
                fprintf(fpde,"1 %d %d\n",px,py);
                move(&px,&py,'d',mp1);
                paintmp(mp1,px,py);
            }
            else if(value=='A'||value=='a') //向左运动
            {
                fprintf(fpde,"1 %d %d\n",px,py);
                move(&px,&py,'l',mp1);
                paintmp(mp1,px,py);
            }
            else if(value=='D'||value=='d') //向右运动
            {
                fprintf(fpde,"1 %d %d\n",px,py);
                move(&px,&py,'r',mp1);
                paintmp(mp1,px,py);
            }
        }
    }
    fclose(fpde);
    return;
}

void drawbasic()
{
    setbkcol(MISTY_ROSE);

    bar(750,0,1024,768,MARINE_BLUE);

    bar(800,200,900,300,MISTY_ROSE);
}

void paintmp(int (*mp)[N],int px,int py)
{
    int i,j;
    int tx=24,ty=15,sz=40;
    int cx1,cy1,cx2,cy2;
    
    for(i=0;i<N;i++)    
    for(j=0;j<N;j++)
    {
        cy1=tx+i*sz, cx1=ty+j*sz;
        cy2=cy1+sz, cx2=cx1+sz;
        switch(mp[i][j])
        {
            case 0: case 2:
                bar(cx1,cy1,cx2,cy2,WHITE);
                break;
            case 1:
                bar(cx1,cy1,cx2,cy2,BLACK);
                break;
            default: break;
        }
    }
    cy1=tx+px*sz, cx1=ty+py*sz;
    cy2=cy1+sz, cx2=cx1+sz;
    drawrobot_front((cx1+cx2)/2,(cy1+cy2)/2,1);
}

void move(int *px,int *py,char dir,int (*mp)[N])
{
    int dx,dy,nx,ny;
    switch(dir) //判断移动方向
    {
        case 'u': dx=-1; dy=0; break;
        case 'd': dx=1; dy=0; break;
        case 'l': dx=0; dy=-1; break;
        case 'r': dx=0; dy=1; break;
        default: break;
    }
    nx=(*px)+dx, ny=(*py)+dy;
    //fprintf(fpde,"2 %d %d\n",nx,ny);
    if(nx>0 && nx<N && ny>0 && ny<N && mp[nx][ny]!=1)
    {
        mp[*px][*py]=0;
        *px=nx, *py=ny;
        mp[*px][*py]=2;
    }
}