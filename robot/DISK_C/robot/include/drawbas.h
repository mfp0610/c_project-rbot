/*
    drawbas.h
    
    Partly adapted by pervious version
    Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: Mengfp
*/
#ifndef _DRAWBAS_H_
#define _DRAWBAS_H_

#include "headers.h"

void linelevel(int x0,int y0,int x1,int y1,int thick,int color);
void linever(int x0,int y0,int x1,int y1,int thick,int color);
void Horizline(int x, int y, int width, int  color);
void bar(int x0, int y0, int x1, int y1, int color);
void Circle(int x0,int y0,int radius,int color);
void FillCircle(/*int x, int y, int r, int color*/int xc, int yc, int radius, int color);

void HER_Fillellipse(int x1,int y1,int x2,int y2,int r,int color);//填充椭圆（竖直方向）
void HOR_Fillellipse(int x1,int y1,int x2,int y2,int r,int color);//填充椭圆（水平方向）
void ellipse(int x1,int y1,int x2,int y2,int r,int color);
void semicircle_up(int x,int y,int r,int color);
void semicircle_down(int x,int y,int r,int color);
void Half_Circle(int xc, int yc, int radius, unsigned int color);
void fill_bow_right_up(int x,int y,int r,int color);
void fill_bow_left_up(int x,int y,int r,int color);
void fill_bow_left_down(int x,int y,int r,int color);
void fill_bow_right_down(int x,int y,int r,int color);
void fill_bow_down(int x,int y,int r, int color);
void fill_bow_up(int x,int y,int r, int color);
void fill_bow_left(int x,int y, int r, int color);
void fill_bow_right(int x,int y,int r,int color);
void bar_round(int x,int y,int length,int height,int r,int thick,int color);
void bar_round_2(int x0,int y0,int x1,int y1,int r,int thick,int color);
void bar_round_with_shadow(int x,int y,int length,int height,int r,int thick,int color);
void bow_right_down(int x,int y,int r,int color);
void bow_left_down(int x,int y,int r,int color);
void bow_right_up(int x,int y,int r,int color);
void bow_left_up(int x,int y,int r,int color);
void lean_line(int x,int y,int length,int theta,int color);
void lean_line_thick(int x,int y,int length,int theta,int thick,int color);

#endif