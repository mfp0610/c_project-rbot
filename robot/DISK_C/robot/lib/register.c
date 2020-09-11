/*
    login.c

    Initial version: 2020.7.13
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