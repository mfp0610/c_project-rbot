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

extern int MouseX, MouseY, MouseS, press;
extern union REGS regs;
extern int mousesave[13][20];

void mouseinit();
void mouse(int x,int y);
void mread(int *nx,int *ny,int *nbuttons);
void newmouse(int *nx,int *ny,int *nbuttons);
void save_bk_mou(int nx,int ny);
void clrmous(int nx,int ny);
void drawmous(int nx,int ny);
int mouse_press(int x1, int y1, int x2, int y2);

#endif
