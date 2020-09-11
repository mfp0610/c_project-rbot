/*
    login.c

    Initial version: 2020.7.13
    Lastest update: 2020.9.11 
    Author: Mengfp
*/
#include "headers.h"

void start_func()
{
    start_page();//画出开始界面
    login_page(); //画出登录界面
    mouseinit();
    login_func(); //进入登录界面 
}

void login_func()
{
    int flag;
    USER usr; //用户信息
    usr.user[0]='\0';
    usr.code[0]='\0';
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(180,350,500,400)==1) //输入账号
            input(180,350,500,400,usr.user,15,0,0,WHITE);
        if(mouse_press(180,450,500,500)==1) //输入密码
            input(180,450,500,500,usr.code,15,1,0,WHITE);
        if(mouse_press(200,550,400,600)==1)
        {
            bar(0,0,1024,720,MARINE_BLUE);
            break;
        }
        if(mouse_press(100,615,220,655)==1)
        {
            clrmous(MouseX, MouseY);
            register_page();
            user_register();
            break;
        }
        if(mouse_press(380,615,500,655)==1)
        {
            clrmous(MouseX, MouseY);
            findback_page();
            user_findback();
            break;
        }
        if(mouse_press(240,650,360,700)==1)
        {
            clrmous(MouseX, MouseY);
            exit_window();
            exit_pro();
            break;
        }
    }
    switch()
    {
        if(mouse_press(200,550,400,600)==1)
        {
            bar(0,0,1024,720,MARINE_BLUE);
            break;
        }
        if(mouse_press(100,615,220,655)==1)
        {
            clrmous(MouseX, MouseY);
            register_page();
            user_register();
            break;
        }
        if(mouse_press(380,615,500,655)==1)
        {
            clrmous(MouseX, MouseY);
            findback_page();
            user_findback();
            break;
        }
        if(mouse_press(240,650,360,700)==1)
        {
            clrmous(MouseX, MouseY);
            exit_window();
            exit_pro();
            break;
        }
    }
}

void user_register()
{
    USER usr; //用户信息
    char ver_cod[5]; //验证码
    usr.user[0]='\0';
    usr.code[0]='\0';
    usr.tel[0]='\0';
    ver_cod[0]='\0';
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(180,300,500,350)==1) //输入账号
            input(180,300,500,350,usr.user,15,0,0,WHITE);
        if(mouse_press(180,375,500,425)==1) //输入密码
            input(180,375,500,425,usr.code,15,1,0,WHITE);
        if(mouse_press(220,450,500,500)==1) //输入电话
            input(220,450,500,500,usr.tel,15,0,1,WHITE);
        if(mouse_press(220,525,500,575)==1) //输入验证码
            input(220,525,500,575,ver_cod,15,0,1,WHITE);
        if(mouse_press(120,625,240,675)==1)
        {
            clrmous(MouseX, MouseY);
            bar(0,0,1024,720,MARINE_BLUE);
            break;
        }
        if(mouse_press(360,625,480,675)==1)
        {
            clrmous(MouseX, MouseY);
            login_page();
            login_func();
            break;
        }
    }
}

void user_findback()
{
    USER usr; //用户信息
    char ver_cod[5]; //验证码
    usr.user[0]='\0';
    usr.tel[0]='\0';
    ver_cod[0]='\0';
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(180,300,500,350)==1) //输入账号
            input(180,300,500,350,usr.user,15,0,0,WHITE);
        if(mouse_press(180,375,500,425)==1) //输入电话
            input(180,375,500,425,usr.tel,15,0,1,WHITE);
        if(mouse_press(220,450,500,500)==1) //输入验证码
            input(220,450,500,500,ver_cod,15,0,1,WHITE);
        if(mouse_press(120,600,240,650)==1) 
        {
            clrmous(MouseX, MouseY);
            bar(0,0,1024,720,MARINE_BLUE);
            break;
        }
        if(mouse_press(360,600,480,650)==1)
        {
            clrmous(MouseX, MouseY);
            login_page();
            login_func();
            break;
        }
    }
}

void exit_pro()
{
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(300,450,330,480)==1) 
        {
            exit(0);
            break;
        }
        if(mouse_press(470,450,500,480)==1)
        {
            clrmous(MouseX, MouseY);
            login_page();
            login_func();
            break;
        }
    }
}

void input(int x1,int y1,int x2,int y2, char *s, int max_len, int fp, int fn,int backcolor)
{
	char value;
	int length=strlen(s);
	int width=16;  //字符宽度
    int flag;
	line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, BLACK);//绘制光标
	while(1)
	{
        int flag;
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press_out(x1,y1,x2,y2)==1)
        {
            s[length]='\0';
			line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, backcolor);	//覆盖光标
			break;
        }
        if(kbhit())
        {
            value=getch();
            if(value=='\n'||value=='\r') //判断到按下回车
            {
                s[length]='\0';
			    line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, backcolor);	//覆盖光标
			    break;
            }
		    else if(value=='\b')
		    {
			    clrmous(MouseX, MouseY);
                newmouse(&MouseX, &MouseY, &press);
                if(length==0) continue;
                line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, BLACK);	
			    bar(x1+5+width*(length-1), y1+3, x2, y2-3, backcolor);	//覆盖光标和最后一个字符
			    s[--length]='\0';
			    if(length+1<max_len) s[length+1]='\0';
			    line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, BLACK);  //重新绘制光标
		    }
            //尝试添加可通过方向键动态修改功能，待完善
            /*else if(value==224)
            {
                value1=getch();
                if(value1==72||value1==80) continue;
                else if(value1==75) 
                else if(value1==77) 
            }*/
		    else if(length<max_len)
		    {
			    if(fn&&(value>'9'||value<'0')) continue; //判断是否要求全数字
                clrmous(MouseX, MouseY);
                newmouse(&MouseX, &MouseY, &press);
                line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, backcolor);	//覆盖光标
			    //判断是否为密码，如果是，则需要保密
                if(!fp) putEngletter(x1-4+width*length, y1+8, (int)(value), 2,2,BLACK);  //显示字符
			    else fill_circle(x1+16+width*length, (y1+y2)/2, 4,BLACK); //显示小圆点
			    s[length++]=value;
			    line(x1+5+width*length, y1+3, x1+5+width*length, y2-3, BLACK);	//重新绘制光标
		    }
        }
	}
}
