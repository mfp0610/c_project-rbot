/*
    login.c

    Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: Mengfp
*/
#include "headers.h"

void start_func()
{
    int flag;
    start_page();//画出开始界面

    login_page(); //画出登录界面
    mouseinit();
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(120,550,240,600)==1) {flag=1; break;}
        if(mouse_press(360,550,480,600)==1) {flag=2; break;}
        if(mouse_press(240,630,360,680)==1) {flag=3; break;}
    }
    switch(flag)
    {
        case 1:
        {
            register_page();
            user_register();
        }
        break;
        case 2:
        {
            findback_page();
            user_findback();
        }
        break;
        case 3:
        {
            exit_window();
            exit_pro();
        }
        break;
        default: break;
    }
}

void user_register()
{
    clrmous(MouseX, MouseY);
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        //if(bioskey(1)) exit(0);
    }
}

void user_findback()
{
    clrmous(MouseX, MouseY);
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        //if(bioskey(1)) exit(0);
    }
}

void exit_pro()
{
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(200,200,500,500)==1) exit(0);
    }
}