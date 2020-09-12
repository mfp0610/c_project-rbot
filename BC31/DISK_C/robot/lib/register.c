/*
    register.c

    Initial version: 2020.9.12
    Lastest update: 2020.9.12 
    Author: hhw
*/
#include "headers.h"


void random_vc(char *vc)
{
    int a;
    int i;
    int x[4];
    srand((unsigned)(time(NULL)));
    a=rand()%9000+1000;
    x[0]=a/1000;
    x[1]=a/100%10;
    x[2]=a/10%10;
    x[3]=a%10;
    for ( i = 0; i < 4; i++)
    {
        vc[i]=x[i]+'0';
    }
    vc[4]='\0';
}

int register_func(char *user,char *code,char *tel,char *vc,char *vc1)
{
    if (strcmp(vc,vc1)==0)
    {
        input_database(user,code,tel); //写入数据库
        puthz(405,558,"注册成功",24,25,'H',BLACK);
        Delaytime(2000);
        return 1;
    }
    else
        return 0; 
}

int findback_func(char *user,char *code,char *tel)
{
    int f=0;
    output_database(user,code,tel,&f); //读取输出数据库数据
    if(f)
    {
        Delaytime(2000);
        return 1;    
    }
    return 0; 
}

void input_database(char *user1,char *code1,char *tel1)
{
    FILE *fp;
	USER *u;
	char n;
	if ((fp = fopen("data\\user.dat", "rb+" )) == NULL)//建立数据库
	{
		printf("cannot open file UserData.dat");
		Delaytime(3000);
		exit(1);
	}
    if ((u = (USER*)malloc(sizeof(USER))) == NULL)
	{
		printf("memoryallocation runs wrong in lgfunc.c");
		Delaytime(3000);
		exit(1);
	}
    memset(u,'\0',sizeof(USER));
    strcpy(u->user,user1);
    strcpy(u->code,code1);
    strcpy(u->tel,tel1);
    fseek(fp, 0, SEEK_END);//跳转至文件末尾
    fwrite(u, sizeof(USER), 1, fp);//把用户信息写入文件
    if (u != NULL)
	{
		free(u);
		u = NULL;
	}
	if (fclose(fp) != 0)
	{
		printf("\n cannot close Database.");
		Delaytime(3000);
		exit(1);
	}
}

void output_database(char *user,char *code,char *tel,int *f)
{
    if (check_data(user,code,tel))
    {
        *f = 1;
    }
    else
    {
        puthz(230,535,"账号或手机号错误",24,25,'K',BLACK);
        *f = 0;
    }
}

int check_data(char *user,char *code,char *tel)
{
    int len;
	int i;
	FILE* fp;
	USER* u = NULL;
    if ((fp = fopen("data\\user.dat", "rb+")) == NULL)//建立数据库
	{
		printf("cannot open file UserData.dat");
		Delaytime(3000);
		exit(1);
	}
    fseek(fp, 0, SEEK_END);
	len = ftell(fp) / sizeof(USER);
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
        if (strcmp(u->user, user)==0&&strcmp(u->tel, tel)==0)
		{
			strcpy(code,u->code);
            if (u != NULL)
			{
				free(u);
				u = NULL;
			}
			if (fclose(fp) != 0)
			{
				printf("\n cannot close Database.");
				Delaytime(3000);
				exit(1);
			}
			return 1;
		}
		free(u);
		u = NULL;
	}
	if (u != NULL)
	{
		free(u);
		u = NULL;
	}
    if (fclose(fp) != 0)
	{
		printf("\n cannot close Database.");
		Delaytime(3000);
		exit(1);
	}
	return 0;
}
