/*
    interface.c

    Initial version: 2020.7.13
    Lastest update: 2020.9.12
    Author: hhw
*/
#include "headers.h"

void start_page()
{
    int i,f1=1;
    setbkcol(MISTY_ROSE);
    for(i=15;i<=80;i++)
    {
        drawrobot_right(i*10,500,5);
        Delaytime(100);
        clearrobot(i*10,500,5);
        if(i%10<5) puthz(220,90,"加载中，请耐心等待。。。",48,50,'K',BLACK);
        else puthz(220,90,"加载中，请耐心等待。。。",48,50,'K',STRONG_RED);
    }
    setbkcol(MISTY_ROSE);
    drawrobot_front(800,500,5);
    Delaytime(1000);
    clearrobot(800,500,5);
    drawrobot_front_hello(800,500,5);
    puthz(187,90,"欢迎使用家居机器人模拟系统",48,50,'H',BLACK);
    puthz(120,500,"本程序由华中科技大学自动化学院",24,28,'K',BLACK);
    puthz(120,550,"一九零五班孟繁鹏，黄瀚文共同开发",24,28,'K',BLACK);
    puthz(200,300,"按任意键继续",32,35,'K',BLACK);
    while(1)
    {
        Delaytime(500);
        if(f1) puthz(200,300,"按任意键继续",32,35,'K',BLACK), f1=0;
        else puthz(200,300,"按任意键继续",32,35,'K',STRONG_RED), f1=1;
        if(bioskey(1)) break;
    }
}

void login_page()
{
    setbkcol(MISTY_ROSE);
    drawrobot_front_hello(800,500,5);
    puthz(187,90,"欢迎使用居家机器人模拟系统",48,50,'H',BLACK);
    outtextxy(175,250,"LOGIN",3,3,50,MARINE_BLUE);
    
    fill_rect(100,350,500,400,WHITE,BLACK);
    fill_rect(100,450,500,500,WHITE,BLACK);
    fill_rect(100,350,180,400,MARINE_BLUE,BLACK);
    fill_rect(100,450,180,500,MARINE_BLUE,BLACK);
    puthz(108,359,"账号",32,35,'K',WHITE);
    puthz(108,459,"密码",32,35,'K',WHITE);

    fill_rect(200,550,400,600,MARINE_BLUE,BLACK);
    puthz(254,558,"登录",32,60,'K',WHITE); //画登录框图

    fill_rect(100,615,220,655,MARINE_BLUE,BLACK);
    fill_rect(380,615,500,655,MARINE_BLUE,BLACK);
    puthz(110,623,"新人注册",24,25,'K',WHITE);
    puthz(390,623,"找回密码",24,25,'K',WHITE);
    
    fill_rect(240,650,360,700,MARINE_BLUE,BLACK);
    puthz(250,663,"退出程序",24,25,'K',WHITE); //画找回和注册界面

}

void register_page()
{
    int begposi=300; 

    setbkcol(MISTY_ROSE);
    drawrobot_front_hello(800,500,5);
    puthz(187,90,"欢迎使用居家机器人模拟系统",48,50,'H',BLACK);
    puthz(200,200,"新人注册",48,50,'K',MARINE_BLUE);
    
    fill_rect(100,begposi,500,begposi+50,WHITE,BLACK);
    fill_rect(100,begposi+75,500,begposi+125,WHITE,BLACK);
    fill_rect(100,begposi+150,500,begposi+200,WHITE,BLACK);
    fill_rect(100,begposi+225,500,begposi+275,WHITE,BLACK);
    fill_rect(100,begposi,180,begposi+50,MARINE_BLUE,BLACK);
    fill_rect(100,begposi+75,180,begposi+125,MARINE_BLUE,BLACK);
    fill_rect(100,begposi+150,220,begposi+200,MARINE_BLUE,BLACK);
    fill_rect(100,begposi+225,220,begposi+275,MARINE_BLUE,BLACK);
    fill_rect(360,begposi+225,500,begposi+275,MARINE_BLUE,BLACK);
    puthz(108,begposi+9,"账号",32,35,'K',WHITE);
    puthz(108,begposi+84,"密码",32,35,'K',WHITE);
    puthz(108,begposi+159,"手机号",32,35,'K',WHITE); 
    puthz(108,begposi+234,"验证码",32,35,'K',WHITE); 
    puthz(370,begposi+234,"发送",32,35,'K',WHITE);//画注册框图

    fill_rect(120,begposi+325,240,begposi+375,MARINE_BLUE,BLACK);
    fill_rect(360,begposi+325,480,begposi+375,MARINE_BLUE,BLACK);
    puthz(130,begposi+338,"确认注册",24,25,'K',WHITE);
    puthz(370,begposi+338,"返回菜单",24,25,'K',WHITE); //画找回和注册界面
}

void findback_page()
{
    int begposi=300; 

    setbkcol(MISTY_ROSE);
    drawrobot_front_hello(800,500,5);
    puthz(187,90,"欢迎使用居家机器人模拟系统",48,50,'H',BLACK);
    puthz(200,200,"找回密码",48,50,'K',MARINE_BLUE);
    
    fill_rect(100,begposi,500,begposi+50,WHITE,BLACK);
    fill_rect(100,begposi+75,500,begposi+125,WHITE,BLACK);
    fill_rect(100,begposi+150,500,begposi+200,WHITE,BLACK);
    fill_rect(100,begposi,180,begposi+50,MARINE_BLUE,BLACK);
    fill_rect(100,begposi+75,220,begposi+125,MARINE_BLUE,BLACK);
    fill_rect(100,begposi+150,220,begposi+200,MARINE_BLUE,BLACK);
    fill_rect(360,begposi+150,500,begposi+200,MARINE_BLUE,BLACK);
    puthz(108,begposi+9,"账号",32,35,'K',WHITE);
    puthz(108,begposi+84,"手机号",32,35,'K',WHITE); 
    puthz(108,begposi+159,"验证码",32,35,'K',WHITE);
    puthz(370,begposi+159,"发送",32,35,'K',WHITE); //画找回密码框图

    puthz(108,begposi+235,"您的密码：",24,25,'K',MARINE_BLUE);

    fill_rect(120,begposi+300,240,begposi+350,MARINE_BLUE,BLACK);
    fill_rect(360,begposi+300,480,begposi+350,MARINE_BLUE,BLACK);
    puthz(130,begposi+313,"找回密码",24,25,'K',WHITE);
    puthz(370,begposi+313,"返回菜单",24,25,'K',WHITE); //画找回和注册界面
}

void exit_window()
{
    int begposi=200;

    fill_rect(200,begposi,600,begposi+300,WHITE,BLACK);
    fill_rect(300,begposi+250,330,begposi+280,MARINE_BLUE,BLACK);
    fill_rect(470,begposi+250,500,begposi+280,MARINE_BLUE,BLACK);
    puthz(267,begposi+100,"确定退出本程序吗",32,35,'K',BLACK);
    puthz(305,begposi+255,"是",24,25,'K',WHITE);
    puthz(475,begposi+255,"否",24,25,'K',WHITE); //画退出界面
}