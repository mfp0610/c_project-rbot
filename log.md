# mfp&hhw家用机器人模拟系统工作日志

[TOC]

## 工作计划

### 必要结构

登陆界面：账号密码

有个学长实现了收验证码功能 可以试试

找回密码也是一个可以尝试的点，一位学长用了学号，私以为可以尝试设置安全问题

整个程序中很重要的就是避障和规划路线，目前感觉需要点算法来搞，我来想办法

其余就是各种功能

### 功能

主要需要实现的功能

#### 1.充电

电量低自动充电，人工操作充电

#### 2.垃圾相关

放置垃圾，打扫垃圾，倒垃圾

#### 3.除草

庭院除草

#### 4.舒适度

各房间空调温度，空气湿度，pm2.5等数据

一位学长搞成了低温变蓝，高温变红，可以参考

#### 6.房间的操作

开门关门，开窗关窗

#### 7.远程遥控

遥控机器人进行移动

#### 8.巡逻

定向巡逻，自由巡逻

#### 9.手机上的骚操作

这个是大有可为的地方，也许可以引进一些高级的东西实现ai聊天，我来想办法



## 代码结构及分工

> svga.c   svga头文件   --- 使用前人代码
>
> mouse.c   鼠标文件  ---  mfp改编前人代码使用
>
> hzk.c   汉字库文件   ---  mfp改编前人代码使用
>
> mysys.c   自己编写的系统函数   --- mfp编写
>
> >mfp：
> >
> >void Delaytime(int time);    延时函数
> >
> >void swap(int *x,int *y);   交换函数
>
> drawbas.c   画图文件   ---- mfp编写
>
> > mfp：
> >
> > void setbkcol(int color);   设置背景颜色
> >
> > void line(int x1,int y1,int x2,int y2,int color);   绘制直线
> >
> > void thick_line(int x1,int y1,int x2,int y2,int thick,int color);   绘制粗直线
> >
> > void bar(int x1,int y1,int x2,int y2,int color);   绘制填充矩形
> >
> > void rect(int x1,int y1,int x2,int y2,int color);   绘制空心矩形
> >
> > void fill_rect(int x1,int y1,int x2,int y2,int color,int edgecolor);   绘制实心矩形（带边框）
> >
> > void fill_circle(int xc,int yc,int r,int color);   绘制实心圆
>
> drawrobot.c   画机器人文件（可调节大小）   ---mfp编写
>
> >mfp：
> >
> >void drawrobot_front(int x,int y,int size);   画正面机器人
> >
> >void drawrobot_front_hello(int x,int y,int size);   画问好机器人
> >
> >void drawrobot_left(int x,int y,int size);   画左视机器人
> >
> >void drawrobot_right(int x,int y,int size);   画右视机器人
> >
> >void drawrobot_back(int x,int y,int size);   画背面机器人
> >
> >void clearrobot(int x,int y,int size);   清空机器人
>
> login.c   开始界面逻辑文件   ---mfp&hhw编写
>
> > mfp：
> >
> > void start_func();   开始页面的逻辑
> >
> > void input(int x1,int x2,int y1,int y2, char *s, int max_len, int fp, int backcolor);   输入函数   
> >
> > hhw：
> >
> > void login_func();   登陆界面逻辑   *未完成，需要调试
> >
> > void user_register();   注册界面逻辑   *未完成，需要调试
> >
> > void user_findback();   找回界面逻辑   *未完成，需要调试
> >
> > void exit_pro();   推出窗口逻辑   *未完成，需要调试
>
> interface.c   界面绘制文件   ---mfp&hhw编写
>
> > mfp：
> >
> > void start_page();   绘制开始界面
> >
> > void login_page();   绘制登陆界面
> >
> > void register_page();   绘制注册界面
> >
> > void findback_page();   绘制找回界面
> >
> > hhw：
> >
> > void exit_window();   画出退出确认界面

