/*
    drawmap.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.10.8
    Author: hhw
*/
#ifndef _DRAWMAP_H_
#define _DRAWMAP_H_

#include "headers.h"

void draw_floor_wood(int x,int y);
void draw_floor_ceramic(int x,int y);
void draw_table(int x,int y);
void draw_chair(int x,int y);
void draw_door_left(int x,int y);
void draw_door_right(int x,int y);
void draw_door_vertical(int x,int y,int n);
void draw_else(int x,int y);

#endif