/*
    comfort.c

	Initial version: 2020.7.21
    Lastest update: 2020.10.8
    Author: mfp
*/
#include "headers.h"

int func_comfort(HOUSE *house, ROBOT *robot, USER *usr)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

    draw_bactr(robot);
    write_statu(house,robot,2);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,usr,2);
        if(mouse_press(LB+110,UB+355,LB+140,UB+385)==1) //打开关闭空调开关
        {
            if((*house).set) (*house).set=0;
            else (*house).set=1;
            nocombo();
            write_statu(house,robot,2);
            continue;
        }
        if(mouse_press(LB+167,UB+360,LB+187,UB+380)==1) //降低设定温度
        {
            if((*house).tempset<=10) continue;
            com_settemp(house,robot,-1);
            nocombo();
            write_statu(house,robot,2);
            continue;
        }
        if(mouse_press(LB+227,UB+360,LB+247,UB+380)==1) //提高设定温度
        {
            if((*house).tempset>=40) continue;
            com_settemp(house,robot,1);
            nocombo();
            write_statu(house,robot,2);
            continue;
        }
        if(mouse_press(LB+37,UB+410,LB+127,UB+450)==1) //进入干燥
        {
            com_dry(house,robot);
            continue;
        }
        if(mouse_press(LB+147,UB+410,LB+237,UB+450)==1) //进行除尘
        {
            com_clean(house,robot);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回控制面板
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
                bar(1000,750,1024,768,BLACK);
            }
        }
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1)
            return 1;
    }
}

void com_dry(HOUSE *house, ROBOT *robot)
{
    (*house).setd=1;
    //write_statu(house,robot,1);
}

void com_clean(HOUSE *house, ROBOT *robot)
{
    (*house).setc=1;
    //write_statu(house,robot,1);
}

void com_settemp(HOUSE *house, ROBOT *robot,int change)
{
    if(change==1) (*house).tempset++;
    else (*house).tempset--;
    write_statu(house,robot,2);
}