/*
    electr.c
    
    Initial version: 2020.10.28
    Lastest update: 2020.10.28
    Author: hhw
*/
#include "headers.h"

FILE *fpde3;

void charge(HOUSE *house, ROBOT *robot)
{
    NODE mp;
    NODE mp1;
    NODE charge_point;
    mp.x=(*robot).px;
    mp.y=(*robot).py;
    charge_point.x=17;
    charge_point.y=0;
    Astarmove(mp,charge_point,robot,house);
    bar(LB+17,UB+60,LB+258,UB+150,MARINE_BLUE);
    puthz(LB+27,UB+95,"≥‰µÁ÷–",32,32,'S',BLACK);
    Delaytime(5000);
    draw_electr();
    mp1.x=(*robot).px;
    mp1.y=(*robot).py;
    Astarmove(mp1,mp,robot,house);
    (*robot).electr=100;
}