/*
    login.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.9.8
    Author: hhw
*/
#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "headers.h"

typedef struct userinfo{
	char user[15];
	char code[20];
}USER;
void start_func(); //开始页面的逻辑
void login_func(); //登陆界面逻辑
void user_register(); //注册界面逻辑
void user_findback(); //找回界面逻辑
void exit_pro(); //推出窗口逻辑

void creatlist(USER *user);

#endif