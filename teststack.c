/*************************************************************************
	> File Name: teststack.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <stdlib.h>
struct p{
    int a;
    char b;
};
struct p*  test()
{
    struct p q;
    struct p* qq;
    q.a=1;
    q.b='q';
    *qq=q;
    return qq; 
}
int main(){
    struct p* we=test();
    printf("%d %c\n",we->a, we->b);
    return 0;
}
