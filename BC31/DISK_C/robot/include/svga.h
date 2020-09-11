/*
    svga.h
 
    Adapted by pervious version
    Initial version: 2020.7.12
    Lastest update: 2020.7.12 
*/
#ifndef _SVGA_H_
#define _SVGA_H_

#include "headers.h"

/*BMP文件头结构*/
typedef struct tagBITMAPFILEHEADER{
	int bfType;
	long bfsize;//文件大小，单位为字节
	int bfReserved1;//保留，必须为0
	int bfReserved2;//保留，必须为0
	long bfOffBits;
}BITMAPFILEHEADER;

/*BMP信息头结构*/
typedef struct tagBITMAPINFOHEADER{
	long biSize; /*信息头大小*/
	long biWidth; /*图像宽度*/
	long biHeight; /*图像高度*/
	int biPlanes; /*必须为1*/
	int biBitCount; /*每像素位数，必须为1，4，8，24*/
	long	biCompression;	/*  压缩方法 */
	long	biSizeImage;	/* 实际图像大小，必须是 4 的倍数 */
	long	biXPelsPerMeter;	/*  水平方向每米像素数 */
	long	biYPelsPerMeter;	/*  垂直方向每米像素数*/
	long	biClrUsed;	/*  所用颜色数*/
	long	biClrImportant;	/* 重要的颜色数 */
} BITMAPINFOHEADER;


typedef struct tagRGBQUAD
{
	unsigned char B;	/*蓝色分量，RED缩写*/
	unsigned char G;	/*绿色分量，GREEN缩写*/
	unsigned char R;	/*红色分量，BLUE缩写*/
	unsigned char reserved;		/*保留字*/
} RGBQUAD;

extern void SetSVGA256();
extern void SetSVGA64k();
extern unsigned int GetSVGA();


typedef struct
{
	unsigned char B;	/*蓝色分量，BLUE缩写*/
	unsigned char G;	/*绿色分量，GREEN缩写*/
	unsigned char R;	/*红色分量，RED缩写*/
} WESHEN;

extern unsigned int SelectPage(unsigned char page);
extern int putpixel(int x,int y,int color);
extern int getpixel(int x,int y);
extern void Xorpixel (int x, int y, int color);
extern void Putpixel64k(int x, int y,  int color);
extern unsigned int Getpixel64k(int x, int y);
extern int  Readbmp256(int x,int y,char * path);

 
 /*读取24位图片，参数x,y为图片位置，name为路径，返回值：0失败，1成功*/
extern int Putbmp64k(int x,int y,const char *path);
extern void  put_image(int x0,int y0,int x1,int y1,unsigned int far *save);
extern void get_image(int x0,int y0,int x1,int y1,unsigned int far *save);
extern void  printf_image0(int x0, int y0, int x1, int y1);
extern void save_image0(int x0, int y0, int x1, int y1);
extern void  printf_image(int x0, int y0, int x1, int y1);
extern void save_image(int x0, int y0, int x1, int y1);
extern void  printf_image_2(int x0, int y0, int x1, int y1, int begin_y);

#endif