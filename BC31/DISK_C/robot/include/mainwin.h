/*
    mainwin.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.9.12
    Author: mfp
*/
#ifndef _MAINWIN_H_
#define _MAINWIN_H_
#define N 18

#include "headers.h"

typedef struct{
    int electr; //机器人电量
} ROBOT;

typedef struct{
    long long time; //程序运行时间
    int temp; //房间温度
    int wet; //房间湿度
    int pm25; //房间的pm2.5指数
} HOUSE;

void mainWindow(); //程序主界面
void drawbasic(); //程序主界面画图
void paintmp(int (*mp)[N],int px,int py,char pdir); //画出地图
void move(int *px,int *py,char dir,int (*mp)[N]); //移动机器人
void maininit(HOUSE *house, ROBOT *robot);
void func_electr(HOUSE *house, ROBOT *robot); //充电界面函数
void func_comfort(HOUSE *house, ROBOT *robot); //舒适度界面函数
void func_clean(HOUSE *house, ROBOT *robot); //情节界面函数
void func_move(HOUSE *house, ROBOT *robot); //控制界面函数
void timepass(HOUSE *house, ROBOT *robot); //时间流逝函数

#endif