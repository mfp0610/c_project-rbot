/*
    drawrobot.h
    
    Initial version: 2020.7.21
    Lastest update: 2020.7.21
    Author: Mengfp
*/
#ifndef _DRAWROBOT_H_
#define _DRAWROBOT_H_

#include "headers.h"

void drawrobot_front(int x,int y,int size); //画正面机器人
void drawrobot_front_hello(int x,int y,int size); //画问好机器人
void drawrobot_left(int x,int y,int size); //画左视机器人
void drawrobot_right(int x,int y,int size); //画右视机器人
void drawrobot_back(int x,int y,int size); //画背面机器人
void clearrobot(int x,int y,int size); //清空机器人

#endif