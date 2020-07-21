/*
    mouse.h
    
    Adapted by pervious version
    Initial version: 2020.7.19
    Lastest update: 2020.7.19
    Author: Mengfp
*/
#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "headers.h"

void setMouseShape(int mark,int mx,int my);


void cursor(int x, int y);


void getMousebk(int x, int y);


void mousehide(int x, int y);

int init();
void mouseInit(int *mx,int *my, int *mbutt);


int readxy(int *mx, int *my, int *mbutt);


void newxy(int *mx, int *my, int *mbutt);

void backgroundChange(int mx, int my,int x1,int y1,int x2,int y2);

void AddFrame(int mx, int my, int x1, int y1, int x2, int y2,int thick,int color);

void reset_mouse(int *x,int *y);


#endif
