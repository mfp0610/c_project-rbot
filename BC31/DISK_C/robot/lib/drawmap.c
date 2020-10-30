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

void paintmp(HOUSE *house, ROBOT *robot)
{
    int i,j;
    int flag_bed=0;
    int tx=24,ty=15,sz=40;
    int cx1,cy1,cx2,cy2;
    
    for(i=0;i<N;i++)    
    for(j=0;j<N;j++)
    {
        cy1=tx+i*sz, cx1=ty+j*sz;
        cy2=cy1+sz, cx2=cx1+sz;
        
        switch((*house).mp1[i][j])
        {
            case 0:
                draw_floor_wood(cx1,cy1);
                break;
            case 2:
                bar(cx1,cy1,cx2,cy2,BLACK);
                break;
            case 3:
                draw_bin(cx1,cy1);
                break;
            case 4:
                draw_floor_wood(cx1,cy1);
                fill_circle((cx1+cx2)/2,(cy1+cy2)/2,20,PEACH_PUFF,BLACK);
                bar(cx1,cy1,cx2,cy1+8,DARK_GRAY);
                break;
            case 5:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                break;
            case 6:
                bar(cx1,cy1,cx2,cy2,LIGHT_GRAY);
                break;
            case 7:
                bar(cx1,cy1,cx2,cy2,PINK);
                break;
            case 8:
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                bar(cx1+2,cy1,cx2,cy2,PINK);
                break;
            case 9:
                draw_floor_wood(cx1,cy1);
                draw_door_vertical(cx1,cy1,1);
                break;
            case 10:
                draw_door_left(cx1,cy1);
                break;
            case 11:
                draw_door_right(cx1,cy1);
                break;
            case 12:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1+8,cx2-8,cy2,WHEAT);
                break;
            case 13:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1,cx2-8,cy1+12,WHEAT);
                bar(cx1,cy1+28,cx2-8,cy2,WHEAT);
                break;
            case 14:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1,cx2-8,cy2-8,WHEAT);
                break;
            case 15:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1+19,cx2,cy2-19,BLACK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 16:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1+21,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy1+19,cx2,cy2-19,BLACK);
                bar(cx1+19,cy1,cx2-19,cy2,BLACK);
                break;
            case 17:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1+19,cy1,cx2-19,cy2,BLACK);
                bar(cx1+21,cy1,cx2,cy2,WHEAT);
                break;
            case 18:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy1+8,cx2-8,cy1+10,BLACK);
                bar(cx2-10,cy1+10,cx2-8,cy2,BLACK);
                bar(cx1,cy1+10,cx2-10,cy2,PINK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 19:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx2-10,cy1,cx2-8,cy2-8,BLACK);
                bar(cx1,cy2-10,cx2-10,cy2-8,BLACK);
                bar(cx1,cy1,cx2-10,cy2-10,PINK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 20:
                bar(cx1,cy1,cx2,cy2,PINK);
                bar(cx1,cy1,cx1+2,cy2,BLACK);
                break;
            case 21:
                draw_charge(cx1,cy1);    
                break;
            case 22:
                draw_floor_wood(cx1,cy1);
                draw_rub(cx1,cy1);
                break;
            case 23:
                draw_floor_wood(cx1,cy1);
                open_up_door(cx1,cy1);
                break;
            case 24:
                draw_floor_wood(cx1,cy1);
                open_down_door(cx1,cy1);
                break;
            case 25:
                draw_floor_wood(cx1,cy1);
                open_left_door(cx1,cy1);
                break;
            case 26:
                draw_floor_wood(cx1,cy1);
                open_right_door(cx1,cy1);
                break;
            case 27:
                draw_floor_wood(cx1,cy1);
                fill_circle(cx1+20,cy1+20,20,WHEAT,BLACK);
                break;
            case 28:
                draw_floor_wood(cx1,cy1);
                bar(cx1,cy1,cx1+10,cy2,DARK_GRAY);
                bar(cx1+10,cy1,cx1+20,cy2,BLACK);
                break;
            case 29:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                break;
            case 30:
                draw_floor_wood(cx1,cy1);
                fill_circle((cx1+cx2)/2,(cy1+cy2)/2,20,PEACH_PUFF,BLACK);
                bar(cx1,cy2-8,cx2,cy2,DARK_GRAY);
                break;
            case 31:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1+8,cy1+8,cx1+10,cy2,BLACK);
                bar(cx1+10,cy1+8,cx2,cy1+10,BLACK);
                bar(cx1+10,cy1+10,cx2,cy2,PINK);
                bar(cx1,cy2-1,cx2,cy2,BLACK);
                break;
            case 32:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy1+8,cx2-8,cy1+10,BLACK);
                bar(cx2-10,cy1+8,cx2-8,cy2,BLACK);
                bar(cx1,cy1+10,cx2-10,cy2,PINK);
                bar(cx1,cy2-1,cx2,cy2,BLACK);
                break;
            case 33:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1+8,cy1,cx1+10,cy2-8,BLACK);
                bar(cx1+8,cy2-10,cx2,cy2-8,BLACK);
                bar(cx1+10,cy1,cx2,cy2-10,PINK);
                bar(cx1,cy1,cx2,cy1+1,BLACK);
                break;
            case 34:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy2-10,cx2-8,cy2-8,BLACK);
                bar(cx2-10,cy1,cx2-8,cy2-10,BLACK);
                bar(cx1,cy1,cx2-10,cy2-10,PINK);
                bar(cx1,cy1,cx2,cy1+1,BLACK);
                break;
            case 35:
                draw_floor_ceramic(cx1,cy1);
                draw_toilet(cx1,cy1);
                break;
            case 36:
                draw_floor_ceramic(cx1,cy1);
                break;
            case 37:
                bar(cx1,cy1,cx2,cy2,LIGHT_GRAY);
                draw_wash(cx1,cy1);
                break;
            case 38:
                bar(cx1,cy1,cx2,cy2,WHEAT);
                bar(cx1,cy1,cx1+10,cy2,DARK_GRAY);
                bar(cx1+10,cy1,cx1+20,cy2,BLACK);
                break;
            case 39:
                draw_scupper(cx1,cy1);
                break;
            case 40:
                bar(cx1,cy1,cx2,cy2,LIGHT_GRAY);
                draw_cooker(cx1,cy1);
                break;
            case 41:
                bar(cx1,cy1,cx2,cy2,LIGHT_GRAY);
                fill_circle(cx1+20,cy1+20,18,WHITE,BLACK);
                fill_circle(cx1+20,cy1+15,10,LIGHT_GRAY,LIGHT_GRAY);
                fill_rect(cx1,cy1,cx2,cy1+7,WHITE,BLACK);
                fill_rect(cx1+16,cy1,cx2-16,cy1+20,DARK_GRAY,BLACK);
                break;
            default: break;
        }
    }
    bar(0,0,15,768,MISTY_ROSE);
    bar(735,0,750,768,MISTY_ROSE);
    bar(0,0,750,24,MISTY_ROSE);
    bar(0,744,750,768,MISTY_ROSE);
    cy1=tx+(*robot).px*sz, cx1=ty+(*robot).py*sz;
    cy2=cy1+sz, cx2=cx1+sz;
    switch((*robot).rt)
    {
        case 'u': drawrobot_back((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        case 'd': drawrobot_front((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        case 'l': drawrobot_left((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        case 'r': drawrobot_right((cx1+cx2)/2,(cy1+cy2)/2,1); break;
        default: break;
    }
}

void draw_floor_wood(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BROWN);
    bar(x,y+10,x+SIZE,y+20,DARK_RED);
    bar(x,y+30,x+SIZE,y+SIZE,DARK_RED);
}

void draw_floor_ceramic(int x,int y)
{
    fill_rect(x,y,x+SIZE,y+SIZE,LIGHT_BLUE,BULE);
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
    fill_rect(x,y,x+SIZE,y+SIZE,PINK,BLACK);
    fill_circle(x+30,y+20,4,BLACK,BLACK);
}

void draw_door_right(int x,int y)
{
    fill_rect(x,y,x+SIZE,y+SIZE,PINK,BLACK);
    fill_circle(x+8,y+20,4,BLACK,BLACK);
}

void draw_door_vertical(int x,int y,int n)
{
    fill_rect(x,y,x+2*WALL_WIDE,y+n*SIZE,PINK,BLACK);
}

void draw_else(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BLACK);
}

void draw_bin(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BLACK);
    bar(x+13,y,x+27,y+5,DARK_GRAY);
    bar(x,y+5,x+SIZE,y+15,DARK_GRAY);
    bar(x+5,y+15,x+35,y+SIZE,LIGHT_GRAY);
    bar(x+7,y+20,x+13,y+SIZE-5,DARK_GRAY);
    bar(x+17,y+20,x+23,y+SIZE-5,DARK_GRAY);
    bar(x+27,y+20,x+33,y+SIZE-5,DARK_GRAY);
    fill_circle(x+10,y+20,3,DARK_GRAY,DARK_GRAY);
    fill_circle(x+20,y+20,3,DARK_GRAY,DARK_GRAY);
    fill_circle(x+30,y+20,3,DARK_GRAY,DARK_GRAY);
}

void draw_charge(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,LIGHT_GRAY);
    bar(x+18,y+5,x+22,y+15,BLACK);
    bar(x+5,y+27,x+13,y+30,BLACK);
    bar(x+27,y+27,x+35,y+30,BLACK);
}

void open_left_door(int x,int y)
{
    fill_rect(x,y,x+2*WALL_WIDE,y+SIZE,PINK,BLACK);
}

void open_right_door(int x,int y)
{
    fill_rect(x+SIZE-2*WALL_WIDE,y,x+SIZE,y+SIZE,PINK,BLACK);
}

void open_up_door(int x,int y)
{ 
    fill_rect(x,y,x+SIZE,y+2*WALL_WIDE,PINK,BLACK);
}

void open_down_door(int x,int y)
{
    fill_rect(x,y+SIZE-2*WALL_WIDE,x+SIZE,y+SIZE,PINK,BLACK);
}

void draw_rub(int x,int y)
{
    fill_rect(x,y+10,x+SIZE,y+SIZE,MARINE_BLUE,BLACK);
    bar(x+17,y+7,x+22,y+9,BLACK);
    bar(x+16,y+6,x+23,y+6,MARINE_BLUE);
    bar(x+15,y+5,x+24,y+5,MARINE_BLUE);
    bar(x+14,y+4,x+25,y+4,MARINE_BLUE);
    bar(x+13,y+3,x+26,y+3,MARINE_BLUE);
    bar(x+12,y+2,x+27,y+2,MARINE_BLUE);
    bar(x+11,y+1,x+28,y+1,MARINE_BLUE);
    bar(x+10,y,x+29,y,MARINE_BLUE);
}

void draw_toilet(int x,int y)
{
    fill_circle(x+20,y+20,20,WHITE,BLACK);
    fill_circle(x+20,y+15,10,LIGHT_GRAY,LIGHT_GRAY);
    fill_rect(x,y,x+SIZE,y+10,WHITE,BLACK);
}

void draw_wash(int x,int y)
{
    fill_circle(x+20,y+20,20,WHITE,BLACK);
    fill_circle(x+25,y+20,10,LIGHT_GRAY,LIGHT_GRAY);
    fill_rect(x+SIZE-7,y,x+SIZE,y+SIZE,WHITE,BLACK);
    fill_rect(x+20,y+16,x+SIZE,y+24,DARK_GRAY,BLACK);
}

void draw_scupper(int x,int y)
{
    bar(x,y,x+SIZE,y+SIZE,BLACK);
    bar(x,y+8,x+SIZE,y+16,DARK_GRAY);
    bar(x,y+24,x+SIZE,y+32,DARK_GRAY);
    bar(x+8,y,x+16,y+SIZE,DARK_GRAY);
    bar(x+24,y,x+32,y+SIZE,DARK_GRAY);
}

void draw_cooker(int x,int y)
{
    fill_circle(x+20,y+20,20,BLACK,BLACK);
    fill_circle(x+20,y+20,17,DARK_GRAY,BLACK);
    fill_circle(x+20,y+20,10,BLACK,BLACK);
    fill_circle(x+20,y+20,7,STRONG_RED,BLACK);
    bar(x,y+17,x+10,y+23,BLACK);
    bar(x+SIZE-10,y+17,x+SIZE,y+23,BLACK);
    bar(x+17,y,x+23,y+10,BLACK);
    bar(x+17,y+SIZE-10,x+23,y+SIZE,BLACK);
}