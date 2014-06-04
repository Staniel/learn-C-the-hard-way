/*************************************************************************
	> File Name: ex24.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include "dbg.h"
#include <stdlib.h>
#include <ctype.h>
#define MAX_DATA 100

typedef enum EyeColor{
    BLUE, GREEN, BROWN, BLACK, OTHER
} EyeColor;
const char* EYE_COLOR_NAMES[]={
    "Blue", "Green", "Brown", "Black", "Other"
};
typedef struct Person{
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
}Person;

void trim_get(char* str)
{
    char ch;
    while ( (ch = getchar()) && isspace(ch) );
    ungetc(ch, stdin);
    char* in = fgets(str, MAX_DATA, stdin);
    if (!in)
    {
        printf("fail to read line\n");
        exit(1);
    }
    int end = strlen(str)-1;
    while ( isspace(str[end]) ) end--;
    str[end+1]='\0';
}
int main()
{
    Person you = {.age = 0};
    int i;
    char* in = NULL;
    int rc;
    char* value=malloc(MAX_DATA);
    memset(value, '\0', MAX_DATA);

    printf("What's your first name? ");
    trim_get(you.first_name);
    printf("what's your last name?");
    trim_get(you.last_name);
// use fgets and atoi to read number
    printf("how old r u\n");
    in = fgets(value,MAX_DATA-1, stdin );
    you.age = atoi(value);
    check( in!=NULL, "fail to read age" );
    check( you.age > 0, "age should be positive" );

    printf("what color ar your eye?\n");
    for (i=0;i <= OTHER; i++)
    {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");
    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "you have to enter a number");
    you.eyes = eyes-1;
    check(you.eyes <= OTHER && you.eyes >= 0, "wrong");
    printf("money?\n");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "enter a float");

    printf("---result---\n");
    printf("first name:%s\n", you.first_name);
    printf("laste name:%s\n", you.last_name);
    printf("age:%d\n", you.age);
    printf("eyes:%s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("income:%f\n", you.income);
    return 0;
error:
    return -1;

}
