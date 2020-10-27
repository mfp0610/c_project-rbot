/*
    board.h

    Initial version: 2020.9.27
    Lastest update: 2020.9.27
    Author: mfp
*/
#ifndef _BOARD_H_
#define _BOARD_H_

#include "headers.h"

void draw_control(); //画出控制主面板
void draw_eletr();
void draw_comfort(); //
void draw_move(); //画出移动面板
void draw_clean(); //画出清洁面板
void draw_react(); //画出互动面板
void draw_bactr(ROBOT *robot); //画电池函数
void write_statu(HOUSE *house, ROBOT *robot, int st); //写状态函数

#endif