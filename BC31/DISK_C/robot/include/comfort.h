/*
    comfort.h
    
    Initial version: 2020.10.24
    Lastest update: 2020.10.24
    Author: mfp
*/
#ifndef _COMFORT_H_
#define _COMFORT_H_

#include "headers.h"

void com_clean(HOUSE *house, ROBOT *robot); //清洁空气功能
void com_settemp(HOUSE *house, ROBOT *robot,int change); //更改设定温度功能

#endif