/*
    electr.c
    
    Initial version: 2020.10.28
    Lastest update: 2020.10.28
    Author: hhw
*/
#include "headers.h"

int func_electr(HOUSE *house, ROBOT *robot, USER *usr)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标
    
    draw_bactr(robot);
    write_statu(house,robot,5);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,usr,5);
        if(mouse_press(LB+57,UB+350,LB+217,UB+390)==1) //手动充电
        {
            nocombo();
            charge(house,robot,usr);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回主菜单
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

void charge(HOUSE *house, ROBOT *robot, USER *usr)
{
    NODE mp;
    NODE mp1;
    NODE charge_point;
    int i,t;
    
    //移动到对应位置
    mp.x=(*robot).px;
    mp.y=(*robot).py;
    charge_point.x=17;
    charge_point.y=0;
    Astarmove(mp,charge_point,robot,house);
    
    t=5000/(100-(*robot).electr);
    puthz(LB+87,UB+135,"充电中",32,32,'S',BLACK);
    for(i=0;i<5000;i++)
    {
        newmouse(&MouseX, &MouseY, &press);
        Delaytime(1);
        if(i%t==0)
        {
            (*robot).electr++;
            if((*robot).electr>100) (*robot).electr=100;
        }
        if(i%100==0) draw_bactr(robot);
        if(i%500==0)
        {
            bar(LB+77,UB+200,LB+197,UB+300,WHITE);
            if((i/500)%5>=4) fill_rect(LB+87,UB+204,LB+187,UB+224,BRIGHT_GREEN,WHITE);
            if((i/500)%5>=3) fill_rect(LB+87,UB+228,LB+187,UB+248,BRIGHT_GREEN,WHITE);
            if((i/500)%5>=2) fill_rect(LB+87,UB+252,LB+187,UB+272,BRIGHT_GREEN,WHITE);
            if((i/500)%5>=1) fill_rect(LB+87,UB+276,LB+187,UB+296,BRIGHT_GREEN,WHITE);
        }
        if(mouse_press(LB+57,UB+410,LB+217,UB+450)==1)
        {
            bar(LB+17,UB+130,LB+258,UB+170,MISTY_ROSE);
            (*robot).electr=100;
            write_statu(house,robot,5);
            return ;
        }
    }
    
    draw_bactr(robot);
    write_statu(house,robot,5);
    bar(LB+17,UB+130,LB+258,UB+170,MISTY_ROSE);
    (*robot).electr=100;
    mp1.x=(*robot).px;
    mp1.y=(*robot).py;
    Astarmove(mp1,mp,robot,house);
    return ;
}