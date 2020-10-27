/*
    rubbish.c
    
    Initial version: 2020.10.25
    Lastest update: 2020.10.25
    Author: hhw
*/

#include "headers.h"

void set_rub(int *pnum,NODE *rubbish,HOUSE *house)
{
    int x,y,num=0;
    while(1)
    {
        x=randin(17);
        y=randin(17);
        if((*house).mp1[x][y]==0)
        {
            rubbish[*pnum].x=x;
            rubbish[*pnum].y=y;
            draw_rub(pnum,rubbish);
            return;
        }
    }
}

void col_rub(int *pnum,NODE *rubbish,HOUSE *house,ROBOT *robot)
{
    NODE mp;
    mp.x=(*robot).px;
    mp.y=(*robot).py;
    Astarmove(mp,rubbish[*pnum],robot,house);
}

void draw_rub(int *pnum,NODE *rubbish)
{
    int x,y;
    x=15+(rubbish[*pnum].y)*40;
    y=24+(rubbish[*pnum].x)*40;
    bar(x,y,x+40,y+40,BLACK);
}