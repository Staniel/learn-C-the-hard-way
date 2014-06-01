/*************************************************************************
	> File Name: ex10.c
	> Author: Lixin Yao
    */
#include <stdio.h>
int main(int argc, char* argv[])
{
    int i;
    for (i=1;i<argc;i++)
    {
        printf("arg %d is : %s\n",i,argv[i]);
    }
    char* state[]={"yao","li","xin",NULL};
    int len=4;
    if ((argc-1)<len)
    len=argc-1;
    i=0;
    while(i<len)
    {
        state[i]=argv[i+1];
        i++;
    }
    //printf("null is %s\n",NULL);
    //argv[3]="ta";
    //printf("argc is %d\n",argc);
    //for (i=1;i<argc;i++)
    //{
    //    printf("arg %d is : %s\n",i,argv[i]);
    //}
    for (i=0;i<4;i++)
    printf("state %d is %s\n",i,state[i]);

    return 0;
}
