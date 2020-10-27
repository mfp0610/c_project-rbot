/*
    rubbish.c
    
    Initial version: 2020.10.25
    Lastest update: 2020.10.25
    Author: hhw
*/

#include "headers.h"

FILE *fpde2;

void set_rub(int *pnum,NODE *rubbish,HOUSE *house)
{
    int x,y;
    fpde2=fopen("debug\\debug2.txt","w");
    while(1)
    {
        x=randin(17);
        y=randin(17);
        fprintf(fpde2,"%d\t%d\t%d\n",x,y,*pnum);

        if((*house).mp1[x][y]==0)
        {
            rubbish[*pnum].x=x;
            rubbish[*pnum].y=y;
            (*house).mp1[x][y]=22;
            (*house).mpinit[x][y]=22;
            /*draw_rub(pnum,rubbish);*/
            break;
        }
    }
    fclose(fpde2);
}

void col_rub(int *pnum,NODE *rubbish,HOUSE *house,ROBOT *robot)
{
    int x,y;
    NODE mp;
    x=rubbish[*pnum].x;
    y=rubbish[*pnum].y;
    fpde2=fopen("debug\\debug2.txt","w");
    mp.x=(*robot).px;
    mp.y=(*robot).py;
    Astarmove(mp,rubbish[*pnum],robot,house);
    (*house).mp1[x][y]=0;
    (*house).mpinit[x][y]=0;
    fclose(fpde2);
}

void draw_rub(int *pnum,NODE *rubbish)
{
    int x,y;
    x=15+(rubbish[*pnum].y)*40;
    y=24+(rubbish[*pnum].x)*40;
    bar(x,y,x+5,y+5,BLACK);
    bar(x+10,y,x+15,y+5,BLACK);
    bar(x+20,y,x+25,y+5,BLACK);
    bar(x+30,y,x+35,y+5,BLACK);
    bar(x+5,y+5,x+10,y+10,BLACK);
    bar(x+15,y+5,x+20,y+10,BLACK);
    bar(x+25,y+5,x+30,y+10,BLACK);
    bar(x+35,y+5,x+40,y+10,BLACK);
    bar(x,y+10,x+5,y+15,BLACK);
    bar(x+10,y+10,x+15,y+15,BLACK);
    bar(x+20,y+10,x+25,y+15,BLACK);
    bar(x+35,y+10,x+40,y+15,BLACK);
    bar(x+5,y+15,x+5,y+20,BLACK);
    bar(x+15,y+15,x+20,y+20,BLACK);
    bar(x+25,y+15,x+30,y+20,BLACK);
    bar(x+35,y+15,x+40,y+20,BLACK);
    bar(x,y+20,x+5,y+25,BLACK);
    bar(x+10,y+20,x+15,y+25,BLACK);
    bar(x+20,y+20,x+25,y+25,BLACK);
    bar(x+30,y+20,x+35,y+25,BLACK);
    bar(x+5,y+25,x+5,y+30,BLACK);
    bar(x+15,y+25,x+20,y+30,BLACK);
    bar(x+25,y+25,x+30,y+30,BLACK);
    bar(x+35,y+25,x+40,y+30,BLACK);
    bar(x,y+30,x+5,y+35,BLACK);
    bar(x+10,y+30,x+15,y+35,BLACK);
    bar(x+20,y+30,x+25,y+35,BLACK);
    bar(x+30,y+30,x+35,y+35,BLACK);
    bar(x+5,y+35,x+5,y+40,BLACK);
    bar(x+15,y+35,x+20,y+40,BLACK);
    bar(x+25,y+35,x+30,y+40,BLACK);
    bar(x+35,y+35,x+40,y+40,BLACK);
}