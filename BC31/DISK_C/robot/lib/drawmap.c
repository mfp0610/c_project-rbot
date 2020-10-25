/*
    drawmap.c

	Initial version: 2020.7.21
    Lastest update: 2020.10.8
    Author: hhw
*/
#include "headers.h"

#define SIZE 40
#define WIDE 2
#define WALL_WIDE 4

void draw_floor_wood(int x,int y)
{
    bar(x+WIDE,y+WIDE,x+SIZE-WIDE,y+SIZE-WIDE,BROWN);
    bar(x,y,x+SIZE,y+WIDE,BLACK);
    bar(x,y+WIDE,x+WIDE,y+SIZE,BLACK);
    bar(x+SIZE-WIDE,y+WIDE,x+SIZE,y+SIZE,BLACK);
    bar(x+WIDE,y+SIZE-WIDE,x+SIZE-WIDE,y+SIZE,BLACK);
}

void draw_floor_ceramic(int x,int y)
{
    bar(x+WIDE,y+WIDE,x+SIZE-WIDE,y+SIZE-WIDE,LIGHT_BLUE);
    bar(x,y,x+SIZE,y+WIDE,BULE);
    bar(x,y+WIDE,x+WIDE,y+SIZE,BULE);
    bar(x+SIZE-WIDE,y+WIDE,x+SIZE,y+SIZE,BULE);
    bar(x+WIDE,y+SIZE-WIDE,x+SIZE-WIDE,y+SIZE,BULE);
}

void draw_wall_horizon(int x,int y,int n)
{
    bar(x,y,x+n*SIZE,y+WALL_WIDE,WALL_GREEN);
}

void draw_wall_vertical(int x,int y,int n)
{
    bar(x,y,x+WALL_WIDE,y+n*SIZE,WALL_GREEN);
}

void draw_table(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,WHEAT);
}

void draw_chair(int x,int y)
{
    fill_circle(x+20,y+20,19,WHEAT,BLACK);
}

void draw_door_left(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BROWN);
    fill_circle(x+30,y+20,2,BLACK,BLACK);
}

void draw_door_right(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BROWN);
    fill_circle(x+8,y+20,2,BLACK,BLACK);
}

void draw_door_vertical(int x,int y,int n)
{
    bar(x,y,x+WALL_WIDE,y+n*SIZE,BROWN);
}

void draw_else(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BLACK);
}