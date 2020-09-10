/*
    drawbas.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.7.21
    Author: Mengfp
*/
#ifndef _DRAWBAS_H_
#define _DRAWBAS_H_

#include "headers.h"

void setbkcol(int color); //设置背景颜色
void line(int x1,int y1,int x2,int y2,int color); //绘制直线
void thick_line(int x1,int y1,int x2,int y2,int thick,int color); //绘制粗直线
void bar(int x1,int y1,int x2,int y2,int color); //绘制填充矩形
void rect(int x1,int y1,int x2,int y2,int color); //绘制空心矩形
void fill_rect(int x1,int y1,int x2,int y2,int color,int edgecolor); //绘制实心矩形（带边框）
void fill_circle(int xc,int yc,int r,int color); //绘制实心圆

#endif