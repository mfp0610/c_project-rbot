/*
    interface.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: mfp && hhw
*/
#ifndef _INTERF_H_
#define _INTERF_H_

#include "headers.h"

void start_func(); //开始页面的逻辑
/*
fp:记录输入是否是密码
fn:记录是否要求输入是数字
*/
void input(int x1,int x2,int y1,int y2, char *s, int max_len, int fp, int fn, int backcolor); //输入内容
void start_page(); //绘制开始界面
void login_page(); //绘制登陆界面
void register_page(); //绘制注册界面
void findback_page(); //绘制找回界面
void exit_window(); //画出退出确认界面

#endif