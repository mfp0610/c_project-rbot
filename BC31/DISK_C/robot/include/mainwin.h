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

void mainWindow(); //程序主界面
void drawbasic(); //程序主界面画图
void paintmp(int (*mp)[N],int px,int py); //画出地图
void move(int *px,int *py,char dir,int (*mp)[N]); //移动机器人

#endif