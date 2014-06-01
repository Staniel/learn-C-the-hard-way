/*************************************************************************
	> File Name: ex15.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <stdlib.h>
void p1(int* a, char** b,int count)
{
    int i;
    for (i=0;i<count;i++)
    {
        printf("%s has %d years old\n",*(b+i),*(a+i));
    }
    printf("---------------\n");
}
void p2(int* a, char** b,int count)
{
    int i;
    for (i=0;i<count;i++)
    {
        printf("%s has %d years old\n",b[i],a[i]);
    }
    printf("---------------\n");
}

int main(int argc, char* argv[])
{
    int i;
    char** ptr=argv;
    for (i=0;i<argc;i++)
    printf("%d arg is %s\n",i,*(ptr+i));
    //int *ages={23,43,12,89,2};
    int *ages= (int*) malloc(sizeof(int)*5);
    *ages=23;*(ages+1)=43;ages[2]=12;ages[3]=89;ages[4]=2;
    char* names[]={
        "abcdefgh","frank","mary","john"
        ,"lisa"
    };
    int count=sizeof(ages)/sizeof(int);
    count=5;
    for (i=0;i<count;i++)
    printf("%s has %d years life\n",names[i],ages[i]);
    printf("---------\n");
    int * cur_age=ages;
    char **cur_name=names;
    /*
    printf("cur_name is %p\n",cur_name);
    printf("cur_name+1 is %p\n",cur_name+1);
    printf("*cur_name is %p\n",*cur_name);
    printf("cur_age is %p\n",cur_age);
    printf("cur_age+1 is %p\n",cur_age+1);
*/
    // question about cur_name, why not move the char position?
   /*
    for (i=0;i<count;i++)
    {
        printf("%s has %d years old\n",cur_name[i],cur_age[i]);
    }*/
    printf("---------------\n");
    while(cur_age<(ages+count))
    {
        
        printf("%s has %d years old\n",*cur_name,*cur_age);
        cur_name++;
        cur_age++;
    }
    
   // p1(cur_age,cur_name,count);
   // p2(cur_age,cur_name,count);
    return 0;
}
