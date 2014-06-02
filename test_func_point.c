/*************************************************************************
	> File Name: test_func_point.c
	> Author: Lixin Yao
    */
#include <stdio.h>

typedef void (*func)();
void dos()
{
    printf("hello\n");
}
int main()
{
   // func x;
   // x=&dos;
    // the dos and &dos are the same
    printf("%p\t%p\n", dos, &dos);
    //x();
}
