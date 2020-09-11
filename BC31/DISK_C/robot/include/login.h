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

void start_func(); //开始页面的逻辑
void login_func(); //登陆界面逻辑
void user_register(); //注册界面逻辑
void user_findback(); //找回界面逻辑
void exit_pro(); //推出窗口逻辑

int login_comp(char *user, char *cod); 
int judge_rightpassword(char *user, char *code);
void judge(char *str, int *p); //登录信息比对
/*
fp:记录输入是否是密码
fn:记录是否要求输入是数字
*/
void input(int x1,int x2,int y1,int y2, char *s, int max_len, int fp, int fn, int backcolor); //输入内容
void creatlist(USER *user);

#endif