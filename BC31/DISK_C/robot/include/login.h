/*
    login.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.9.12
    Author: hhw
*/
#ifndef _LOGIN_H_
#define _LOGIN_H_

#include "headers.h"

typedef struct userinfo{
	char user[15];
	char code[15];
    char tel[15];
}USER;

int login_func(USER *usr); //登陆界面逻辑
void user_register(); //注册界面逻辑
void user_findback(); //找回界面逻辑
int exit_pro(); //推出窗口逻辑
int login_comp(char *user, char *cod); 
int judge_rightpassword(char *user, char *code);
void judge(char *str, int *p); //登录信息比对
void creatlist(USER *user);

#endif