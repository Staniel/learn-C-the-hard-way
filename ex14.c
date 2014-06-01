/*************************************************************************
	> File Name: ex14.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
int can_print_it(char ch);
void print_letters(char arg[]);

void print_argument(int argc, char* argv[])
{
    int i=0;
    for (i=0;i<argc;i++)
        print_letters(argv[i]);
}
void print_letters(char arg[])
{
    int i;
    int length=strlen(arg);
    for (i=0;i<length;i++)
    {
        char ch=arg[i];
        if (isalpha(ch)|| isblank(ch))
            printf("%c = %d\t",ch,ch);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    print_argument(argc,argv);
    return 0;
}
