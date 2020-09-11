/*
    headers.h
    
    Initial version: 2020.7.12
    Lastest update: 2020.8.8
    Author: Mengfp
*/
#ifndef _HEADERS_H_
#define _HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <bios.h>
#include <time.h>

#include "svga.h" //svga头文件
#include "hzk.h" //汉字库头文件
#include "mouse.h" //鼠标函数库头文件
#include "drawbas.h" //基础画图头文件
#include "mysys.h" //自己写的系统函数
#include "drawrobot.h" //画机器人头文件
#include "interface.h" //登陆界面绘图头文件
#include "login.h" //登陆界面头文件
#include "register.h" //注册界面头文件


//定义颜色宏
#define BLACK 0
#define MARINE_BLUE 559
#define DARK_GRAY 44373
#define STRONG_RED 57344
#define DARK_ORANGE 64608
#define MISTY_ROSE 65340
#define WHITE 65535

//必要的参数
#define ROBOT_SIZE 20 //定义基础机器人大小

#endif