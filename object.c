/*************************************************************************
	> File Name: object.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "object.h"

int Object_init(void* self)
{
    return 1;
}
void Object_describe(void* self)
{
    assert(self != NULL);
    Object* obj = self;
    assert(obj->description != NULL);
    printf("%s\n", obj->description);
}
void* Object_move(void* self, Direction direction)
{
    printf("you can not move that direction\n");
    return NULL;
}
void Object_destroy(void* self)
{
    assert(self != NULL);
    Object *obj = self;
    if(obj){
        if (obj->description) free(obj->description);
        free(obj);
    }
}
int Object_attack(void* self, int damage)
{
    printf("no attack\n");
    return 0;
}

void* Object_new(size_t size, Object proto, char* description)
{
    assert(description != NULL);
    assert(size > 0);
    if (!proto.init) proto.init=Object_init;
    if (!proto.describe) proto.describe=Object_describe;
    if (!proto.destroy) proto.destroy=Object_destroy;
    if (!proto.attack) proto.attack=Object_attack;
    if (!proto.move) proto.move=Object_move;
    Object* el=calloc(1, size);
    assert(el);
    *el= proto;
    el->description= strdup(description);
    if (!el->init(el))
    {
        el->destroy(el);
        return NULL;
    }
    else{
        assert(el);
        return el;
    }
}
