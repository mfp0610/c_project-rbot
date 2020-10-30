/*
    chat.h
    
    Adapted by pervious version
    Initial version: 2020.10.27
    Lastest update: 2020.10.27
    Author: mfp
*/
#ifndef _CHAT_H_
#define _CHAT_H_

#include "headers.h"

int func_react(HOUSE *house, ROBOT *robot, USER *usr); //互动界面函数
void c_reply1(int *qhwh,int *show_y);
int reply_match(char * str,char *order,char *reply); //寻找匹配答案
void show_incode(char *incode,int *y);
void show_reply(char *reply,int *y);

#endif