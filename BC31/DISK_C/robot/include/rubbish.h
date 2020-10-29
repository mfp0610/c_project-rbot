/*
    rubbish.h
    
    Initial version: 2020.10.25
    Lastest update: 2020.10.25
    Author: hhw
*/
#ifndef _RUBBISH_H_
#define _RUBBISH_H_

#include "headers.h"

int func_clean(NODE *rubbish, HOUSE *house, ROBOT *robot, USER *usr); //清洁界面函数
void set_rub(NODE *rubbish,HOUSE *house);
void col_rub(int *f,NODE *rubbish,HOUSE *house,ROBOT *robot);

#endif