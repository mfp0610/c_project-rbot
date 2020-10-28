/*
    board.c

	Initial version: 2020.9.27
    Lastest update: 2020.9.27
    Author: mfp
*/

#include "headers.h"

void draw_control()
{

    bar(LB,UB,1024,768,MARINE_BLUE);

    //画返回主菜单
    fill_rect(LB+140,UB+10,LB+250,UB+40,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+145,UB+12,"返回菜单",24,25,'K',BLACK);

    //画状态显示栏
    fill_rect(LB+17,UB+60,LB+257,UB+320,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+27,UB+95,"欢迎用户",32,32,'S',BLACK);
    outtextxy(LB+145,UB+95,"111",2,2,16,BLACK);
    puthz(LB+37,UB+160,"室内温度：",24,25,'K',BLACK);
    puthz(LB+37,UB+195,"室外温度：",24,25,'K',BLACK);
    puthz(LB+37,UB+230,"空气湿度：",24,25,'K',BLACK);
    puthz(LB+37,UB+265,"污染指数：",24,25,'K',BLACK);

    //画功能按钮
    fill_rect(LB+37,UB+350,LB+127,UB+390,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+47,UB+354,"电量",32,35,'K',BLACK);
    fill_rect(LB+147,UB+350,LB+237,UB+390,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+157,UB+354,"舒适",32,35,'K',BLACK);
    fill_rect(LB+37,UB+410,LB+127,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+47,UB+414,"环境",32,35,'K',BLACK);
    fill_rect(LB+147,UB+410,LB+237,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+157,UB+414,"控制",32,35,'K',BLACK);
    fill_rect(LB+57,UB+470,LB+217,UB+510,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+474,"人机互动",32,32,'K',BLACK);

    //画遥控按钮
    draw_conbot();
}

void draw_electr()
{
    bar(LB,UB,1024,768,MARINE_BLUE);  

    //画返回主菜单
    fill_rect(LB+140,UB+10,LB+250,UB+40,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+145,UB+12,"返回菜单",24,25,'K',BLACK);

    //画状态显示栏
    fill_rect(LB+17,UB+60,LB+257,UB+320,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+27,UB+95,"欢迎用户",32,32,'H',BLACK);
    
    outtextxy(LB+145,UB+95,"111",2,2,16,BLACK);

    //画功能按钮
    fill_rect(LB+57,UB+350,LB+217,UB+390,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+354,"自动充电",32,32,'K',BLACK);
    fill_rect(LB+57,UB+410,LB+217,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+414,"手动充电",32,32,'K',BLACK);
    fill_rect(LB+57,UB+470,LB+217,UB+510,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+474,"返回主页",32,32,'K',BLACK);

    //画遥控按钮
    draw_conbot();
}

void draw_comfort()
{
    bar(LB,UB,1024,768,MARINE_BLUE);

    //画返回主菜单
    fill_rect(LB+140,UB+10,LB+250,UB+40,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+145,UB+12,"返回菜单",24,25,'K',BLACK);

    //画状态显示栏
    fill_rect(LB+17,UB+60,LB+257,UB+320,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+27,UB+95,"欢迎用户",32,32,'H',BLACK);
    
    outtextxy(LB+145,UB+95,"111",2,2,16,BLACK);
    puthz(LB+37,UB+160,"室内温度：",24,25,'K',BLACK);
    puthz(LB+37,UB+195,"室外温度：",24,25,'K',BLACK);
    puthz(LB+37,UB+230,"空气湿度：",24,25,'K',BLACK);
    puthz(LB+37,UB+265,"污染指数：",24,25,'K',BLACK);

    //画功能按钮
    puthz(LB+27,UB+354,"温度",32,32,'K',WHITE);

    fill_rect(LB+110,UB+355,LB+140,UB+385,MISTY_ROSE,MARINE_BLUE);

    fill_rect(LB+167,UB+360,LB+187,UB+380,MISTY_ROSE,MARINE_BLUE);
    fill_rect(LB+227,UB+360,LB+247,UB+380,MISTY_ROSE,MARINE_BLUE);
    outtextxy(LB+159,UB+353,"-",2,2,16,BLACK);
    outtextxy(LB+219,UB+353,"+",2,2,16,BLACK);
    
    fill_rect(LB+37,UB+410,LB+127,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+47,UB+414,"除湿",32,35,'K',BLACK);
    fill_rect(LB+147,UB+410,LB+237,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+157,UB+414,"除尘",32,35,'K',BLACK);
    fill_rect(LB+57,UB+470,LB+217,UB+510,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+474,"返回主页",32,32,'K',BLACK);

    //画遥控按钮
    draw_conbot();
}

void draw_move()
{
    bar(LB,UB,1024,768,MARINE_BLUE);

    //画返回主菜单
    fill_rect(LB+140,UB+10,LB+250,UB+40,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+145,UB+12,"返回菜单",24,25,'K',BLACK);

    //画状态显示栏
    fill_rect(LB+17,UB+60,LB+257,UB+320,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+27,UB+95,"欢迎用户",32,32,'H',BLACK);
    outtextxy(LB+145,UB+95,"111",2,2,16,BLACK);
    
    //画功能按钮
    fill_rect(LB+57,UB+350,LB+217,UB+390,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+354,"定向巡逻",32,32,'K',BLACK);
    fill_rect(LB+57,UB+410,LB+217,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+414,"自动巡逻",32,32,'K',BLACK);
    fill_rect(LB+57,UB+470,LB+217,UB+510,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+474,"返回主页",32,32,'K',BLACK);

    //画遥控按钮
    draw_conbot();
}

void draw_clean()
{
    bar(LB,UB,1024,768,MARINE_BLUE);

    //画返回主菜单
    fill_rect(LB+140,UB+10,LB+250,UB+40,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+145,UB+12,"返回菜单",24,25,'K',BLACK);

    //画状态显示栏
    fill_rect(LB+17,UB+60,LB+257,UB+320,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+27,UB+95,"欢迎用户",32,32,'H',BLACK);
    
    outtextxy(LB+145,UB+95,"111",2,2,16,BLACK);
    puthz(LB+37,UB+160,"地面垃圾：",24,25,'K',BLACK);
    puthz(LB+37,UB+195,"桶内垃圾：",24,25,'K',BLACK);

    //画功能按钮
    fill_rect(LB+57,UB+350,LB+217,UB+390,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+354,"生成垃圾",32,32,'K',BLACK);
    fill_rect(LB+57,UB+410,LB+217,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+414,"拾取垃圾",32,32,'K',BLACK);
    fill_rect(LB+57,UB+470,LB+217,UB+510,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+474,"返回主页",32,32,'K',BLACK);

    //画遥控按钮
    draw_conbot();
}

void draw_react()
{
    bar(LB,UB,1024,768,MARINE_BLUE);  

    //画返回主菜单
    fill_rect(LB+140,UB+10,LB+250,UB+40,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+145,UB+12,"返回菜单",24,25,'K',BLACK);
    
    //画状态显示栏
    fill_rect(LB+17,UB+60,LB+257,UB+380,MISTY_ROSE,MISTY_ROSE);
    puthz(LB+27,UB+95,"欢迎用户",32,32,'H',BLACK);
    
    outtextxy(LB+145,UB+95,"111",2,2,16,BLACK);
    //puthz(LB+37,UB+160,"室外温度：",24,25,'K',BLACK);
    //puthz(LB+37,UB+195,"室内温度：",24,25,'K',BLACK);
    //puthz(LB+37,UB+230,"空气湿度：",24,25,'K',BLACK);
    //puthz(LB+37,UB+265,"空气质量：",24,25,'K',BLACK);

    //画功能按钮
    fill_rect(LB+37,UB+410,LB+127,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+47,UB+414,"聊天",32,35,'K',BLACK);
    fill_rect(LB+147,UB+410,LB+237,UB+450,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+157,UB+414,"字谜",32,35,'K',BLACK);
    fill_rect(LB+57,UB+470,LB+217,UB+510,MISTY_ROSE,MARINE_BLUE);
    puthz(LB+71,UB+474,"返回主页",32,32,'K',BLACK);

    //画遥控按钮
    draw_conbot();
}

void draw_conbot()
{
    //midx-137 midy-700
    int cx,cy;

    fill_circle(LB+92,UB+630,30,MISTY_ROSE,MARINE_BLUE);
    fill_circle(LB+182,UB+630,30,MISTY_ROSE,MARINE_BLUE);
    fill_circle(LB+137,UB+585,30,MISTY_ROSE,MARINE_BLUE);
    fill_circle(LB+137,UB+675,30,MISTY_ROSE,MARINE_BLUE);

    cx=LB+137, cy=UB+585;
    thick_line(cx-20,cy-5,cx,cy-20,4,MARINE_BLUE);
    thick_line(cx,cy-20,cx+20,cy-5,4,MARINE_BLUE);
    thick_line(cx-5,cy-5,cx-20,cy-5,4,MARINE_BLUE);
    thick_line(cx+5,cy-5,cx+20,cy-5,4,MARINE_BLUE);
    thick_line(cx-5,cy-5,cx-5,cy+20,4,MARINE_BLUE);
    thick_line(cx+5,cy-5,cx+5,cy+20,4,MARINE_BLUE);
    thick_line(cx-5,cy+20,cx+5,cy+20,4,MARINE_BLUE);

    cx=LB+137, cy=UB+675;
    thick_line(cx-20,cy+5,cx,cy+20,4,MARINE_BLUE);
    thick_line(cx,cy+20,cx+20,cy+5,4,MARINE_BLUE);
    thick_line(cx-5,cy+5,cx-20,cy+5,4,MARINE_BLUE);
    thick_line(cx+5,cy+5,cx+20,cy+5,4,MARINE_BLUE);
    thick_line(cx-5,cy+5,cx-5,cy-20,4,MARINE_BLUE);
    thick_line(cx+5,cy+5,cx+5,cy-20,4,MARINE_BLUE);
    thick_line(cx-5,cy-20,cx+5,cy-20,4,MARINE_BLUE);

    cx=LB+92, cy=UB+630;
    thick_line(cx-20,cy,cx-5,cy+20,4,MARINE_BLUE);
    thick_line(cx-20,cy,cx-5,cy-20,4,MARINE_BLUE);
    thick_line(cx-5,cy+5,cx-5,cy+20,4,MARINE_BLUE);
    thick_line(cx-5,cy-5,cx-5,cy-20,4,MARINE_BLUE);
    thick_line(cx-5,cy-5,cx+20,cy-5,4,MARINE_BLUE);
    thick_line(cx-5,cy+5,cx+20,cy+5,4,MARINE_BLUE);
    thick_line(cx+20,cy-5,cx+20,cy+5,4,MARINE_BLUE);

    cx=LB+182, cy=UB+630;
    thick_line(cx+5,cy+20,cx+20,cy,4,MARINE_BLUE);
    thick_line(cx+5,cy-20,cx+20,cy,4,MARINE_BLUE);
    thick_line(cx+5,cy+5,cx+5,cy+20,4,MARINE_BLUE);
    thick_line(cx+5,cy-5,cx+5,cy-20,4,MARINE_BLUE);
    thick_line(cx+5,cy-5,cx-20,cy-5,4,MARINE_BLUE);
    thick_line(cx+5,cy+5,cx-20,cy+5,4,MARINE_BLUE);
    thick_line(cx-20,cy-5,cx-20,cy+5,4,MARINE_BLUE);

}

void draw_bactr(ROBOT *robot)
{
    char s[5];
    int len;
    bar(LB,UB,LB+130,UB+60,MARINE_BLUE);
    fill_rect(LB+21,UB+10,LB+70,UB+40,MISTY_ROSE,MARINE_BLUE);
    fill_rect(LB+70,UB+15,LB+75,UB+35,MISTY_ROSE,MISTY_ROSE);
    itoa((*robot).electr,s,10);
    len=strlen(s);
    s[len]='%';
    s[len+1]='\0';
    outtextxy(LB+80,UB+10,s,1,2,10,WHITE);
    if((*robot).electr<25) fill_rect(LB+23,UB+12,LB+32,UB+38,STRONG_RED,BRIGHT_GREEN);
    else fill_rect(LB+23,UB+12,LB+32,UB+38,BRIGHT_GREEN,BRIGHT_GREEN);
    if((*robot).electr>=25) fill_rect(LB+35,UB+12,LB+44,UB+38,BRIGHT_GREEN,BRIGHT_GREEN);
    if((*robot).electr>=50) fill_rect(LB+47,UB+12,LB+56,UB+38,BRIGHT_GREEN,BRIGHT_GREEN);
    if((*robot).electr>=75) fill_rect(LB+59,UB+12,LB+68,UB+38,BRIGHT_GREEN,BRIGHT_GREEN);
}

void write_statu(HOUSE *house, ROBOT *robot,int st)
{
    int LBx=LB+110, LBy=UB+355;
    int color;
    if(st==1||st==2)
    {
        char s1[5],s2[5],s3[5],s4[8];
        itoa((*house).temp,s1,10);
        itoa((*house).tempout,s2,10);
        itoa((*house).wet,s3,10);
        itoa((*house).pm25,s4,10);
        
        bar(LB+150,UB+150,LB+210,UB+300,MISTY_ROSE);
        outtextxy(LB+150,UB+155,s1,2,2,16,BLACK);
        outtextxy(LB+150,UB+190,s2,2,2,16,BLACK);
        outtextxy(LB+150,UB+225,s3,2,2,16,BLACK);
        outtextxy(LB+150,UB+260,s4,2,2,16,BLACK);
        outtextxy(LB+190,UB+155,"C",2,2,16,BLACK);
        outtextxy(LB+190,UB+190,"C",2,2,16,BLACK);
        outtextxy(LB+190,UB+225,"%",2,2,16,BLACK);
        outtextxy(LB+190,UB+260,"%",2,2,16,BLACK);
        drcircle(LB+197,UB+155,3,BLACK);
        drcircle(LB+197,UB+190,3,BLACK);
        if(st==2)
        {
            char s5[3];
            itoa((*house).tempset,s5,10);
            bar(LB+190,UB+360,LB+230,UB+390,MARINE_BLUE);
            
            if((*house).set==1) color=STRONG_RED;
            else color=BLACK;
            //LB+110,UB+355,LB+140,UB+385,
            bar(LBx+14,LBy+2,LBx+16,LBy+15,color);
            bar(LBx+5,LBy+5,LBx+12,LBy+7,color);
            bar(LBx+18,LBy+5,LBx+25,LBy+7,color);
            bar(LBx+5,LBy+5,LBx+7,LBy+25,color);
            bar(LBx+23,LBy+5,LBx+25,LBy+25,color);
            bar(LBx+5,LBy+23,LBx+25,LBy+25,color);
            
            outtextxy(LB+182,UB+354,s5,2,2,16,WHITE);
        }
        return ;
    }
}