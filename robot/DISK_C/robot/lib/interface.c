/*
    interface.c

    Initial version: 2020.7.13
    Lastest update: 2020.7.13
    Author: 
*/
#include "headers.h"

void start_page()
{
    int i;
    setbkcol(MISTY_ROSE);
    puthz(187,90,"欢迎使用居家机器人模拟系统",48,50,'H',BLACK);
    drawrobot_front(200,600,1);
    //fill_rect(900,200,1000,400,MARINE_BLUE);
    //fill_circle(200,200,100,MARINE_BLUE);
    //Delaytime(10000);
    getch();
	//closegraph();
	return 0;
    
	
}