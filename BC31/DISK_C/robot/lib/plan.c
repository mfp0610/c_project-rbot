#include "headers.h"
FILE *fpde1;

/***heap实现优先队列部分***/
void swapnode(NODE1 *a, NODE1 *b)
{
    NODE1 x=*a;
    *a=*b, *b=x;     
}
void put(NODE1 *heap, int *size, NODE1 d)
{
    int now,next;
    heap[++(*size)]=d;
    now=(*size);
    while(now>1)
    {
        next=now>>1;
        if(heap[now].val>=heap[next].val) return;
        swapnode(&heap[now],&heap[next]);
        now=next;
    }
}
void del(NODE1 *heap, int *size)
{
    int now,next;
    heap[1]=heap[(*size)--];
    now=1;
    while(now*2<=(*size))
    {
        next=now*2;
        if(next<(*size)&&heap[next+1].val<heap[next].val) next++;
        if(heap[now].val<=heap[next].val) return;
        swapnode(&heap[now],&heap[next]);
        now=next;                      
    }
    return;
}
/***完成优先队列的实现***/

int val_func(int a,NODE beg,int x,int y) //估价函数
{
    return a+abs(beg.x-x)+abs(beg.y-y);
}

int BFS(NODE beg,NODE end,NODE1 *node,int sz,HOUSE *house)
{
    NODE1 heap[M];
    int hp_sz=0; //定义优先队列

    int vis_map[N][N]={0}; //地图访问情况
    int dir[4][2]={{0,1},{0,-1},{-1,0},{1,0}}; //方向数组
    int i,newx,newy;

    node[++sz].x=beg.x;
    node[sz].y=beg.y;
    node[sz].dis=0;
    node[sz].val=val_func(node[sz].dis,beg,node[sz].x,node[sz].y);
    node[sz].id=sz;
    node[sz].last=-1;
    put(heap,&hp_sz,node[sz]);
    while(hp_sz!=0)
    {
        NODE1 hed=heap[1];
        del(heap,&hp_sz);
        vis_map[hed.x][hed.y]=1;
        for(i=0;i<4;i++)
        {
            newx=dir[i][0]+hed.x;
            newy=dir[i][1]+hed.y;
            if(newx>=0&&newx<=100&&newy>=0&&newy<=100
            &&!vis_map[newx][newy]&&pd_pass((*house).mp1[newx][newy]))
            {
                vis_map[newx][newy]=1;
                node[++sz].x=newx;
                node[sz].y=newy;
                node[sz].dis=hed.dis+1;
                node[sz].last=hed.id;
                node[sz].id=sz;
                node[sz].val=val_func(node[sz].dis,beg,node[sz].x,node[sz].y);
                put(heap,&hp_sz,node[sz]);
                if(newx==end.x&&newy==end.y) return sz;
            }
        }
    }
    return -1;
}


void get_path(NODE *road, int *cnt, NODE1 *node, int x)
{
    if(node[x].last==-1) 
    {
        road[++(*cnt)].x=node[x].x;
        road[(*cnt)].y=node[x].y;
        return;
    }
    get_path(road,cnt,node,node[x].last);
    road[++(*cnt)].x=node[x].x;
    road[(*cnt)].y=node[x].y;
}

int Astarmove(NODE beg, NODE end, ROBOT *robot, HOUSE *house)
{
    NODE1 node[M];
    int nd_sz=0; //定义结点记录数组
    NODE road[M];
    int rd_sz=0; //定义路径记录数组
    
    char dir;
    int i;
    
    fpde1=fopen("debug\\debug1.txt","w");

    nd_sz=BFS(beg,end,node,0,house); //宽度优先搜索得到路径
    if(nd_sz==-1) return 0;
    get_path(road,&rd_sz,node,nd_sz); //规范化路径
    for(i=2;i<=rd_sz;i++)
    {
        if(road[i].x-road[i-1].x==1) dir='s';
        if(road[i].x-road[i-1].x==-1) dir='w';
        if(road[i].y-road[i-1].y==1) dir='d';
        if(road[i].y-road[i-1].y==-1) dir='a';
        fprintf(fpde1,"1 %d %d %c\n",road[i].x,road[i].y,dir);
        Delaytime(100);
        moveupdate(house,robot,dir);
    }
    fclose(fpde1);
    return 1;
}