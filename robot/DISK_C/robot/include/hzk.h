/*
    hzk.h
    
    Initial version: 2020.7.13
    Lastest update: 2020.7.22
    Author: Mengfp
*/
#ifndef _HZK_H_
#define _HZK_H_

#include "headers.h"

void puthz(int x,int y,char *s,int size,int part,int form,int color); //输出一行汉字文本
/*
支持四种字体：F H K S
支持四种字号：16 24 32 48
*/
void putEngletter(int x1,int y1,int ascii,int mx,int my,int color); //输出一个英文字母
void outtextxy(int x,int y,char *c,int mx,int my,int part,int color); //输出一行英文文本

#endif
