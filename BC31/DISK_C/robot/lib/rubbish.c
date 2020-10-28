/*
    rubbish.c
    
    Initial version: 2020.10.25
    Lastest update: 2020.10.25
    Author: hhw
*/

#include "headers.h"

FILE *fpde4;

void set_rub(NODE *rubbish,HOUSE *house)
{
    int x,y;
    
    
    while(1)
    {
        x=randin(17);
        y=(randin(17)+23451)%17;
        if((*house).mp1[x][y]==0)
        {
            rubbish[house->rubnum].x=x;
            rubbish[house->rubnum].y=y;
            (*house).mp1[x][y]=22;
            (*house).mpinit[x][y]=22;
            
            /*draw_rub(pnum,rubbish);*/
            break;
        }
    }
    
}

void col_rub(int *f,NODE *rubbish,HOUSE *house,ROBOT *robot)
{
    int x,y;
    int i,j;
    NODE mp;
    NODE trash_bin;
    fpde4=fopen("debug\\debug4.txt","w");
    trash_bin.x=0;
    trash_bin.y=0;
    x=rubbish[house->rubnum].x;
    y=rubbish[house->rubnum].y;
    mp.x=(*robot).px;
    mp.y=(*robot).py;
    *f=Astarmove(mp,rubbish[house->rubnum],robot,house);
    fprintf(fpde4,"%d %d %d %d %d",mp.x,mp.y,x,y,*f);
    if(*f==1)
    {
        (*house).mp1[x][y]=0;
        (*house).mpinit[x][y]=0;
        mp.x=(*robot).px;
        mp.y=(*robot).py;
        if((house->rubnum)==1)
        {
            Astarmove(mp,trash_bin,robot,house);
        }
        (house->rubnum)--;
    }
    fclose(fpde4);
}

/*void draw_rub(int *pnum,NODE *rubbish)
{
    int x,y;
    x=15+(rubbish[house->rubnum].y)*40;
    y=24+(rubbish[house->rubnum].x)*40;
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
}*/