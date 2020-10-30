/*
    rubbish.c
    
    Initial version: 2020.10.25
    Lastest update: 2020.10.25
    Author: hhw
*/

#include "headers.h"

FILE *fpde4;

int func_clean(NODE *rubbish,HOUSE *house, ROBOT *robot, USER *usr)
{
    char value;
    int *f;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标
    *f=1;

    //fpde4=fopen("debug\\debug5.txt","w");
    draw_bactr(robot);
    write_statu(house,robot,6);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,usr,6);
        if(mouse_press(LB+57,UB+350,LB+217,UB+390)==1) //生成垃圾
        {
            nocombo();
            nocombo();
            if(house->rubnum<3)
            {
                (house->rubnum)++;
                set_rub(rubbish,house);
                paintmp(house,robot);
            }
            continue;
        }
        if(mouse_press(LB+57,UB+410,LB+217,UB+450)==1) //拾倒垃圾
        {
            nocombo();
            nocombo();
            while(1)
            {
                if(house->rubnum>0&&(*f)==1)
                {
                    //fprintf(fpde4,"%d %d\n",*f,house->rubnum);
                    puthz(LB+37,UB+230,"正在拾取垃圾中。",24,25,'K',BLACK);
                    col_rub(f,rubbish,house,robot);
                    paintmp(house,robot);
                    bar(LB+35,UB+230,LB+250,UB+260,MISTY_ROSE);
                    //fprintf(fpde4,"%d %d\n",*f,house->rubnum);
                }
                else
                    break;
            }
            //fclose(fpde4);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回主界面
        {
            nocombo();
            return 0;
        }
        if(kbhit())
        {
            Delaytime(50);
            value=getch();
            moveupdate(house,robot,value);   
        }
        get_conbot(house,robot);
        if(mouse_press(15,24,735,744)==1)
        {
            nocombo();
            poscode=getposition(MouseX, MouseY);
            mto.x=poscode/18;
            mto.y=poscode%18;
            mp.x=(*robot).px;
            mp.y=(*robot).py;
            if(!Astarmove(mp,mto,robot,house))
            {
                draw_cantgo();
            }
        }
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1)
            return 1;
    }
}

void set_rub(NODE *rubbish,HOUSE *house)
{
    int x,y;
    
    
    while(1)
    {
        x=randin(17);
        y=(randin(17)+23451)%17;
        if((*house).mp1[x][y]==0)
        {
            rubbish[house->rubnum].x=x;
            rubbish[house->rubnum].y=y;
            (*house).mp1[x][y]=22;
            (*house).mpinit[x][y]=22;
            
            /*draw_rub(pnum,rubbish);*/
            break;
        }
    }
    
}

void col_rub(int *f,NODE *rubbish,HOUSE *house,ROBOT *robot)
{
    int x,y;
    int i,j;
    NODE mp;
    NODE trash_bin;
    fpde4=fopen("debug\\debug4.txt","w");
    trash_bin.x=0;
    trash_bin.y=0;
    x=rubbish[house->rubnum].x;
    y=rubbish[house->rubnum].y;
    mp.x=(*robot).px;
    mp.y=(*robot).py;
    *f=Astarmove(mp,rubbish[house->rubnum],robot,house);
    fprintf(fpde4,"%d %d %d %d %d",mp.x,mp.y,x,y,*f);
    if(*f==1)
    {
        (*house).mp1[x][y]=0;
        (*house).mpinit[x][y]=0;
        mp.x=(*robot).px;
        mp.y=(*robot).py;
        if((house->rubnum)==1)
        {
            Astarmove(mp,trash_bin,robot,house);
        }
        (house->rubnum)--;
    }
    fclose(fpde4);
}