/*
    login.c

    Initial version: 2020.7.13
    Lastest update: 2020.9.12 
    Author: mfp & hhw
*/
#include "headers.h"

int login_func(USER *us)
{
    int flag;
    USER usr; //用户信息
    usr.user[0]='\0';
    usr.code[0]='\0';
    mouseinit();
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(180,350,500,400)==1) //输入账号
            input(180,350,500,400,usr.user,15,0,0,WHITE);
        if(mouse_press(180,450,500,500)==1) //输入密码
            input(180,450,500,500,usr.code,15,1,0,WHITE);
        
        if(mouse_press(200,550,400,600)==1)
        {
			if (login_comp(usr.user, usr.code)) //信息正确
            {
                clrmous(MouseX, MouseY);
                strcpy((*us).user,usr.user);
                return 1;
            }    
            else continue;
        }
        if(mouse_press(100,615,220,655)==1)
        {
            clrmous(MouseX, MouseY);
            register_page();
            nocombo();
            user_register();
            nocombo();
            continue;
        }
        if(mouse_press(380,615,500,655)==1)
        {
            clrmous(MouseX, MouseY);
            findback_page();
            nocombo();
            user_findback();
            nocombo();
            continue;
        }
        if(mouse_press(240,650,360,700)==1)
        {
            clrmous(MouseX, MouseY);
            exit_window();
            if(exit_pro()==1) return 0;
            nocombo();
            continue;
        }  
    }
}


void user_register()
{
    int f1=1, f2=1;
    int len; //电话号码长度
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
        len=strlen(usr.tel);
        if(mouse_press(360,525,500,575)==1&&f1&&f2)
        {
            if(check_user(usr.user)!=1)
            {
                if(usr.code[0]!='\0')
                {
                    if(len==11)
                    {
                        f1=0;
                        random_vc(ver_cod1); //生成随机数
                        bar(170,588,370,615,MISTY_ROSE);
                        outtextxy(370,575,ver_cod1,2,2,32,BLACK); //输出随机数
                    }
                    else
                    {
                        bar(170,588,370,615,MISTY_ROSE);
                        puthz(170,588,"手机号码错误",24,25,'H',BLACK);
                    }  
                }
                else
                {
                    bar(170,588,370,615,MISTY_ROSE);
                    puthz(170,588,"请输入密码",24,25,'H',BLACK);
                } 
            }
            else
            {
                bar(170,588,370,615,MISTY_ROSE);
                puthz(170,588,"该账号已经注册",24,25,'H',BLACK);
            }  
        }
        if(mouse_press(120,625,240,675)==1&&f2) //注册判断
        {
            if(register_func(usr.user,usr.code,usr.tel,ver_cod,ver_cod1))
            {
                f2=0;
                continue;
            }
            else continue;
        }
        if(mouse_press(360,625,480,675)==1)
        {
            clrmous(MouseX, MouseY);
            login_page();
            nocombo();
            return;
        }
    }
}

void user_findback()
{
    int f1=1, f2=1;
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
        if(mouse_press(220,375,500,425)==1&&f2) //输入电话
            input(220,375,500,425,usr.tel,15,0,1,WHITE);
        if(mouse_press(220,450,360,500)==1&&f2) //输入验证码
            input(220,450,360,500,ver_cod,15,0,1,WHITE);
        if(mouse_press(360,450,500,500)==1&&f1&&f2)
        {
            if (findback_func(usr.user,code,usr.tel)) //验证账号和手机号
            {
                f1=0;
                random_vc(ver_cod1); //生成随机数
                bar(510,459,650,509,MISTY_ROSE);
                bar(230,510,450,590,MISTY_ROSE);
                outtextxy(510,459,ver_cod1,2,2,32,BLACK); //输出随机数
            }
        }
        if(mouse_press(120,600,240,650)==1&&f2) //找回密码判断
        {
            if (strcmp(ver_cod,ver_cod1)==0) //判断验证码
            {
                bar(230,510,450,590,MISTY_ROSE);
                outtextxy(230,535,code,2,2,20,BLACK);
                f2=0;
                continue;
            }
            else 
            {
                bar(230,510,450,590,MISTY_ROSE);
                puthz(230,535,"输入的验证码错误",24,25,'H',BLACK);   
                /*outtextxy(230,535,"error",2,2,20,BLACK);*/
                continue;
            }
        }
        if(mouse_press(360,600,480,650)==1)
        {
            clrmous(MouseX, MouseY);
            login_page();
            nocombo();
            return;
        }
    }
}

int exit_pro()
{
    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        if(mouse_press(300,450,330,480)==1)
            return 1;
        if(mouse_press(470,450,500,480)==1)
        {
            clrmous(MouseX, MouseY);
            login_page();
            nocombo();
            return 0;
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
				bar(405,558,505,608,MISTY_ROSE);
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
				bar(405,558,505,608,MISTY_ROSE);
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
