/*
    plan.h
    
    Initial version: 2020.10.25
    Lastest update: 2020.10.25
    Author: mfp
*/
#ifndef _PLAN_H_
#define _PLAN_H_

#include "headers.h"
//heap实现优先队列部分
void swapnode(NODE1 *a, NODE1 *b);
void put(NODE1 *heap, int *size, NODE1 d);
void del(NODE1 *heap, int *size);
//完成优先队列的实现

int val_func(int a,NODE beg,int x,int y); //利用曼哈顿距离实现估价函数
int BFS(NODE beg,NODE end,NODE1 *node,int sz,HOUSE *house);
void get_path(NODE *road, int *cnt, NODE1 *node, int x);
int Astarmove(NODE beg, NODE end, ROBOT *robot, HOUSE *house);

#endif