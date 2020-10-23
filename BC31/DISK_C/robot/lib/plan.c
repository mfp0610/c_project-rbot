#include "headers.h"
const int N=101;
bool map1[N][N];//地图：0表示可走，1表示障碍物
bool vis_map[N][N];
int direction[4][2]={{0,1},{0,-1},{-1,0},{1,0}};//上，下，左，右
int des_x,des_y;//目的地
int st_x,st_y;//出发地
int id;
int path[10001];
struct Node
{
  int x,y,dis,val;//当前点的 x/y/bfs距离/估价函数
  int last;//记录路径
  int id;
}node[10001];
int val_func(int a,int x,int y)//估价函数
{
  return a+abs(des_x-x)+abs(des_y-y);
}

//-------------分割线------------------heap实现优先队列部分----------------//
int heap_size,n;
Node heap[10001];  
void swap(Node &a,Node &b)
{
    Node x=a;
    a=b;
    b=x;     
}
void put(Node d)
{
  int now,next;
  heap[++heap_size]=d;
  now=heap_size;
  while(now>1)
  {
    next=now>>1;
    if(heap[now].val>=heap[next].val) return;
    swap(heap[now],heap[next]);
    now=next;           
  }    
}
Node del()
{
  int now,next;
  Node res;
  res=heap[1];
  heap[1]=heap[heap_size--];
  now=1;
  while(now*2<=heap_size)
  {
    next=now*2;
    if(next<heap_size&&heap[next+1].val<heap[next].val) next++;
    if(heap[now].val<=heap[next].val) return res;
    swap(heap[now],heap[next]);
    now=next;                      
  } 
}
Node get()
{
 return heap[1];   
} 
//-------------分割线结束---------------------------------------------//
Node BFS()
{
  bool flag=0;//判断结束
  while(!flag)
  {
    Node hed=get();
    del();
    vis_map[hed.x][hed.y]=1;
    for(int i=0;i<4;i++)
    {
      int newx=direction[i][0]+hed.x;
      int newy=direction[i][1]+hed.y;
      if(newx>=0&&newx<=100&&newy>=0&&newy<=100&&!vis_map[newx][newy]&&!map1[newx][newy])
      {
        vis_map[newx][newy]=1;
        node[++id].x=newx;
        node[id].y=newy;
        node[id].dis=hed.dis+1;
        node[id].last=hed.id;
        node[id].id=id;
        node[id].val=val_func(node[id].dis,node[id].x,node[id].y);
        put(node[id]);
        if(newx==des_x&&newy==des_y)
        {
          return node[id];
        }
      }
    }
  }
}
void get_path(Node x)
{
  if(x.last==-1) 
  {
    printf("(%d,%d)\n",x.x,x.y);
    return;
  }
  get_path(node[x.last]);
  printf("(%d,%d)\n",x.x,x.y);
}
void()
{
  scanf("%d%d%d%d",&st_x,&st_y,&des_x,&des_y);//输入出发地和目的地 
  node[++id].x=st_x;
  node[id].x=st_y;
  node[id].dis=0;
  node[id].val=val_func(node[id].dis,node[id].x,node[id].y);
  node[id].id=id;
  node[id].last=-1;
  put(node[id]);
  Node init=BFS();
  get_path(init);
}