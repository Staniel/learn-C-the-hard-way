/*************************************************************************
	> File Name: ex16.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person{
    char* name;
    int age;
    int height;
    int weight;
} ;

struct Person Person_create(char* name, int age, int height, int weight)
{
    struct Person who;
    
    who.name=strdup(name);
    who.age=age;
    who.height=height;
    who.weight=weight;
    return who;
}
/*
void Person_destroy(struct Person* who)
{
    assert(who!=NULL);
    free(who->name);
    free(who);
}
*/
void Person_print(struct Person  who)
{
    printf("name: %s\nage: %d\nHeight: %d\nweight: %d\n",
          who.name,
           who.age,
           who.height,
           who.weight
          );
}
int main(int argc,char* argv[])
{
    struct Person joe=Person_create("joe Alex",32,64,140);
    struct Person frank=Person_create("Frank Underwood",20,72,180);
    printf("joe is at memory %p\n",&joe);
    Person_print(joe);
    printf("francis is at memory %p\n",&frank);
    Person_print(frank);
    joe.age+=20;
    Person_print(joe);
    //Person_print(NULL);

  //  Person_destroy(joe);
  //  Person_destroy(frank);
 //   Person_destroy(NULL);

    return 0;
}
