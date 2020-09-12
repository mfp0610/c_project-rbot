/*
    login.c

    Initial version: 2020.7.13
    Lastest update: 2020.9.12 
    Author: hhw
*/
#include "headers.h"

void start_func()
{
    //start_page();//画出开始界面
    login_page(); //画出登录界面
    mouseinit();
    login_func(); //进入登录界面 

    /*****调试临时使用*****/
    mainWindow();
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
            MouseS = 0;
			if (login_comp(usr.user, usr.code)) //信息正确
            {
                flag = 1;
                break;
            }    
            else continue;
        }
        if(mouse_press(100,615,220,655)==1)
        {
		    flag = 2;
            break;
        }
        if(mouse_press(380,615,500,655)==1)
        {
            flag = 3;
            break;
        }
        if(mouse_press(240,650,360,700)==1)
        {
            flag = 4;
            break;
        }
        
    }
    switch (flag)
    {
        case 1:
            {
                MouseS = 0;
                clrmous(MouseX, MouseY);
                mainWindow(); //程序主界面进入接口
            }
            break;
        case 2:
            {
                MouseS = 0;
                clrmous(MouseX, MouseY);
                register_page();
                user_register();
            }
            break;
        case 3:
            {
                MouseS = 0;
                clrmous(MouseX, MouseY);
                findback_page();
                user_findback();
            }
            break;
        case 4:
            {
                MouseS = 0;
                clrmous(MouseX, MouseY);
                exit_window();
                exit_pro();
            }
            break;
        default: break;
    }
}


void user_register()
{
    int flag, f1=1, f2=1;
    USER usr; //用户信息
    char ver_cod[5]; //输入验证码
    char ver_cod1[5]; //随机验证码
    usr.user[0]='\0';
    usr.code[0]='\0';
    usr.tel[0]='\0';
    ver_cod[0]='\0';
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(180,300,500,350)==1&&f2) //输入账号
            input(180,300,500,350,usr.user,15,0,0,WHITE);
        if(mouse_press(180,375,500,425)==1&&f2) //输入密码
            input(180,375,500,425,usr.code,15,1,0,WHITE);
        if(mouse_press(220,450,500,500)==1&&f2) //输入电话
            input(220,450,500,500,usr.tel,15,0,1,WHITE);
        if(mouse_press(220,525,360,575)==1&&f2) //输入验证码
            input(220,525,360,575,ver_cod,15,0,1,WHITE);
        if(mouse_press(360,525,500,575)==1&&f1&&f2)
        {
            MouseS = 0, f1=0;
            random_vc(ver_cod1); //生成随机数
            outtextxy(370,575,ver_cod1,2,2,32,BLACK); //输出随机数
        }
        if(mouse_press(120,625,240,675)==1&&f2) //注册判断
        {
            MouseS = 0;
            if(register_func(usr.user,usr.code,usr.tel,ver_cod,ver_cod1))
            {
                flag = 1, f2=0;
                break;
            }
            else continue;
        }
        if(mouse_press(360,625,480,675)==1)
        {
            flag = 1;
            break;
        }
    }
    if(flag==1)
    {
        MouseS = 0;
        clrmous(MouseX, MouseY);
        login_page();
        login_func();
    }
}

void user_findback()
{
    int flag=0, f1=1, f2=1;
    USER usr; //用户信息
    char ver_cod[5]; //验证码
    char ver_cod1[5]; //随机验证码
    char code[15]; //找回的密码
    usr.user[0]='\0';
    usr.code[0]='\0';
    usr.tel[0]='\0';
    ver_cod[0]='\0';
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(180,300,500,350)==1&&f2) //输入账号
            input(180,300,500,350,usr.user,15,0,0,WHITE);
        if(mouse_press(180,375,500,425)==1&&f2) //输入电话
            input(180,375,500,425,usr.tel,15,0,1,WHITE);
        if(mouse_press(220,450,360,500)==1&&f2) //输入验证码
            input(220,450,360,500,ver_cod,15,0,1,WHITE);
        if(mouse_press(360,450,500,500)==1&&f1&&f2)
        {
            MouseS = 0, f1=0;
            if (findback_func(usr.user,code,usr.tel)) //验证账号和手机号
            {
                random_vc(ver_cod1); //生成随机数

                outtextxy(510,459,ver_cod1,2,2,32,BLACK); //输出随机数
            }
        }
        if(mouse_press(120,600,240,650)==1&&f2) //找回密码判断
        {
            MouseS = 0;
            if (strcmp(ver_cod,ver_cod1)==0) //判断验证码
            {
                outtextxy(230,535,code,2,2,20,BLACK);
                flag = 1, f2=0;
            }
            else 
            {
                outtextxy(230,535,"error",2,2,20,BLACK);
                continue;
            }
        }
        if(mouse_press(360,625,480,675)==1)
        {
            flag = 1;
            break;
        }
    }
    if(flag==1)
    {
        MouseS = 0;
        clrmous(MouseX, MouseY);
        login_page();
        login_func();
    }
    clrmous(MouseX, MouseY);
}

void exit_pro()
{
    int flag;
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
            flag = 1;
            break;
        }
    }
    if(flag==1)
    {
        clrmous(MouseX, MouseY);
        login_page();
        login_func();
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

int login_comp(char *user, char *code)
{
	int state1 = 1;//是否输入的变量
	int state2 = 1;
	while (1)
	{
		judge(user, &state1);
		judge(code, &state2);
		if (state1 == 1 || state2 == 1)
			break;
		else if (state1 == 0 && state2 == 0)
		{
			if (judge_rightpassword(user, code))
				return 1;
			else
				break;
		}
	}
	return 0;
}

int judge_rightpassword(char *user, char *code)	
{
	int len;
	int i;
	FILE *fp;
	USER *u;
	if ((fp = fopen("data\\user.dat", "rb+")) == NULL)
	{
		printf("cannot open file UserData.dat");
		Delaytime(3000);
		exit(1);
	}
	fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);//比对文件长度
	for (i = 0; i < len; i++)
	{
		if ((u = (USER*)malloc(sizeof(USER))) == NULL)
		{
			printf("memoryallocation runs wrong in lgfunc.c");
			Delaytime(3000);
			exit(1);
		}
		fseek(fp, i * sizeof(USER), SEEK_SET);
		fread(u, sizeof(USER), 1, fp);
		if (strcmp(user, u->user) == 0)//用户名匹配
		{
			if (strcmp(code, u->code) != 0)//密码不配
			{
				puthz(405,558,"密码错误",24,25,'H',BLACK);
				if (u != NULL)
				{
					free(u);
					u = NULL;
				}
				break;
			}
			else if (strcmp(code, u->code) == 0)//密码匹配
			{
				puthz(405,558,"登录成功",24,25,'H',BLACK);
				if (u != NULL)
				{
					free(u);
					u = NULL;
				}
				Delaytime(1000);
				if (fclose(fp) != 0)
				{
					printf("\n cannot close Database");
					Delaytime(3000);
					exit(1);
				}
				return 1;
				//切换界面
			}
		}
		if (u != NULL)
		{
			free(u);
			u = NULL;
		}
	}
	if (i == len)
	{
		puthz(405,558,"该账号不存在",24,25,'H',BLACK);//走到最后一位
	}
	if (u != NULL)
	{
		free(u);
		u = NULL;
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database");
		Delaytime(3000);
		exit(1);
	}
	return 0;
}

void judge(char *str, int *p)
{
    if (strlen(str) != 0)
    {
        *p = 0;
    }
}
