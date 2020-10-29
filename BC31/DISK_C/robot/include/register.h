/*
    register.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.9.12
    Author: hhw
*/
#ifndef _REGISTER_H_
#define _REGISTER_H_

#include "headers.h"

void random_vc(char *c); //生成随机验证码
int register_func(char *user,char *code,char *tel,char *vc,char *vc1); //注册信息处理
int findback_func(char *user,char *code,char *tel); //找回用户信息
void input_database(char *user,char *code,char *tel); //注册信息输入数据库
void output_database(char *user,char *code,char *tel,int *f); //输出数据库信息
int check_data(char *user,char *code,char *tel); //检查账号和电话与数据库信息是否匹配
int check_user(char *user); //检查账号是否已经注册

#endif