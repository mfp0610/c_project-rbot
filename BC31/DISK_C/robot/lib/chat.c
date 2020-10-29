/*
    chat.c
    
    Adapted by pervious version
    Initial version: 2020.10.27
    Lastest update: 2020.10.27
    Author: mfp
*/
#include "headers.h"

int func_react(HOUSE *house, ROBOT *robot, USER *usr)
{
    char value;
    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标
    
    int mode=0;
    Coordinate currentlu={IX+5,IY+WIDTH1+WIDTH2+5}; //文本输出的左上角坐标
	Area txt_area={{IX+5,IY+WIDTH1+WIDTH2+5},{IX+LENGTH-5,IY+WIDTH1+WIDTH2+WIDTH3-5}}; //文本输出的区域
	int *qhwh=(int*)malloc(sizeof(int)*MAXTXT); //区号位号
    int flag;

    draw_bactr(robot);
    write_statu(house,robot,3);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,3);
        
        if(mode==0)
        {
            
        }
        else if(mode==1)
        {
            flag=0;
            bar(IX,IY,IX+LENGTH,IY+WIDTH1,LIGHT_GRAY); //拼音显示框
            bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY); //输入法汉字显示框
            bar(IX,IY+WIDTH1+WIDTH2,IX+LENGTH,IY+WIDTH1+WIDTH2+WIDTH3,LIGHT_GRAY); //文本输出框
            Init_qhwh(qhwh);
            flag=ShowChTab(txt_area,currentlu,16,qhwh);
            if(flag==1) c_reply1(qhwh);
            //bar(IX,IY+WIDTH1+WIDTH2,IX+LENGTH,IY+WIDTH1+WIDTH2+WIDTH3,LIGHT_GRAY);
        }
        else if(mode==2)
        {

        }
        if(mouse_press(LB+37,UB+410,LB+127,UB+450)==1) //进入电量界面
        {
            nocombo();
            if(mode!=1) mode=1;
            else mode=0;
            clrmous(MouseX, MouseY);
            draw_react(usr,mode);
            continue;
        }
        if(mouse_press(LB+147,UB+410,LB+237,UB+450)==1) //进入舒适度界面
        {
            nocombo();
            if(mode!=2) mode=2;
            else mode=0;
            clrmous(MouseX, MouseY);
            draw_react(usr,mode);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回控制面板
        {
            nocombo();
            return 0;
        }
        if(kbhit())
        {
            Delaytime(50);
            value=getch();
            moveupdate(house,robot,value);   
        }
        get_conbot(house,robot);
        if(mouse_press(15,24,735,744)==1)
        {
            nocombo();
            poscode=getposition(MouseX, MouseY);
            mto.x=poscode/18;
            mto.y=poscode%18;
            mp.x=(*robot).px;
            mp.y=(*robot).py;
            if(!Astarmove(mp,mto,robot,house))
            {
                bar(1000,750,1024,768,BLACK);
            }
        }
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1)
            return 1;
    }
}


int c_chat1()
{
	Coordinate currentlu={IX+5,IY+WIDTH1+WIDTH2+5};	//文本输出的左上角坐标
	Area txt_area={{IX+5,IY+WIDTH1+WIDTH2+5},{IX+LENGTH-5,IY+WIDTH1+WIDTH2+WIDTH3-5}};	//文本输出的区域
	int *qhwh=(int*)malloc(sizeof(int)*MAXTXT);		//区号位号
    int flag=0;

	bar(IX,IY,IX+LENGTH,IY+WIDTH1,LIGHT_GRAY);	//拼音显示框
	bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);	//输入法汉字显示框
	bar(IX,IY+WIDTH1+WIDTH2,IX+LENGTH,IY+WIDTH1+WIDTH2+WIDTH3,LIGHT_GRAY);	//文本输出框
	
	if(qhwh==NULL)
	{
		puthz(0,0,"区号位号内存获取失败",16,16,'H',STRONG_RED);
		getch();
		exit(1);
	}
	
	while(flag!=3)
	{
		newmouse(&MouseX, &MouseY, &press);
        flag=0;
		Init_qhwh(qhwh);
		flag=ShowChTab(txt_area,currentlu,16,qhwh);
		bar(IX,IY+WIDTH1+WIDTH2,IX+LENGTH,IY+WIDTH1+WIDTH2+WIDTH3,LIGHT_GRAY);
		if(flag==0) return 1;
        if(flag==1)
		{
			c_reply1(qhwh);
			
		}
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1)
            return 1;
	}
}



void c_reply1(int *qhwh)
{
	int show_y;
	char *order = (char *)malloc(30*sizeof(char));	//之后标记到文件中的问句部分
	char *reply = (char *)malloc(30*sizeof(char));	//之后标记到文件中的答句部分
	char *incode = (char *)malloc(30*sizeof(char));	//用户输入的内码序列
	char str1[30];
	char str2[30];

	if(order==NULL)
	{
        puthz(0,0,"内存分配失败",16,16,'H',STRONG_RED);
		getch();
		exit(1);
	}
	if(reply==NULL)
	{
        puthz(0,0,"内存分配失败",16,16,'H',STRONG_RED);
		getch();
		exit(1);
	}
	if(incode==NULL)
	{
        puthz(0,0,"内存分配失败",16,16,'H',STRONG_RED);
		getch();
		exit(1);
	}
	
	get_str(qhwh,incode);	//将qhwh转换成文字存在incode里面
	strcpy(str1,incode);
	reply_match(incode,order,reply);//将用户的信息与文件里存储的信息进行对比并得到回复
	strcpy(str2,reply);
	bar(IX,IY-WIDTH4,IX+LENGTH,IY,MISTY_ROSE);//聊天框显示区域
	show_incode(str1,&show_y); //将用户输入的信息打印到聊天框
	show_reply(str2,show_y);
	free(order), order=NULL;
	free(reply), reply=NULL;
	free(incode), incode=NULL; //释放空间
}

void show_incode(char *incode,int *y)
{
	puthz(IX,IY-WIDTH4,"用户：",16,16,'K',BLACK);
	puthz(IX+48,IY-WIDTH4,incode,16,16,'K',BLACK);
	*y=IY-WIDTH4;
	*y=*y+20;
}

void show_reply(char *reply,int y)
{
	puthz(IX,y,"小科：",16,16,'K',BLACK);
	puthz(IX+48,y,reply,16,16,'K',BLACK);
}