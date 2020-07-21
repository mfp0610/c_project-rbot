/*
    login.c

    Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: Mengfp
*/
#include "headers.h"

void start_func()
{
    SetSVGA64k();
	start_page();//画出开始界面
    getch();
    //login_page();//画出登陆界面
}