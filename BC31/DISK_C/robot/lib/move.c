/*
    move.c

	Initial version: 2020.10.24
    Lastest update: 2020.10.24
    Author: mfp
*/
#include "headers.h"

void move(HOUSE *house, ROBOT *robot,char dir) //移动机器人
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
    nx=(*robot).px+dx, ny=(*robot).py+dy;
    //fprintf(fpde,"1 %d %d\n",nx,ny);
    if(nx>=0 && nx<N && ny>=0 && ny<N && 
        pd_pass((*house).mp1[nx][ny]))
    {
        (*house).mp1[(*robot).px][(*robot).py]=
            (*house).mpinit[(*robot).px][(*robot).py];
        (*robot).px=nx, (*robot).py=ny;
        (*house).mp1[(*robot).px][(*robot).py]=1;
    }
    (*robot).rt=dir;
}

void moveupdate(HOUSE *house,ROBOT *robot,char value) //移动更新函数
{
    if(value=='W'||value=='w') //向上运动
    {
        move(house,robot,'u'); //移动机器人
        paintmp(house,robot); //重新绘制地图
        clrmous(MouseX, MouseY);
        return;
    }    
    else if(value=='S'||value=='s') //向下运动
    {
        move(house,robot,'d');
        paintmp(house,robot);
        clrmous(MouseX, MouseY);
        return;
    }
    else if(value=='A'||value=='a') //向左运动
    {
        move(house,robot,'l');
        paintmp(house,robot);
        clrmous(MouseX, MouseY);
        return;
    }
    else if(value=='D'||value=='d') //向右运动
    {
        move(house,robot,'r');
        paintmp(house,robot);
        clrmous(MouseX, MouseY);
        return;
    }
}

int getposition(int x,int y)
{
    int by=24,bx=15,len=40,sn=18;
    int retcode;
    retcode=((y-by)/len)*sn+(x-bx)/len;
    return retcode;
}

int pd_pass(int mp)
{
    if(mp==0) return 1;
    if(mp==3) return 1;
    if(mp==9) return 1;
    if(mp==10) return 1;
    if(mp==11) return 1;
    if(mp==22) return 1;
    return 0;
}