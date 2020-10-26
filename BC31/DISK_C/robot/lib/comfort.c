/*
    comfort.c

	Initial version: 2020.7.21
    Lastest update: 2020.10.8
    Author: mfp
*/
#include "headers.h"

void com_dry(HOUSE *house, ROBOT *robot)
{
    (*house).setd=1;
    //write_statu(house,robot,1);
}

void com_clean(HOUSE *house, ROBOT *robot)
{
    (*house).setc=1;
    //write_statu(house,robot,1);
}

void com_settemp(HOUSE *house, ROBOT *robot,int change)
{
    if(change==1) (*house).tempset++;
    else (*house).tempset--;
    write_statu(house,robot,2);
}