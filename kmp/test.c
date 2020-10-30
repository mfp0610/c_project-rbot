#include<stdio.h>
#include<string.h>
#define N 1010
int count_str(char *str,char *tar);
int main()
{
    char s[N],s1[N];
    gets(s);
    gets(s1);
    printf("num:%d\n",count_str(s,s1));
    return 0;
}
int count_str(char *str,char *tar)
{
    int num=0,ne[40],l1,l2;
    int i,j;
    l1=strlen(str);
    l2=strlen(tar);
    str--;
    tar--;
    j=0,ne[0]=-1;
    for(i=2;i<=l2;i++)
	{
       while(j&&tar[i]!=tar[j+1]) j=ne[j];
       if(tar[j+1]==tar[i]) j++;
       ne[i]=j;
    }
    j=0;
    for(i=1;i<=l1;i++)
	{
        while(j>0&&tar[j+1]!=str[i]) j=ne[j];
        if(tar[j+1]==str[i]) j++;
        if(j==l2) num++;
    }
    return num;
}
