/*************************************************************************
	> File Name: ex9.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[])
{

    int numbers[4]={0};
    char name[4]="ya";
    printf("numbers: %d %d %d %d\n",numbers[0],numbers[1],numbers[2],numbers[3]);
    printf("name: %d %d %d %d\n",name[0],name[1],name[2],name[3]);
    printf("name is %s\n",name);
    numbers[0]=0;
    numbers[1]=1;
    numbers[2]=2;
    numbers[3]=3;
    name[0]='y';
    name[1]='a';
    name[2]='o';
    name[3]='a';
    printf("numbers: %d %d %d %d\n",numbers[0],numbers[1],numbers[2],numbers[3]);
    printf("name: %c %c %c %c\n",name[0],name[1],name[2],name[3]);
    printf("name is %s\n",name);
    char * another="yao";
    printf("name is %s\n",another);
    //printf("length is %d\n",strlen(another));
    printf("another each %c %c %c %c\n",another[0],another[1],another[2],another[3]);
    return 0;
}
