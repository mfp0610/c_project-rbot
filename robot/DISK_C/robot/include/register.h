/*
    login.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.9.12
    Author: hhw
*/
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "headers.h"

void random_vc(char *c); //生成随机验证码
int register_func(char *user,char *code,char *tel,char *vc,char *vc1); //注册信息处理
void input_database(char *user,char *code,char *tel); //注册信息输入数据库

#endif