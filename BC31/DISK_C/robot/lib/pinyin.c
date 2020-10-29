/*
    pinyin.c
    
    Adapted by pervious version
    Initial version: 2020.10.27
    Lastest update: 2020.10.27
    Author: mfp
*/
#include "headers.h"

int Init_qhwh(int *qhwh)
{
	int i;
	for(i=0;i<MAXTXT;i++)
	{
		qhwh[i]=0;
	}
	return 0;
}


void SaveEnQhwh(FILE *fp,EN *en)//2
{
    int i=0;
    while(!feof(fp)&&i<120)
    {
        fscanf(fp,"%s",&(en[i].str));//读取字符??

        fscanf(fp,"%d",&(en[i].qhwh));//读取区号位号

        i++;
    }
    fclose(fp);
}
void SaveChQhwh(FILE *fp,CH * ch)
{
    int i=0;
    while(!feof(fp)&&i<463)
    {
        fscanf(fp,"%s", ch[i].str );//读取字符
        fscanf(fp,"%d",&(ch[i].qhwh));//读取区号位号
        i++;
    }
    fclose(fp);
}


int FindChQhwh(CH *ch,char *temp,int num_tab,int qhwh)//3
{
    int  i;
    //对字符进行比对，找到则进行赋值
    for(i=0;i<463;i++)
    {
        if(strncmp(temp,ch[i].str,num_tab)==0)
            {
                qhwh=ch[i].qhwh;
                break;
            }
    }
    return qhwh;
}

int FindEnQhwh(EN *en,char temp)//4
{
    int i,qhwh;
    //对字符进行比对，找到则进行赋值
    for(i=0;i<120;i++)
    {
        if(strncmp( &temp,en[i].str,1)==0)
            {
                qhwh=en[i].qhwh;
                break;
            }
    }
    return qhwh;
}

int CheckQhwhNum(int *qhwh)//11
{
    int num_qhwh=0,i=MAXTXT;
    while(i >= 1)
    {
        if(qhwh[i-1]== 0)
        {
            ++num_qhwh;
            --i;

        }
        else break;
    }

    return (MAXTXT-num_qhwh);
}

//白色（LIGHT_GRAY）光标
void CursorWhite
(
	Coordinate current_show_position,int show_size){
	bar(current_show_position.x,current_show_position.y,current_show_position.x+2,current_show_position.y+show_size,LIGHT_GRAY);
}

//黑色光标
void CursorBlack
(
	Coordinate current_show_position,int show_size){
	bar(current_show_position.x,current_show_position.y,current_show_position.x+2,current_show_position.y+show_size,0);
}

void ClearKey(void)//2
{
	union REGS key;

	key.h.ah = 0x0c;
	key.h.al = 0x00;
	int86(0x21, &key, &key);
}

void DeleteShow(Area show_area,Coordinate * current_show_position,int show_size )//1
{	
	
	//初始化real_rb_x，使其指向定位
    int real_rb_x=((show_area.rb.x - show_area.lt.x)/show_size)*show_size + show_area.lt.x;
    //int real_rb_y=((show_area.rb.y - show_area.lt.y)/show_size)*show_size + show_area.lt.y;
    if(current_show_position->x>show_area.lt.x || current_show_position->y > show_area.lt.y)//框内是否有字的检测
    {
		//有字有两种情况①光标不在最左侧即左侧有字符②光标在最左侧但不在第一行即上面有字符
        if(current_show_position->x > show_area.lt.x )					//①
            current_show_position->x =current_show_position->x-show_size;	//定位往前移一格
        else	//②
        {
            current_show_position->x = real_rb_x- show_size;		//x移到倒数第二位
            current_show_position->y = current_show_position->y- show_size;		//y移到上一行
        }
    }
    ShowWhite( current_show_position, show_size);
}

int ShowPerCharacter(int qhwh,Area show_area,Coordinate * current_position,int color,int size,char *hzk_dir)//2
{
    int i=0,j=0,k=0;
    int x=current_position->x;
    int y=current_position->y;
    int real_rb_x= ((show_area.rb.x - show_area.lt.x)/size)*size + show_area.lt.x;

    FILE *hzk;//定义汉字库文件指针
    char *hzk_file;//定义汉字缓存数组
    int width_byte=0;//定义字节长度
    int qh=0,wh=0;//定义区号位号
    unsigned char *bitmap;//定义bmp指针，用来储存字形码
    long offset;//定义偏移量
    int size_read=0;//定义汉字读取有效长度
    if(x==real_rb_x) x=x-size;

    if((hzk_file=(char *)malloc(sizeof(char)*512))==NULL)//如果动态分配bmp指针内存失败，则直接返回
    {
		bar(0,0,1024,768,STRONG_RED);
		getch();
        exit(1);
    }

    if(size%4!=0&&size<=8)//如果字体太小或者不是4的倍数，则直接返回
    {
        bar(0,0,1024,768,STRONG_RED);
        exit(1);
    }
    else
    {
        size_read=((size+4)/8)*size;//初始化汉字读取有效长度
    }

    sprintf(hzk_file,"%s\\HZK%dK",hzk_dir,size);//把汉字库的数据写入汉字缓存数组中

    if((hzk=fopen(hzk_file,"rb"))==NULL)//如果汉字库文件打开为空，则直接返回
    {
		puthz(0,0,"汉字库读取失败",32,32,'H',STRONG_RED);
		getch();
        exit(1);
    }

    if((bitmap=(char *) malloc(sizeof(char)*size_read))==NULL)//如果动态分配bmp指针内存失败，则直接返回
    {
		puthz(0,0,"内存分配失败",32,32,'H',STRONG_RED);
		getch();
        exit(1);
    }

    qh=qhwh/100;//初始化区号
    wh=qhwh%100;//初始化位号
    offset=(long) (94*((int) qh-1)+((int) wh-1))*size_read;//初始化偏移量

    fseek(hzk,offset,SEEK_SET);//根据偏移量寻找汉字库的该汉字的字形码
    fread(bitmap,sizeof(char),size_read,hzk);//读取汉字库中的该汉字的字形码

    width_byte=(size+4)/8;//计算字节数宽度

    for(i=0;i<size;i+=1)
    {
        for(j=0;j<width_byte;j+=1)
        {
            for(k=0;k<8;k+=1)
            {
                if(GetBit(k+1,bitmap[i*width_byte+j])==1)//如果该像素点需要打印
                {

                    Putpixel64k(x+j*8+k, y+i, color);

                }
            }
        }
    }
    CheckArea(show_area,current_position, size);
    free(hzk_file);
    free(bitmap);
	hzk_file = NULL;
	bitmap = NULL;
    fclose(hzk);
    return 0;
}

int CheckArea(Area area,Coordinate *current_position,int size)//4
{
    if( (current_position->x+size*2) <=area.rb.x)//如果当前位置x轴不越出边界，则初始位置后移
    {
        current_position->x+=size;
    }

    else if( (current_position->y+size*2)<= area.rb.y )//如果当前位置y轴不越出边界，则初始位置换行
    {
        current_position->y+=size;
        current_position->x=area.lt.x;
    }
    else 
	{	
		current_position->x=((area.rb.x - area.lt.x)/size)*size + area.lt.x;	//stay where you are
	}
	return 0;
}

void DeleteTab(Coordinate * current_en_position,CH* ch,EN* en,char *temp ,int * num_tab,int *ch_qhwh)//3
{
    int en_qhwh,i;

    Area show_ch_area={ {IX,IY+WIDTH1} , {IX+LENGTH,IY+WIDTH1+WIDTH2} };
    Area show_en_area={ {IX,IY} , {IX+LENGTH,IY+WIDTH1} };
    Coordinate current_ch_position ={IX+5,IY+WIDTH1+5};
	bar(IX+5+16*(*num_tab-1),IY+5,IX+5+7*16,IY+5+30,LIGHT_GRAY);//删除用的bar

    --(*num_tab);		//拼音数减一
	
    *ch_qhwh = FindChQhwh(ch,temp, *num_tab, *ch_qhwh);		//在num_tab少了一个之后重新在汉字库中寻找匹配值
    current_en_position->x=IX+5;		//
    current_en_position->y=IY+5;		//设置英文输入起始位置

	bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);	//清空输入法汉字输出区域
	//重新输出文字信息
    for(i=0;i<*num_tab;i++)
    {
        en_qhwh = FindEnQhwh(en,temp[i]);
        ShowPerCharacter(en_qhwh,show_en_area, current_en_position ,0x000000,16,"HZK");
    }

    for(i=0;i<5;i++)
    {
        ShowPerCharacter(217+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
        ShowPerCharacter((*ch_qhwh)+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
    }
}

int ShowChTab(Area show_area,Coordinate current_show_position/*文本输出的初始位置的左上角*/, 
    int show_size/*有48，36，28*/,int *qhwh, HOUSE *house, ROBOT *robot, USER *usr, int *mode)//7
{
    union
    {
        int key;
        char c[2];
    }u;
	Coordinate first_show_position = current_show_position;
    CH * ch=NULL;//定义汉字符号结构体
    EN * en=NULL;//定义英文符号结构体
    char temp[500],temp1;          //定义临时变量缓存
    int i,ch_qhwh,en_qhwh,num_tab=0,num_qhwh=0;
    FILE *hanzi;            //定义汉字符号文件指针
    FILE *fuhao;            //定义英文符号文件指针

    int poscode;
    NODE mp,mto; //鼠标点击后行动坐标

   Area show_ch_area={ {IX,IY+WIDTH1} , {IX+LENGTH,IY+WIDTH1+WIDTH2} };
    Area show_en_area={ {IX,IY} , {IX+LENGTH,IY+WIDTH1} };
    Coordinate current_ch_position ={IX+5,IY+WIDTH1+5};
    Coordinate current_en_position ={IX+5,IY+5};


    int real_rb_x= ((show_area.rb.x - show_area.lt.x)/show_size)*show_size + show_area.lt.x;	
	//初始化real_rb_x（最右点坐标），之后用最右值均用此

    if( ( ch=(CH *)malloc(sizeof(CH)*463) )==NULL )//如果动态分配内存失败，则直接返回
    {
		puthz(0,0,"内存分配失败",32,32,'H',STRONG_RED);
		getch();
        return(1);
    }
    if( ( en=(EN *)malloc(sizeof(EN)*120) )==NULL )//如果动态分配内存失败，则直接返回
    {
		puthz(0,0,"内存分配失败",32,32,'H',STRONG_RED);
		getch();
        return(1);
    }

    if((hanzi = fopen("chat\\hanzi.txt","r")) == NULL)//hanzi和fuhao是文件句柄
    {
		puthz(0,0,"汉字文件打开错误",32,32,'H',STRONG_RED);
		getch();
        return (1) ;
    }
    if((fuhao = fopen("chat\\fuhao.txt","r")) == NULL)
    {
		puthz(0,0,"符号文件打开错误",32,32,'H',STRONG_RED);
		getch();
        return (1) ;
    }

    

    SaveChQhwh(hanzi,ch);	//	初始化汉字输入库，将hanzi.txt里的汉字信息全部一个个转移到ch这个结构体中去
    SaveEnQhwh(fuhao,en);	//	初始化英文输入库，将fuhao.txt里的英文信息也全部一个个转移到en这个结构体中去

    num_qhwh=CheckQhwhNum(qhwh);//计算当前字符个数，总共有几个qhwh代表的字符，作用就是之后在整段聊天打印的时候需要
	//初始的光标位置，即文本输出的位置
    CursorBlack(current_show_position,show_size);//光标涂黑（相当于出现光标）
    delay(400);
    CursorWhite(current_show_position,show_size);//光标涂白（隐藏光标），白即BRIGHR_GREEN

    ClearKey();//清除键盘缓存

    draw_bactr(robot);
    write_statu(house,robot,3);
    while(1)//进入按键循环
    {
        newmouse(&MouseX, &MouseY, &press);
        timepass(house,robot,usr,3);
        if(mouse_press(LB+37,UB+410,LB+127,UB+450)==1) //进入默认模式
        {
            nocombo();
            free(ch);
            free(en);
            fclose(hanzi);
            fclose(fuhao);
            ClearKey();
            if(*mode!=1) *mode=1;
            else *mode=0;
            clrmous(MouseX, MouseY);
            draw_react(usr,*mode);
            return 2;
        }
        if(mouse_press(LB+147,UB+410,LB+237,UB+450)==1) //进入谜语模式
        {
            nocombo();
            free(ch);
            free(en);
            fclose(hanzi);
            fclose(fuhao);
            ClearKey();
            if(*mode!=2) *mode=2;
            else *mode=0;
            clrmous(MouseX, MouseY);
            draw_react(usr,*mode);
            return 2;
        }
        if(mouse_press(LB+57,UB+470,LB+217,UB+510)==1) //返回控制面板
        {
            free(ch);
            free(en);
            fclose(hanzi);
            fclose(fuhao);
            ClearKey();
            return 3;
        }
        if(mouse_press(LB+140,UB+10,LB+250,UB+40)==1) //返回主菜单
        {
            free(ch);
            free(en);
            fclose(hanzi);
            fclose(fuhao);
            ClearKey();
            return 0;
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
        
        if(!kbhit()) continue;
        u.key=bioskey(0);//获取按键信息，key是int型

        /*if(u.c[1]==0x1) //键入esc退出
        {
			//归位
            free(ch);
            free(en);
            fclose(hanzi);
            fclose(fuhao);
            ClearKey();
            CursorWhite(current_show_position,show_size);//光标涂白
            return 3;
        }*/

		/**********
		当num_tab==0时，
		均对输入框操作
		以下
		**********/
        if(u.c[1]==0x1c&& num_tab==0)//键入回车发送消息
        {
            //褰掍綅
            free(ch);
            free(en);
			ch = NULL;
			en = NULL;
            fclose(hanzi);
            fclose(fuhao);
            ClearKey();
            CursorWhite(current_show_position,show_size);
            return 1;
        }

		
        else if(u.c[1]==0x48 && num_tab==0)//键入 光标向上（UP上键
        {
            if(current_show_position.y>show_area.lt.y )		//	判断之后是否会出界
            {
                num_qhwh=num_qhwh-(real_rb_x- show_area.lt.x)/show_size;	//num_qhwh减去整整一行的字符数
                CursorWhite(current_show_position,show_size);
                current_show_position.y-=show_size;
                CursorBlack(current_show_position,show_size);
            }

        }

		
        else if(u.c[1]==0x50 && num_tab==0)//键入 光标向下（DOWN下键）
        {
            if((current_show_position.y+2*show_size)<=show_area.rb.y)	//这里*2是因为current_show_position定位的时左上角，故得判断顶端往下两行（即向下一行）的操作之后不会出界
            {
				num_qhwh=num_qhwh+(real_rb_x- show_area.lt.x)/show_size;	//num_qhwh加上整整一行的字符数
                CursorWhite(current_show_position,show_size);
                current_show_position.y+=show_size;
                CursorBlack(current_show_position,show_size);
            }

        }

		
        else if(u.c[1]==0x4b&& num_tab==0)//键入 光标向左（LEFT）
        {
            if( current_show_position.x > show_area.lt.x || current_show_position.y>show_area.lt.y)//判断下一步不会出界
            {
                CursorWhite(current_show_position,show_size);
                if(current_show_position.x > show_area.lt.x )//确认光标不会左移出输入框
                    current_show_position.x = current_show_position.x-show_size;//定位左移一个单位
                else
                {
					//若左移出输入框则定位到上一行字符串尾
                    current_show_position.x =real_rb_x;
                    current_show_position.y =current_show_position.y-show_size;

                }
                --num_qhwh;//不论哪种情况，num_qhwh都是要减1（由键入LEFT键决定）
                CursorBlack(current_show_position,show_size);//显示到现在定位的后面
            }

        }
		//在y处需要*2也是current)_show_position定位在左上角惹的祸，用来判断下一行在不在界内
        else if(u.c[1]==0x4d&& num_tab==0)//键入 光标向右（RIGHT）
		{
            if((current_show_position.x+show_size)<=real_rb_x|| (current_show_position.y+2*show_size)<=show_area.rb.y)//纭?璁ょ幇鍦ㄥ畾浣嶅湪姝ｇ‘妗嗗??
            {
                CursorWhite(current_show_position,show_size);
                if(current_show_position.x <= real_rb_x - show_size)//确认还在离最后面的字的定位有至少一个字以上的空间
                    current_show_position.x =current_show_position.x+show_size;//定位右移一个单位
                else
                {
					//若左移出输入框则定位到下一行字符串首（似乎只对两行以上的输入方式有效	//右移？
                    current_show_position.x = show_area.lt.x;
                    current_show_position.y =current_show_position.y+show_size;

                }
                ++num_qhwh;
                CursorBlack(current_show_position,show_size);
            }

        }

        else if(u.c[1]==0xe && num_tab==0)//键入删除键（backspace），删除定位前一个字符
        {
            if(current_show_position.x>first_show_position.x || current_show_position.y>first_show_position.y)//濡傛灉涓嶅湪绗?涓�涓?瀛楃殑浣嶇疆鎵嶅彲浠ヨ繘琛?
			{
				CursorWhite(current_show_position,show_size);
				DeleteShow( show_area,& current_show_position, show_size );//如果不在第一个字的位置才可以进行
				qhwh[num_qhwh-1]=0;//当前字符区号位号置0
				--num_qhwh;//字符个数减去1
            }
			CursorBlack(current_show_position,show_size);
        }

        else if(u.c[1]==0x39&& num_tab==0&&num_qhwh<15)//键入空格
        {
            if((current_show_position.x+show_size)<=real_rb_x || (current_show_position.y+2*show_size)<=show_area.rb.y)
            {
                CursorWhite(current_show_position,show_size);
                if(current_show_position.x <= real_rb_x - show_size)//确认还在离最后面的字的定位有至少一个字以上的空间
                    current_show_position.x =current_show_position.x+show_size;//图像上的空格，等下字符个数凭空加一
                else
                {
					//满了就初始化重新输入
                    current_show_position.x = show_area.lt.x;
                    current_show_position.y =current_show_position.y+show_size;

                }
                ++num_qhwh;//字符个数+1
                CursorBlack(current_show_position,show_size);
            }
        }


        else if(u.c[0]>='a'&& u.c[0]<='z'&&num_tab<6&&num_qhwh<15)//键入字母，注意 这里是拼音的字母
        {
            num_tab++;
            temp[num_tab-1]=(char) (u.c[0]);	//temp的容量是500，肯定够了
            ch_qhwh = FindChQhwh(ch,temp, num_tab,ch_qhwh);		
			//去这个函数中与之前保存好的ch里面的所有汉字作比较，找到目标汉字，
			//但此时有很多匹配值，所以在后面会全部put出来
            en_qhwh = FindEnQhwh(en,temp[num_tab-1]);	//到英文库中找到输入的字母，直接显示出来
            if(num_tab<=6)	//限制了拼音最多输入6位
            ShowPerCharacter(en_qhwh,show_en_area, &current_en_position ,0x000000,16,"HZK");	//这里先把拼音的字母输出来
            //Putbmp64k(589,633,"bmp\\part.bmp");		//这里是输入法显示框（之前是输入框操作
			bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);	
			
			
            current_ch_position.x = IX+5;	//从这个位置输出可能匹配的汉字
            current_ch_position.y = IY+WIDTH1+5;
            for(i=0;i<5;i++)	//一页显示五个可能值
            {
				//显示序号12345
                ShowPerCharacter(217+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
                //显示汉字，拼音相同的两个汉字区位码相差1
				ShowPerCharacter(ch_qhwh+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
            }

        }


        else if(u.c[1]==0xe && num_tab!=0)//tab框 键入删除键，删除输入法tab框
        {
            DeleteTab(& current_en_position, ch, en, temp ,& num_tab,& ch_qhwh);
        }
		
	/* 	else if(u.c[1]==0x1c && num_tab!=0)
		{
			u.c[0]='1';
		}
		
		else if(u.c[1]==0x39&&num_tab!=0)
		{
			u.c[0]='1';
		} */


        else if(((u.c[1]==0x39||u.c[1]==0x1c)||(u.c[0]>='1'&&u.c[0]<='5'))&& num_tab!=0&&num_qhwh<15)//键入1-5  选择字符??
        {
			if(u.c[1]==0x39||u.c[1]==0x1c)
			{
				u.c[0]='1';
			}
            CursorWhite(current_show_position,show_size);
            ++num_qhwh;
            qhwh[num_qhwh-1]=ch_qhwh + u.c[0]-'1';	
			/***********************
			u.c[0]-'1'是取出整型的输入数字（而不是ascii码），		//两个ascii码值相减
			加上ch_qhwh之后就是指的是输入法框中的第几个汉字了
			***********************/

            ShowPerCharacter(qhwh[num_qhwh-1],show_area, &current_show_position,0x000000 , show_size,"HZK");	//这次是打印到输入框中了
		    bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);	
		    bar(IX,IY,IX+LENGTH,IY+WIDTH1,LIGHT_GRAY);	
			
			num_tab=0;	//拼音字母数归零
            current_ch_position.x = IX+5;	//汉字出现位置归位
            current_ch_position.y = IY+WIDTH1+5;	
            current_en_position.x=IX+5;		//拼音出现位置归位
            current_en_position.y=IY+5;
            CursorBlack(current_show_position,show_size);	//黑色光标重新出现

        }

        else if((u.c[1]==0x48/*UP*/||u.c[1]==0x4b||u.c[0]=='+'/*LEFT*/)&& num_tab!=0)//键入 向上或向左 翻页
        {
            ch_qhwh=ch_qhwh-5;		//汉字库中往前走五个（刚好翻页
  			bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);	
			
			current_ch_position.x = IX+5;	//输入法汉字显示的左上角的位置
            current_ch_position.y = IY+WIDTH1+5;	
            for(i=0;i<5;i++)
            {
                ShowPerCharacter(217+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
                ShowPerCharacter(ch_qhwh+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
            }

        }

        else if((u.c[1]==0x50/*DOWN*/||u.c[1]==0x4d/*RIGHT*/||u.c[0]=='-') && num_tab!=0)//键入 向下翻页
        {
            ch_qhwh=ch_qhwh+5;		//汉字库中往后走五个（刚好翻页
            
            bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);	
			
			current_ch_position.x = IX+5;
            current_ch_position.y = IY+WIDTH1+5;	
            for(i=0;i<5;i++)
            {
                ShowPerCharacter(217+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
                ShowPerCharacter(ch_qhwh+i,show_ch_area,&current_ch_position,0x000000,16,"HZK");
            }
        }
		
		else if(((u.c[0]==','||u.c[0]=='.'||u.c[0]=='?')||(u.c[0]>='0'&&u.c[0]<='9'))&&num_tab==0&&num_qhwh<15)//在文本输出框输出0-9数字或者，。？
        {
            temp1=(char) (u.c[0]);
            en_qhwh = FindEnQhwh(en,temp1);
            CursorWhite(current_show_position,show_size);
            ++num_qhwh;
            qhwh[num_qhwh-1]=en_qhwh;
            ShowPerCharacter(qhwh[num_qhwh-1],show_area, &current_show_position ,0x000000,show_size,"HZK");
            CursorBlack(current_show_position,show_size);

        }
		
		if(num_tab==0)
		{
			bar(IX,IY+WIDTH1,IX+LENGTH,IY+WIDTH1+WIDTH2,LIGHT_GRAY);
		}
    }
}

void ShowWhite(Coordinate * current_show_position,int show_size)
{
    int x,y,i,j,k;
    int width_byte=0;//定义字节长度
    x=current_show_position->x;
    y=current_show_position->y;

    width_byte=(show_size+4)/8;//计算字节数宽度

    for(i=0;i<show_size;i+=1)
    {
        for(j=0;j<width_byte;j+=1)
        {
            for(k=0;k<8;k+=1)
            {
               Putpixel64k(x+j*8+k, y+i, LIGHT_GRAY);
            }
        }
    }
}

int GetBit(int num,char ch)
{
    int i;
    int temp=1;
    for(i=0;i<8-num;i++)
    {
        temp*=2;
    }
    return (temp&ch)&&1;
}

void get_str(int *qhwh, char *incode)
{
	char *p=incode;	//incode的位置指针
	int num_qhwh = CheckQhwhNum(qhwh);
	int i;
	
	for(i=0;i<num_qhwh;i++)
	{
		qhwh2incode(*qhwh,p);
		p+=2;
		qhwh++;
	}
	*p = '\0';
	
}

void qhwh2incode(int qwh,char *incode)
{
	char qh,wh;
	qh = (char)(qwh/100);
	wh = (char)(qwh%100);
	incode[0] = qh+0xa0;
	incode[1] = wh+0xa0;
}