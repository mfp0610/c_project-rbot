/*
    pinyin.h
    
    Adapted by pervious version
    Initial version: 2020.10.27
    Lastest update: 2020.10.27
    Author: mfp
*/
#ifndef _PINYIN_H_
#define _PINYIN_H_

#include "headers.h"
#define MAXTXT 1000
#define IX 767
#define IY 310 //聊天框的左上角的坐标
#define LENGTH 240//聊天框的长度
#define WIDTH1 20 //拼音显示框的宽度
#define WIDTH2 20 //输入法汉字显示框的宽度
#define WIDTH3 30 //文本输出框的宽度
#define WIDTH4 250 //聊天框显示的宽度

typedef struct Coordinate{
	int x;
	int y;
}Coordinate;

typedef struct Area{
	Coordinate lt;
	Coordinate rb;
}Area;

typedef struct CH{
	int qhwh;
	char str[10];
}CH;

typedef struct EN{
	int qhwh;
	char str[10];
}EN;

int Init_qhwh(int *qhwh);
void SaveEnQhwh(FILE *fp,EN *en);//2
void SaveChQhwh(FILE *fp,CH * ch);
int FindChQhwh(CH *ch,char *temp,int num_tab,int qhwh);//3
int FindEnQhwh(EN *en,char temp);  //4
int CheckQhwhNum(int *qhwh); //11
void CursorWhite(Coordinate current_show_position,int show_size);
void CursorBlack(Coordinate current_show_position,int show_size);
void ClearKey(void); //2
void DeleteShow(Area show_area,Coordinate * current_show_position,int show_size ); //1
int ShowPerCharacter(int qhwh,Area show_area,Coordinate * current_position,int color,int size,char *hzk_dir); //2
int CheckArea(Area area,Coordinate *current_position,int size); //4
void DeleteTab(Coordinate * current_en_position,CH* ch,EN* en,char *temp ,int * num_tab,int *ch_qhwh); //3
int ShowChTab(Area show_area,Coordinate current_show_position/*文本输出的初始位置的左上角*/, 
	int show_size/*有48，36，28*/,int *qhwh, USER *usr, int *mode);
void ShowWhite(Coordinate * current_show_position,int show_size);
int GetBit(int num,char ch);
int reply_match(char * str,char *order,char *reply);
void get_str(int *qhwh, char *incode);
void qhwh2incode(int qwh,char *incode);

#endif