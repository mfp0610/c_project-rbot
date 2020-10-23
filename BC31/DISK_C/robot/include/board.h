/*
    board.h
    
    Initial version: 2020.9.27
    Lastest update: 2020.9.27
    Author: mfp
*/
#ifndef _BOARD_H_
#define _BOARD_H_

#include "headers.h"

void draw_control(HOUSE *house, ROBOT *robot); //画出控制主面板
void draw_eletr(HOUSE *house, ROBOT *robot);
void draw_comfort(HOUSE *house, ROBOT *robot); //
void draw_move(HOUSE *house, ROBOT *robot);
void draw_clean(HOUSE *house, ROBOT *robot);
void draw_bactr(ROBOT *robot); //画电池函数

#endif