/*
    move.h
    
    Initial version: 2020.10.24
    Lastest update: 2020.10.24
    Author: mfp
*/
#ifndef _MOVE_H_
#define _MOVE_H_

#include "headers.h"

void move(HOUSE *house, ROBOT *robot,char dir); //移动机器人
void moveupdate(HOUSE *house,ROBOT *robot,char value); //移动更新函数

#endif