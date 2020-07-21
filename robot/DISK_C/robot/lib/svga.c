/*
    svga.c
 
    Adapted by pervious version
    Initial version: 2020.7.12
    Lastest update: 2020.7.12
*/
#include "headers.h"

//设置svga显示模式
//模式1: 1024*768 256k
void SetSVGA256k()
{
	union REGS in;
	in.x.ax=0x4f02;
	in.x.bx=0x105;
	int86(0x10,&in,&in);
	if(in.x.ax!=0x004f)//若调用成功则返回0x004f
	{
		printf("Error in setting SVGA256,0x%x\n",in.x.ax);
		exit(1);
	}
}

//模式2: 1024*768 64k
void SetSVGA64k()
{
	union REGS in;
	in.x.ax=0x4f02;
	in.x.bx=0x117;
	int86(0x10,&in,&in);
	if(in.x.ax!=0x004f)//若调用成功则返回0x004f
	{
		printf("Error in setting SVGA64k,0x%x\n",in.x.ax);
		exit(1);
	}
}

//获得当前svga显示模式的信息，返回模式号
unsigned int GetSVGA()
{
	union REGS out;
	out.x.ax = 0x4f03;
	int86(0x10,&out,&out);
	if(out.x.ax!=0x004f)
	{
		printf("error!: ox%x\n",out.x.ax);
		exit(1);
	}
	return(out.x.bx);
}

/*
获取SVGA显示模式号bx。摘录常用的模式号如下：
				模式号		分辨率		颜色数
				0x101		640*480		256
				0x103		800*600		256
				0x104		1024*768	16
				0x105		1024*768	256
				0x110		640*480		32K
				0x111		640*480		64K
				0x112		640*480		16.8M
				0x113		800*600		32K
				0x114		800*600		64K
				0x115		800*600		16.8M
				0x116		1024*768	32K
				0x117		1024*768	64K
				0x118		1024*768	16.8M
*/



 /******************************************************
 功能说明：显存换页
 参数说明: page ,页面号
 ********************************************************/
unsigned int SelectPage(unsigned char page)
{
	union REGS r;
	static unsigned char old_page=0;    
	static unsigned char flag=0;
	r.x.ax=0x4f05;
	r.x.bx=0;
	if(!flag)
	{
		old_page=page;
		r.x.dx=page;
		int86(0x10,&r,&r);
		flag++;
	}
	if(page!=old_page)
	{
		old_page=page;
		r.x.dx=page;
		int86(0x10,&r,&r);
	}
	return 0;
}
 /********************************************************/

 /********************************************************
	功能说明 ：画点函数
	参数说明：x,y 所要画点位置 color 颜色
**********************************************************/
int putpixel(int x,int y,int color)
{
    unsigned char far *VideoBuffer=(unsigned char far*)0xa0000000L;
    unsigned long int pos;
    register int Newpage=0;
    //计算显存地址偏移量和对应的页面号，做换页操作 
    pos=((unsigned long int)y<<10)+x;
    Newpage=pos>>16;
    SelectPage(Newpage);
    VideoBuffer[pos]=color;
}
/**********************************************************
  功能说明：得到某点的颜色值；
  参数说明：x,y为该点的坐标；
  返回值：color为该点的颜色值
***********************************************************/ 

int getpixel(int x,int y)
{
    int color;
    unsigned char far *VideoBuffer=(unsigned char far*)0xa0000000L;
    unsigned long int pos;
    register int Newpage=0;
    /*计算显存地址偏移量和对应的页面号，做换页操作 */
    pos=((unsigned long int)y<<10)+x;
    Newpage=pos>>15;
    SelectPage(Newpage);
    color=VideoBuffer[pos];
    return color;
}

  
  
 /*******************************************************
 功能说明：  异或画点函数
 参数说明：   x,y为像素位置，color 为异或的颜色
 返回值：    无
/**********************************************************/
void Xorpixel (int x, int y, int color)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;

	/*要切换的页面号*/
	unsigned char newpage = 0;

	unsigned char oldpage;
	/*对应显存地址偏移量*/
	unsigned long int page;
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page=((unsigned long int)y << 10) + x;
	newpage=page >> 15;	                          /*32k个点一换页，除以32k的替代算法*/
		SelectPage(newpage);
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = video_buffer[page]^color;
}

/*************************************************************
功能函数：用64k的模式画点
参数说明：画点的位置
返回值说明： 无返回
***************************************************************/
void Putpixel64k(int x, int y,  int color)
{
	if(x>=0&&x<=1024&&y>=0&&y<=768)
	{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;
	
	/*要切换的页面号*/
	unsigned char newpage=0;
	
//	unsigned char oldpage=0;
	/*对应显存地址偏移量*/
	unsigned long int page;

	
	/*计算显存地址偏移量和对应的页面号，做换页操作*/
	page = ((unsigned long int)y << 10) + x;
	newpage = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	

		SelectPage(newpage);

	
	
	/*向显存写入颜色，对应点画出*/
	video_buffer[page] = color;	
    }
}

/***********************************************************
	功能说明：从硬盘读取8位BMP直接到显存
	参数说明：x，y坐标  name：文件路径
	返回值说明：
/***********************************************************/

int Readbmp256(int x,int y,char * path)
{
    FILE *fp;                   //指向图片文件的文件指针
    RGBQUAD * pc01;       //bmp颜色表结构指针
    unsigned char *buf;         //行像素缓存指针
    long int wide,high;         //图片宽度，长度
    long int perline;          //一行像素所占字节
    unsigned long int clrused;  //实际用的颜色数
    int i,j;
    unsigned int bitcount;

    if((fp=fopen(path,"rb"))==NULL)
    {
	    printf("there file can't open\n");
	    delay(5000);
	    exit(1);
	}


	fseek(fp,28L,0);          /*先判断是不是8位BMP*/
	fread(&bitcount,2,1,fp);
	if(bitcount!=8)
	{
	    printf("it is not 8");
	    delay(5000);
	    return 0;
	}


	fseek(fp,18L,0);         /*将文件指针移动到储存宽度的位置并读取数据*/
	fread(&wide,4,1,fp);
	fread(&high,4,1,fp);

	perline=(wide*8+31)/8;   /*一个扫面行所占的字节数，必须是4的倍数*/
	perline=perline/4*4;

	fseek(fp,46l,0);          /*得到实际使用颜色*/
	fread(&clrused,4,1,fp);

	if(clrused==0)
	{
	    clrused=1U<<8;
	}

	if((pc01=(RGBQUAD*)malloc(4L*clrused))==NULL)   /*依据使用颜色个数来分配空间*/
	{
	    printf("the color is wrong");
	    delay(5000); 
	    return 0;
	}
	
	fseek(fp,54L,0);            /*读取颜色表数据*/
	fread(pc01,4L*clrused,1,fp); 
	
	for(i=0;i<clrused;i++,pc01++)
	{
	    outportb(0x3c8,i);
	    outportb(0x3c9,pc01->R>>2);
	    outportb(0x3c9,pc01->G>>2);
	    outportb(0x3c9,pc01->B>>2);
	}
	free(pc01);

	buf=(unsigned char *)malloc(perline);
	if(buf==NULL)  /*分配动态行像素数据储存空间*/
		return 0;
	
	fseek(fp,54L+4L*clrused,0);              /*将每行的像素信息都显示出来*/
	for(i=high;i>-1;i--)
	{
	    fread(buf,perline,1,fp);
	    for(j=0;j<wide;j++)
	        putpixel(x+j,i+y,buf[j]);
	}
    free(buf);
    fclose(fp);
    return 1;
}

 
/*读取24位图片，参数x,y为图片位置，name为路径，返回值：0失败，1成功*/
int Putbmp64k(int x,int y,const char *path)
{
	 FILE *fpbmp;
	 WESHEN *buffer;//行像素缓存指针
	 long int width,height,linebytes;//一行像素所占字节数（含补齐空字节）
	/*循环变量*/
	int i, j;

	/*图片位深*/
	unsigned int bit;

	/*压缩类型数*/
	unsigned long int compression;

	/*打开文件*/
	if ((fpbmp = fopen(path, "rb")) == NULL)
	{
		return -1;
	}

	/*读取位深*/
	fseek(fpbmp, 28L, 0);
	fread(&bit, 2, 1, fpbmp);

	/*非24位图则退出*/
	if (bit != 24U)
	{
		return -1;
	}

	/*读取压缩类型*/
	fseek(fpbmp, 30L, 0);
	fread(&compression, 4, 1, fpbmp);

	/*采用压缩算法则退出*/
	if (compression != 0UL)
	{
		return -1;
	}

	/*读取宽度、高度*/
	fseek(fpbmp, 18L, 0);
	fread(&width, 4, 1, fpbmp);
	fread(&height, 4, 1, fpbmp);


	/*计算一行像素占字节数，包括补齐的空字节*/
	linebytes = (3 * width) % 4;

	if(!linebytes)
	{
		linebytes = 3 * width;
	}
	else
	{
		linebytes = 3 * width + 4 - linebytes;
	}

	/*开辟行像素数据动态储存空间*/
	if ((buffer = (WESHEN *)malloc(linebytes)) == 0)
	{
		return -1;
	}

	/*行扫描形式读取图片数据并显示*/
	fseek(fpbmp, 54L, 0);
	for (i = height - 1; i > -1; i--)
	{
		fread(buffer, linebytes, 1, fpbmp);	/*读取一行像素数据*/

		/*一行像素的数据处理和画出*/
		for (j = 0; j < width; j++)
		{
			/*0x117模式下，原图红绿蓝各8位分别近似为5位、6位、5位*/
			buffer[j].R >>= 3;
			buffer[j].G >>= 2;
			buffer[j].B >>= 3;
			Putpixel64k(j + x, i + y,
			((((unsigned int)buffer[j].R) << 11)
			| (((unsigned int)buffer[j].G) << 5)
			| ((unsigned int)buffer[j].B)));	/*计算最终颜色，红绿蓝从高位到低位排列*/
		}
	}

	free(buffer);
	fclose(fpbmp);
	return 0;
}


unsigned int Getpixel64k(int x, int y)
{
	/*显存指针常量，指向显存首地址，指针本身不允许修改*/
	unsigned int far * const video_buffer = (unsigned int far *)0xa0000000L;

	/*要切换的页面号*/
	unsigned char new_page;

	 /*对应显存地址偏移量*/
	unsigned long int page;

	 /*判断点是否在屏幕范围内，不在就退出*/
	if (x < 0 || x >(1024 - 1) || y < 0 || y >(768 - 1))
		return 0;

	 /*计算显存地址偏移量和对应的页面号，做换页操作*/
	 page = ((unsigned long int)y << 10) + x;
	 new_page = page >> 15;	/*32k个点一换页，除以32k的替代算法*/
	 SelectPage(new_page);

	 /*返回颜色*/
	 return video_buffer[page];
 }

/**************************************************
                9月26日编写
function:       get_image

description:     得到一片区域的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标，save 指向存储信息的数组

out:              无输出
**************************************************************/

void    get_image(int x0,int y0,int x1,int y1,unsigned int far *save)
{
	
	int i=0;                                   /*循环变量*/
	int j=0;
	int wide=x1-x0;
    int high=y1-y0;	
	
	unsigned   int far *VideoBuffer=(unsigned int far *)0xa0000000L  ;
	
	long int newpage=0;
//    long int oldpage=0;
	
	unsigned long pos;

	for(i=0;i<high;i++)
	{
		for(j=0;j<x1-x0;j++)
		{

		   pos=((unsigned long)(y0+i)<<10)+x0+j;

		   newpage=pos>>15 ;                         /*除以32k的替代算法*/

			
			 SelectPage(newpage);
			
			save[i*wide+j]=VideoBuffer[pos];

		}
	}

}



/**************************************************
				9月26日编写
function:       put_image

description:     显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标，save 指向存储信息的数组

out:              无输出
**************************************************************/

void    put_image(int x0,int y0,int x1,int y1,unsigned int far *save)
{

	int i=0;                                   /*循环变量*/
	int j=0;

	int wide=x1-x0;
	int high=y1-y0;

	unsigned   int far *VideoBuffer=(unsigned int far *)0xa0000000L ;

	long int newpage=0;
//	long int  oldpage=0;

	unsigned long pos;

	for(i=0;i<high;i++)
	{
		for(j=0;j<x1-x0;j++)
		{   
	        
	      pos=((unsigned long)(y0+i)<<10)+x0+j;
	
	      newpage=pos>>15 ;                         /*除以32k的替代算法*/
	
	      
			  SelectPage(newpage);
			

			VideoBuffer[pos]=save[i*wide+j];
		
		}
	}


}

/**************************************************
10月26日编写
function:       save_image

description:    显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息存到文件里面

out:            
**************************************************************/
void save_image(int x0, int y0, int x1, int y1)
{
	FILE * fp;                            /*定义文件指针*/
     
	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;


	int save = 0;



	char fg[20] = "saveim";
	fp = fopen(fg, "wb");                  /*建立保存背景的文件*/
	if (fp == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

			save = Getpixel64k(x0+j,y0+i);
			fwrite(&save,sizeof(int),1,fp);

		}
	}

	fclose(fp);

}


/**************************************************
10月26日编写
function:       printf_image

description:    从文件中读取这个背景像素

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息覆盖到界面上

out:
**************************************************************/

void  printf_image(int x0, int y0, int x1, int y1)
{
	FILE * fpo;                            /*定义文件指针*/

	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;

	unsigned   int save = 0;

	char  fas[20]="saveim";
	fpo = fopen(fas, "rb");                  /*建立保存背景的文件*/
	if (fpo == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

		 
			fread(&save,sizeof(int),1,fpo);
			Putpixel64k(x0 + j, y0 + i, save);

		}
	}

	fclose(fpo);

}


/**************************************************
10月26日编写
function:       save_image

description:    显示出存储空间的图像信息

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息存到文件里面

out:            
**************************************************************/
void save_image0(int x0, int y0, int x1, int y1)
{
	FILE * fp;                            /*定义文件指针*/
     
	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;


	int save = 0;



	char fg[20] = "saveim0.dat";
	fp = fopen(fg, "wb+");                  /*建立保存背景的文件*/
	if (fp == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

			save = Getpixel64k(x0+j,y0+i);
			fwrite(&save,sizeof(unsigned int),1,fp);

		}
	}

	fclose(fp);

}


/**************************************************
10月26日编写
function:       printf_image

description:    从文件中读取这个背景像素

Input:          x0,y0,左上角起始坐标，X1,Y2右下角坐标,将图像信息覆盖到界面上

out:
**************************************************************/

void  printf_image0(int x0, int y0, int x1, int y1)
{
	FILE * fpo;                            /*定义文件指针*/

	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;

	unsigned   int save = 0;

	char  fas[20]="saveim0.dat";
	fpo = fopen(fas, "rb+");                  /*建立保存背景的文件*/
	if (fpo == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}


	for (i = 0; i<high; i++)
	{
		for (j = 0; j<wide; j++)
		{

		 
			fread(&save,sizeof(unsigned int),1,fpo);
			Putpixel64k(x0 + j, y0 + i, save);

		}
	}

	fclose(fpo);

}


void  printf_image_2(int x0, int y0, int x1, int y1, int begin_y)
{
	FILE * fpo;                            /*定义文件指针*/

	int i = 0;                                   /*循环变量*/
	int j = 0;
	int wide = x1 - x0;
	int high = y1 - y0;
	int dy = begin_y - y0;

	unsigned   int save = 0;

	char  fas[20]="saveim";
	fpo = fopen(fas, "rb");                  /*建立保存背景的文件*/
	if (fpo == NULL)
	{
		printf("the file cant creat\n");
		exit(1);
	}

	for (i = 0; i<dy; i++)
	{
		for (j = 0; j<wide; j++)
		{
			fread(&save,sizeof(int),1,fpo);
		}
	}

	for (i = 0; i<high - dy; i++)
	{
		for (j = 0; j<wide; j++)
		{

		 
			fread(&save,sizeof(int),1,fpo);
			Putpixel64k(x0 + j, y0 + i, save);

		}
	}

	fclose(fpo);

}

