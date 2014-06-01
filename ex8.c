/*************************************************************************
	> File Name: ex8.c
	> Author: Lixin Yao
    */
#include <stdio.h>
int main()
{
    char qqq[]={'a','v','q','\0'};
    int area[]={10,12,45};
    char name[]="yao";
    printf("size of int %ld\n",sizeof(int));
    printf("qqq is  %s\n",qqq);
    printf("size of long %ld\n",sizeof(long));

    printf("size of double %ld\n",sizeof(double));
    printf("size of area %ld\n",sizeof(area));
    printf("size of yao %ld\n",sizeof(name));
    printf("sizeof qqq %ld\n",sizeof(qqq));
    printf("the fist of area is %c\n",name[100]);
     

    return 0;
}
