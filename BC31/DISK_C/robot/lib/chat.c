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
    
    Coordinate currentlu={IX+5,IY+WIDTH1+WIDTH2+5}; //文本输出的左上角坐标
    Area txt_area={{IX+5,IY+WIDTH1+WIDTH2+5},{IX+LENGTH-5,IY+WIDTH1+WIDTH2+WIDTH3-5}}; //文本输出的区域
    int *qhwh=(int*)malloc(sizeof(int)*MAXTXT); //区号位号
    char *incode=(char *)malloc(30*sizeof(char)); //标记输入内容
    char *quest=(char *)malloc(30*sizeof(char)); //标记谜语答案
    char *answer=(char *)malloc(30*sizeof(char)); //标记谜语答案
    int flag, f1=2;
    int mode=0;
    int show_y=IY-245;

    draw_bactr(robot);
    write_statu(house,robot,3);
    clrmous(MouseX, MouseY);

    while(1)
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,usr,3);
        if(mode==0)
        {
            puthz(IX+25,IY-140,"你好！我是你的",24,25,'K',BLACK);
            puthz(IX+25,IY-110,"家居机器人小科。",24,25,'K',BLACK);
            puthz(IX+10,IY-70,"想聊点什么呢？",32,32,'K',BLACK);
        }
        else if(mode==1)
        {
            bar(IX,IY,IX+LENGTH,IY+WIDTH1,LIGHT_GRAY); //拼音显示框
            bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY); //输入法汉字显示框
            bar(IX,IY+WIDTH1+WIDTH2,IX+LENGTH,IY+WIDTH1+WIDTH2+WIDTH3,LIGHT_GRAY); //文本输出框
            //bar(IX,IY-WIDTH4,IX+LENGTH,IY,MISTY_ROSE); //聊天框显示区域

            Init_qhwh(qhwh);
            flag=ShowChTab(txt_area,currentlu,16,qhwh,house,robot,usr,&mode);
            if(flag==0) 
            {
                free(qhwh);
                free(quest);
                free(answer);
                free(incode);
                return 1;
            }
            if(flag==1) 
                c_reply1(qhwh,&show_y);
            if(flag==2) continue ;
            if(flag==3)
            {
                nocombo();
                free(qhwh);
                free(quest);
                free(answer);
                free(incode);
                clrmous(MouseX, MouseY);
                return 0;
            }
        }
        else if(mode==2)
        {
            bar(IX,IY,IX+LENGTH,IY+WIDTH1,LIGHT_GRAY); //拼音显示框
            bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY); //输入法汉字显示框
            bar(IX,IY+WIDTH1+WIDTH2,IX+LENGTH,IY+WIDTH1+WIDTH2+WIDTH3,LIGHT_GRAY); //文本输出框
            //bar(IX,IY-WIDTH4,IX+LENGTH,IY,MISTY_ROSE); //聊天框显示区域
            
            if(f1==2)
            {
                make_ques(quest,answer);
                show_reply(quest,&show_y);
                Init_qhwh(qhwh);
                flag=ShowChTab(txt_area,currentlu,16,qhwh,house,robot,usr,&mode);
                if(flag==0)
                {
                    free(qhwh);
                    free(quest);
                    free(answer);
                    free(incode);
                    return 1;
                }
                if(flag==1)
                {
                    get_str(qhwh,incode);
                    show_incode(incode,&show_y);
                    f1=check_answer(incode,answer);
                    continue;
                }
                if(flag==2) continue ;
                if(flag==3)
                {
                    nocombo();
                    free(qhwh);
                    free(quest);
                    free(answer);
                    free(incode);
                    clrmous(MouseX, MouseY);
                    return 0;
                }
            }
            else if(f1==1)
            {
                show_reply("恭喜你，答对啦！",&show_y);
                f1=2;
                Delaytime(1000);
                continue;
            }
            else
            {
                show_reply("别灰心，再试一次！",&show_y);
                show_reply("也可输入“放弃”换一题",&show_y);
                Init_qhwh(qhwh);
                flag=ShowChTab(txt_area,currentlu,16,qhwh,house,robot,usr,&mode);
                if(flag==0)
                {
                    free(qhwh);
                    free(quest);
                    free(answer);
                    free(incode);
                    return 1;
                }
                if(flag==1)
                {
                    get_str(qhwh,incode);
                    show_incode(incode,&show_y);
                    if(check_answer(incode,"放弃"))
                    {
                        f1=2;
                        continue;
                    }
                    f1=check_answer(incode,answer);
                    continue;
                }
                if(flag==2) continue ;
                if(flag==3)
                {
                    nocombo();
                    free(qhwh);
                    free(quest);
                    free(answer);
                    free(incode);
                    clrmous(MouseX, MouseY);
                    return 0;
                }
            }
        }
        if(mouse_press(LB+37,UB+410,LB+127,UB+450)==1) //进入闲聊模式
        {
            nocombo();
            if(mode!=1)
            {
                bar(IX,IY-WIDTH4,IX+LENGTH,IY,MISTY_ROSE); //聊天框显示区域
                show_y=IY-245;
                mode=1;
            }
            else mode=0;
            clrmous(MouseX, MouseY);
            draw_react(usr,mode);
            draw_bactr(robot);
            write_statu(house,robot,3);
            continue;
        }
        if(mouse_press(LB+147,UB+410,LB+237,UB+450)==1) //进入谜语模式
        {
            nocombo();
            if(mode!=2)
            {
                bar(IX,IY-WIDTH4,IX+LENGTH,IY,MISTY_ROSE); //聊天框显示区域
                show_y=IY-245;
                mode=2;
            }
            else mode=0;
            clrmous(MouseX, MouseY);
            draw_react(usr,mode);
            draw_bactr(robot);
            write_statu(house,robot,3);
            continue;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回控制面板
        {
            nocombo();
            free(qhwh);
            free(quest);
            free(answer);
            free(incode);
            clrmous(MouseX, MouseY);
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
                draw_cantgo();
            }
        }
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1)
        {
            free(qhwh);
            free(quest);
            free(answer);
            free(incode);
            return 1;
        }
    }
}

void c_reply1(int *qhwh,int *show_y)
{
	char *order=(char *)malloc(30*sizeof(char)); //之后标记到文件中的问句部分
	char *reply=(char *)malloc(30*sizeof(char)); //之后标记到文件中的答句部分
	char *incode=(char *)malloc(30*sizeof(char)); //用户输入的内码序列
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
	
	get_str(qhwh,incode); //将qhwh转换成文字存在incode里面
	strcpy(str1,incode);
	reply_match(incode,order,reply); //将用户的信息与文件里存储的信息进行对比并得到回复
	strcpy(str2,reply);
	
	show_incode(str1,show_y); //将用户输入的信息打印到聊天框
	show_reply(str2,show_y); //将机器人回答的信息打印到聊天框

	free(order), order=NULL;
	free(reply), reply=NULL;
	free(incode), incode=NULL; //释放空间
}

int reply_match(char *str,char *order,char *reply)
{
    FILE *fp; //定义文件指针
    int f=0; //作为判断依据，匹配成功则1，失败则0
    fp=fopen("chat\\match.txt","rt");
    if(fp==NULL)
    {
        puthz(0,0,"匹配文件打开错误",32,32,'H',STRONG_RED);
        exit(1);
    }
    rewind(fp);
    while(feof(fp)==0)
    {
        fscanf(fp,"%s",order);
        fscanf(fp,"%s",reply);
        if(strcmp(order,str)==0)
        {
            f=1;
            fclose(fp);
            return;
        }
    }
    if(f==0)
        strcpy(reply,"抱歉，我不懂你在说什么");
    fclose(fp);
}

int make_ques(char *question,char *answer)
{
    FILE *game;
    int tm; //用来确定最终选择的题号
    int i=0; //标记暂时选择的题号

    srand((unsigned)(time(NULL)));
    tm=rand()%100;
    game=fopen("chat\\zimi.txt","r");
    if(game==NULL)
    {
        puthz(0,0,"文件打开错误",32,32,'H',STRONG_RED);
        getch();
        exit(1);
    }
    rewind(game); //使指针指向文件流的开头
    while(feof(game)==0) //当文件读取完毕或标记题号与选中题号相符时
    {	
        fscanf(game,"%s",question);
        fscanf(game,"%s",answer);
        if(i==tm) break;
        i++;
    }
    fclose(game);
    return tm;
}

int check_answer(char *incode,char *answer)
{
    if(strcmp(incode,answer)==0) return 1;
    return 0;
}

void show_incode(char *incode,int *y)
{
    int len=strlen(incode), line=1;
    int IY1=IY-5, WIDTHI=WIDTH4-10;
    unsigned int back[260][90];
    line=len/24+1;
    if(*y>=IY-5)
    {
        clrmous(MouseX, MouseY);
        get_image(IX,IY1-WIDTHI+line*20,IX+LENGTH,IY1-WIDTHI*2/3+line*20,*back);
        put_image(IX,IY1-WIDTHI,IX+LENGTH,IY1-WIDTHI*2/3,*back);
        get_image(IX,IY1-WIDTHI*2/3+line*20,IX+LENGTH,IY1-WIDTHI/3+line*20,*back);
        put_image(IX,IY1-WIDTHI*2/3,IX+LENGTH,IY1-WIDTHI/3,*back);
        get_image(IX,IY1-WIDTHI/3+line*20,IX+LENGTH,IY1,*back);
        put_image(IX,IY1-WIDTHI/3,IX+LENGTH,IY1-line*20,*back);
        bar(IX,IY1-line*20,IX+LENGTH,IY1,MISTY_ROSE);

        puthz1(IX,*y-line*20,"用户：");
	    puthz1(IX+48,*y-line*20,incode);
    }
    else
    {
        puthz1(IX,*y,"用户：");
	    puthz1(IX+48,*y,incode);
        *y+=(line*20);
    }
}

void show_reply(char *reply,int *y)
{
    int len=strlen(reply), line=1;
    int IY1=IY-5, WIDTHI=WIDTH4-10;
    unsigned int back[260][90];
    line=len/24+1;
    if(*y>=IY-5)
    {
        get_image(IX,IY1-WIDTHI+line*20,IX+LENGTH,IY1-WIDTHI*2/3+line*20,*back);
        put_image(IX,IY1-WIDTHI,IX+LENGTH,IY1-WIDTHI*2/3,*back);
        get_image(IX,IY1-WIDTHI*2/3+line*20,IX+LENGTH,IY1-WIDTHI/3+line*20,*back);
        put_image(IX,IY1-WIDTHI*2/3,IX+LENGTH,IY1-WIDTHI/3,*back);
        get_image(IX,IY1-WIDTHI/3+line*20,IX+LENGTH,IY1,*back);
        put_image(IX,IY1-WIDTHI/3,IX+LENGTH,IY1-line*20,*back);
        bar(IX,IY1-line*20,IX+LENGTH,IY1,MISTY_ROSE);

        puthz1(IX,*y-line*20,"小科：");
	    puthz1(IX+48,*y-line*20,reply);
    }
    else
    {
        puthz1(IX,*y,"小科：");
	    puthz1(IX+48,*y,reply);
        *y+=(line*20);
    }
}