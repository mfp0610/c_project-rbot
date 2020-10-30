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

void mainWindow(USER *usr)
{
    HOUSE *house;
    ROBOT *robot;
    NODE rubbish[4];
    char value, value1;
    int i,j;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

    drawbasic();  //画出画面底板
    clrmous(MouseX, MouseY);
    
    house=(HOUSE *)malloc(sizeof(HOUSE));
    robot=(ROBOT *)malloc(sizeof(ROBOT));
    maininit(house,robot); //定义并初始化房间和机器人
    
    paintmp(house,robot);
    draw_control(usr);
    draw_bactr(robot);
    write_statu(house,robot,1);
    house->rubnum=0;

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,usr,1);
        if(mouse_press(LB+37,UB+350,LB+127,UB+390)==1) //进入电量界面
        {
            clrmous(MouseX, MouseY);
            draw_electr(usr);
            nocombo();
            if(func_electr(house,robot,usr))
                return ;
            draw_control(usr);
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+147,UB+350,LB+237,UB+390)==1) //进入舒适度界面
        {
            clrmous(MouseX, MouseY);
            draw_comfort(usr);
            nocombo();
            if(func_comfort(house,robot,usr))
                return ;
            draw_control(usr);
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+37,UB+410,LB+127,UB+450)==1) //进入环境界面
        {
            clrmous(MouseX, MouseY);
            draw_clean(usr);
            nocombo();
            if(func_clean(rubbish,house,robot,usr))
                return ;
            draw_control(usr);
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+147,UB+410,LB+237,UB+450)==1) //进入控制界面
        {
            clrmous(MouseX, MouseY);
            draw_move(usr);
            nocombo();
            if(func_move(house,robot,usr))
                return ;
            draw_control(usr);
            draw_bactr(robot);
            write_statu(house,robot,1);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //进入互动界面
        {
            clrmous(MouseX, MouseY);
            draw_react(usr,0);
            nocombo();
            if(func_react(house,robot,usr))
                return ;
            draw_control(usr);
            nocombo();
            draw_bactr(robot);
            write_statu(house,robot,1);
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
                draw_cantgo();
            }
        }
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1)
            return ;
    }
    return;
}

void drawbasic()
{
    setbkcol(MISTY_ROSE);
    bar(750,0,1024,768,MARINE_BLUE);
    bar(800,200,900,300,MISTY_ROSE);
}

void maininit(HOUSE *house, ROBOT *robot)
{
    int i,j;
    int mp1init[N][N]={
        {3,2,0,0,2,41,41,6,2,36,35,6,2,0,0,0,0,0},
        {0,9,0,0,2,0,0,6,2,39,36,6,2,5,5,0,0,0},
        {0,9,0,0,9,0,0,40,2,36,36,6,2,38,5,18,0,0},
        {0,2,0,0,9,0,0,6,2,36,36,37,2,38,5,19,0,0},
        {2,2,0,0,2,0,0,40,2,36,36,6,2,5,5,0,0,0},
        {0,0,0,0,2,6,6,6,2,36,36,6,2,0,0,0,0,0},
        {4,4,0,0,2,2,2,2,2,10,11,2,2,0,0,0,0,29},
        {5,5,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,29},
        {5,5,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0,29},
        {30,30,0,0,0,0,0,2,10,11,2,2,2,2,2,2,2,2},
        {0,0,0,31,32,0,6,2,0,0,0,0,0,29,29,29,29,29},
        {28,0,0,0,0,20,17,2,0,0,0,0,0,0,0,0,0,0},
        {28,0,0,5,5,15,16,2,0,0,0,0,0,0,0,0,0,27},
        {28,0,0,5,5,20,17,2,28,0,0,0,0,7,7,7,8,12},
        {28,0,0,5,5,15,16,2,28,0,0,0,0,7,7,7,8,13},
        {28,0,0,0,0,20,17,2,28,0,0,0,0,7,7,7,8,14},
        {0,0,0,33,34,0,6,2,0,0,0,0,0,0,0,0,0,27},
        {21,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
    };
    //0是地板，1是机器人，2是墙壁，3是垃圾桶，4 30是椅子，
    //5是桌子，6是一般高度家具，7 8 12 13 14是床，9是竖门，10是左门，11是右门
    //21是充电桩，22是垃圾，23 24 25 26是开门状态，27是床头柜，28是电视，29是书柜
    //35是马桶，36是瓷砖，37是洗手池，39是排水口，40是煤气灶

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
        (*house).dor[i]=1;
    //初始化房间信息

    for(i=0;i<N;i++)
    for(j=0;j<N;j++)
    {
        (*house).mp1[i][j]=mp1init[i][j];
        (*house).mpinit[i][j]=mp1init[i][j];
    }
}

void timepass(HOUSE *house, ROBOT *robot, USER *usr, int st)
{
    char *s;
    unsigned int *back[240][90];
    FILE *fpsv;

    if((*house).time%timeupdate==0)
    {
        draw_bactr(robot); //画电池电量
        write_statu(house,robot,st); //画出状态栏
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
        fin(fpsv,"data\\mpsv.txt",LB+17,UB+60,LB+257,UB+510);
        
        draw_electr(usr);
        write_statu(house,robot,5);
        charge(house,robot,usr);

        fout(fpsv,"data\\mpsv.txt",LB+17,UB+60,LB+257,UB+510);
    }
    (*house).time%=timecut;
    ((*house).time)++; 
}

void fin(FILE *fp, char *rd, int x1,int y1,int x2,int y2)
{
    int i,j;
    fp=fopen(rd,"w");
    for(i=x1;i<=x2;i++)
    for(j=y1;j<=y2;j++)
        fprintf(fp,"%u\n",Getpixel64k(i,j));
    fclose(fp);
    return ;
}

void fout(FILE *fp, char *rd, int x1,int y1,int x2,int y2)
{
    int i,j;
    unsigned int px;
    fp=fopen(rd,"r");
    for(i=x1;i<=x2;i++)
    for(j=y1;j<=y2;j++)
    {
        fscanf(fp,"%u",&px);
        Putpixel64k(i,j,px);
    }
    fclose(fp);
    return ;
}