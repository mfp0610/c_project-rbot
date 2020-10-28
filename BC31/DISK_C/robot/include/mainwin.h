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
    int px, py; //机器人位置
    char rt; //机器人朝向
} ROBOT;

typedef struct{
    long int time; //程序运行时间
    int set,setd,setc; //人工设定标签
    int tempset; //温度设定温度
    int tempout; //室外温度
    int temp; //房间温度
    int wet; //房间湿度
    int pm25; //房间的pm2.5指数
    int mp1[N][N]; //储存地图
    int mpinit[N][N]; //储存初始地图 
    int dor[5];
    int win[5];
} HOUSE;

void mainWindow(); //程序主界面
void drawbasic(); //程序主界面画图
void paintmp(HOUSE *house, ROBOT *robot); //画出地图
void maininit(HOUSE *house, ROBOT *robot);
void func_electr(HOUSE *house, ROBOT *robot); //充电界面函数
void func_comfort(HOUSE *house, ROBOT *robot); //舒适度界面函数
void func_clean(HOUSE *house, ROBOT *robot); //情节界面函数
void func_move(HOUSE *house, ROBOT *robot); //控制界面函数
void func_react(HOUSE *house, ROBOT *robot); //互动界面函数
void timepass(HOUSE *house, ROBOT *robot,int st); //时间流逝函数

#endif