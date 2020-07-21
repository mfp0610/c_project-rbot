/*
    drawrobot.c

	Initial version: 2020.7.21
    Lastest update: 2020.7.21
    Author: Mengfp
*/
#include "headers.h"

void drawrobot_front(int x,int y,int size)
{
    int sb=20*size;
    fill_rect(x-sb,y-sb,x+sb,y+sb,MARINE_BLUE); //画机器人身子
    
    fill_rect(x+sb,y-sb,x+sb/2*3,y+sb/2,MARINE_BLUE);
    fill_rect(x-sb,y-sb,x-sb/2*3,y+sb/2,MARINE_BLUE); //画机器人胳膊
    
    fill_rect(x+sb,y+sb,x+sb/2,y+sb/2*3,MARINE_BLUE);
    fill_rect(x-sb,y+sb,x-sb/2,y+sb/2*3,MARINE_BLUE); //画机器人腿

    fill_rect(x-sb,y-sb,x+sb,y-2*sb,MARINE_BLUE);
    fill_circle(x+sb/2,y-sb/2*3,sb/5,WHITE);
    fill_circle(x-sb/2,y-sb/2*3,sb/5,WHITE);
    line(x+sb/2,y-3*sb,x+sb/2,y-2*sb,MARINE_BLUE);
    line(x-sb/2,y-3*sb,x-sb/2,y-2*sb,MARINE_BLUE);
    fill_circle(x+sb/2,y-3*sb-sb/5,sb/5,MARINE_BLUE);
    fill_circle(x-sb/2,y-3*sb-sb/5,sb/5,MARINE_BLUE);
    //画机器人头
}