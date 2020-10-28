/*
    mainwin.c

    Initial version: 2020.9.12
    Lastest update: 2020.9.12 
    Author: mfp
*/
#include "headers.h"

#define timeupdate 100000 //更新界面时间
#define timeset 50000 //污染湿度按照要求更新
#define timedirt 500000 //污染，湿度程度更新时间
#define timetmpset 500000 //设定温度更新时间
#define timetmp 1000000 //温度更新时间
#define timeele 500000 //电量更新时间
#define timecut 10000000 //时间计数器请清零
#define setclean 20
#define setwet 20

FILE *fpde;

void mainWindow()
{
    HOUSE *house;
    ROBOT *robot;
    char value, value1;
    int i,j;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

    drawbasic();  //画出画面底板
    clrmous(MouseX, MouseY);
    
    house=(HOUSE *)malloc(sizeof(HOUSE));
    robot=(ROBOT *)malloc(sizeof(ROBOT));
    maininit(house,robot); //定义并初始化房间和机器人

    //fpde=fopen("debug\\debug.txt","w");
    
    paintmp(house,robot);
    draw_control();
    draw_bactr(robot);
    write_statu(house,robot,1);

    /*fprintf(fpde,"\ninit\n");
    fprintf(fpde,"time %lld\n",(*house).time); 
    fprintf(fpde,"pm %d\n",(*house).pm25);
    fprintf(fpde,"out %d\n",(*house).tempout);
    fprintf(fpde,"in %d\n",(*house).temp);
    fprintf(fpde,"dian %d\n",(*robot).electr);*/

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,1);
        if(mouse_press(LB+37,UB+350,LB+127,UB+390)==1) //进入电量界面
        {
            clrmous(MouseX, MouseY);
            draw_electr();
            nocombo();
            func_electr(house,robot);
            draw_control();
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+147,UB+350,LB+237,UB+390)==1) //进入舒适度界面
        {
            clrmous(MouseX, MouseY);
            draw_comfort();
            nocombo();
            func_comfort(house,robot);
            draw_control();
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+37,UB+410,LB+127,UB+450)==1) //进入环境界面
        {
            clrmous(MouseX, MouseY);
            draw_clean();
            nocombo();
            func_clean(house,robot);
            draw_control();
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+147,UB+410,LB+237,UB+450)==1) //进入控制界面
        {
            clrmous(MouseX, MouseY);
            draw_move();
            nocombo();
            func_move(house,robot);
            draw_control();
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //进入互动界面
        {
            clrmous(MouseX, MouseY);
            draw_react();
            nocombo();
            func_react(house,robot);
            draw_control();
            nocombo();
            draw_bactr(robot);
            write_statu(house,robot,1);
            fclose(fpde);
            continue;
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
    }
    return;
}

void drawbasic()
{
    setbkcol(MISTY_ROSE);
    bar(750,0,1024,768,MARINE_BLUE);
    bar(800,200,900,300,MISTY_ROSE);
}

void paintmp(HOUSE *house, ROBOT *robot)
{
    int i,j;
    int flag_bed=0;
    int tx=24,ty=15,sz=40;
    int cx1,cy1,cx2,cy2;
    
    for(i=0;i<N;i++)    
    for(j=0;j<N;j++)
    {
        cy1=tx+i*sz, cx1=ty+j*sz;
        cy2=cy1+sz, cx2=cx1+sz;
        
        switch((*house).mp1[i][j])
        {
            case 0:
                draw_floor_wood(cx1,cy1);
                break;
            case 2:
                bar(cx1,cy1,cx2,cy2,BLACK);
                break;
            case 3:
                bar(cx1,cy1,cx2,cy2,BROWN);
                break;
            case 4:
                draw_floor_wood(cx1,cy1);
                fill_circle((cx1+cx2)/2,(cy1+cy2)/2,20,PEACH_PUFF,BLACK);
                break;
            case 5:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                break;
            case 6:
                draw_floor_ceramic(cx1,cy1);
                break;
            case 7:
                bar(cx1,cy1,cx2,cy2,PINK);
                break;
            case 8:
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                bar(cx1+2,cy1,cx2,cy2,PINK);
                break;
            case 9:
                draw_floor_wood(cx1,cy1);
                draw_door_vertical(cx1,cy1,1);
                break;
            case 10:
                draw_door_left(cx1,cy1);
                break;
            case 11:
                draw_door_right(cx1,cy1);
                break;
            case 12:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1+8,cx2-8,cy2,WHEAT);
                break;
            case 13:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1,cx2-8,cy1+12,WHEAT);
                bar(cx1,cy1+28,cx2-8,cy2,WHEAT);
                break;
            case 14:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1,cx2-8,cy2-8,WHEAT);
                break;
            case 15:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1+19,cx2,cy2-19,BLACK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 16:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1+21,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy1+19,cx2,cy2-19,BLACK);
                bar(cx1+19,cy1,cx2-19,cy2,BLACK);
                break;
            case 17:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1+19,cy1,cx2-19,cy2,BLACK);
                bar(cx1+21,cy1,cx2,cy2,WHEAT);
                break;
            case 18:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy1+8,cx2-8,cy1+10,BLACK);
                bar(cx2-10,cy1+10,cx2-8,cy2,BLACK);
                bar(cx1,cy1+10,cx2-10,cy2,PINK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 19:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx2-10,cy1,cx2-8,cy2-8,BLACK);
                bar(cx1,cy2-10,cx2-10,cy2-8,BLACK);
                bar(cx1,cy1,cx2-10,cy2-10,PINK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 20:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 21:
                bar(cx1,cy1,cx2,cy2,YELLOW);     
                break;
            case 22:
                bar(cx1,cy1,cx2,cy2,GREEN);
                break;
            default: break;
        }
    }
    bar(0,0,15,768,MISTY_ROSE);
    bar(735,0,750,768,MISTY_ROSE);
    bar(0,0,750,24,MISTY_ROSE);
    bar(0,744,750,768,MISTY_ROSE);
    cy1=tx+(*robot).px*sz, cx1=ty+(*robot).py*sz;
    cy2=cy1+sz, cx2=cx1+sz;
    switch((*robot).rt)
    {
        case 'u': drawrobot_back((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        case 'd': drawrobot_front((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        case 'l': drawrobot_left((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        case 'r': drawrobot_right((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        default: break;
    }
}

void maininit(HOUSE *house, ROBOT *robot)
{
    int i,j;
    int mp1init[N][N]={
        {3,2,6,6,2,6,6,6,2,6,6,6,2,0,0,0,0,0},
        {0,9,0,0,2,6,6,6,2,6,6,6,2,5,5,0,0,0},
        {0,9,0,0,9,0,0,6,2,0,0,6,2,5,5,18,0,0},
        {0,2,0,0,9,0,0,6,2,0,0,6,2,5,5,19,0,0},
        {2,2,0,0,9,0,0,6,2,0,0,6,2,5,5,0,0,0},
        {0,0,0,0,2,6,6,6,2,0,0,6,2,0,0,0,0,0},
        {4,4,0,0,2,2,2,2,2,10,11,2,2,0,0,0,0,6},
        {5,5,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,6},
        {5,5,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,6},
        {4,4,0,0,0,0,0,2,10,11,2,2,2,2,2,2,2,2},
        {0,0,0,4,4,0,6,2,0,0,0,0,0,6,6,6,6,6},
        {6,0,0,0,0,20,17,2,0,0,0,0,0,0,0,0,0,0},
        {6,0,0,5,5,15,16,2,0,0,0,0,0,0,0,0,0,6},
        {6,0,0,5,5,20,17,2,6,0,0,0,0,7,7,7,8,12},
        {6,0,0,5,5,15,16,2,6,0,0,0,0,7,7,7,8,13},
        {6,0,0,0,0,20,17,2,6,0,0,0,0,7,7,7,8,14},
        {0,0,0,4,4,0,6,2,0,0,0,0,0,0,0,0,0,6},
        {21,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    };
    //0是地板，1是机器人，2是墙壁，3是垃圾桶，4是椅子，
    //5是桌子，6是一般高度家具，7 8 12 13 14是床，9是竖门，10是左门，11是右门
    //21是充电桩，22是垃圾

    (*robot).electr=100; //初始化机器人信息
    (*robot).px=10, (*robot).py=0;
    (*robot).rt='d';
    
    (*house).time=0;

    (*house).set=0;
    (*house).setd=0;
    (*house).setc=0;

    (*house).tempset=26;
    (*house).tempout=20;
    (*house).temp=26;
    (*house).wet=50;
    (*house).pm25=50; 
    
    for(i=0;i<5;i++)
    {
        (*house).dor[i]=1;
        (*house).win[i]=1;
    }   
    //初始化房间信息

    for(i=0;i<N;i++)
    for(j=0;j<N;j++)
    {
        (*house).mp1[i][j]=mp1init[i][j];
        (*house).mpinit[i][j]=mp1init[i][j];
    }
}

void func_electr(HOUSE *house, ROBOT *robot)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标
    
    draw_bactr(robot);
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,3);
        if(mouse_press(LB+57,UB+350,LB+217,UB+390)==1) //手动充电
        {
            nocombo();
            charge(house,robot);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回主菜单
        {
            nocombo();
            return;
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
    }
}

void func_comfort(HOUSE *house, ROBOT *robot)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

    draw_bactr(robot);
    write_statu(house,robot,2);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,2);
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
            return;
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
    }
}

void func_clean(HOUSE *house, ROBOT *robot)
{
    NODE rubbish[4];
    char value;
    int *pnum=0;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

    draw_bactr(robot);
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,1);
        if(mouse_press(LB+57,UB+350,LB+217,UB+390)==1) //生成垃圾
        {
            nocombo();
            nocombo();
            if(*pnum<3)
            {
                (*pnum)++;
                set_rub(pnum,rubbish,house);
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
                if(*pnum>0)
                {
                    col_rub(pnum,rubbish,house,robot);
                    paintmp(house,robot);
                    (*pnum)--;
                }
                else
                    break;
            }
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回主界面
        {
            nocombo();
            return;
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
    }
}

void func_react(HOUSE *house, ROBOT *robot)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

    draw_bactr(robot);
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,3);
        if(mouse_press(LB+57,UB+350,LB+217,UB+390)==1) //进入电量界面
        {
            
            continue;
        }
        if(mouse_press(LB+57,UB+410,LB+217,UB+450)==1) //进入舒适度界面
        {
            
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回控制面板
        {
            nocombo();
            return;
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
    }
}

void func_move(HOUSE *house, ROBOT *robot)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标
    
    draw_bactr(robot);
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,4);
        if(mouse_press(LB+57,UB+350,LB+217,UB+390)==1) //进入自由巡逻功能
        {
            free_hang(house,robot);
            nocombo();
            continue;
        }
        ope_door(house,robot);
        ope_wins(house,robot);
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
    }
}

void timepass(HOUSE *house, ROBOT *robot,int st)
{
    /*******上机调试*******/
    char *s;
    /*bar(0,0,150,60,MARINE_BLUE);
    itoa(house).time,s,10);
    outtextxy(0,0,s,1,2,10,WHITE);*/
    if((*house).time%timeupdate==0)
    {
        draw_bactr(robot); //画电池电量
        write_statu(house,robot,st); //画出状态栏
        /*fprintf(fpde,"\naaaa\n");
        fprintf(fpde,"time %lld\n",(*house).time); 
        
        fprintf(fpde,"flag %d\n",(*house).set);
        fprintf(fpde,"out %d\n",(*house).tempout);
        fprintf(fpde,"in %d\n",(*house).temp);
        fprintf(fpde,"set %d\n",(*house).tempset);*/
        
    }
    if((*house).time%timeset==0)
    {
        //pm25变化
        if((*house).pm25>=setclean&&(*house).setc)
            (*house).pm25--;
        else if((*house).time%timedirt==0)
        {
            (*house).setc=0;
            (*house).pm25++;
        }
        //湿度变化
        if((*house).wet>=setwet&&(*house).setd)
            (*house).wet--;
        else if((*house).time%timedirt==0)
        {
            (*house).setd=0;
            (*house).wet++;
        }
    }
    if((*house).time%timetmpset==0)
    {
        if((*house).set)
            (*house).temp-=sign((*house).temp-(*house).tempset);
        else if((*house).time%timetmp==0)
            (*house).temp-=sign((*house).temp-(*house).tempout);
    }
    if((*house).time%timeele==0) 
        (*robot).electr--;
    if((*robot).electr<=10) //触发自动充电模块
    {
        charge(house,robot);
    }
    (*house).time%=timecut;
    ((*house).time)++; 
}