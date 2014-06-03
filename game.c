/*************************************************************************
	> File Name: game.c
	> Author: Lixin Yao
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "game.h"

int Monster_init(void* self)
{
        assert(self);
        Monster* monster=self;
        monster->hit_points=10;
        return 1;

}
int Monster_attack(void* self, int damage)
{
        assert(self);
        assert( damage > 0  );
        Monster* monster=self;
        printf("you attack%s!\n", monster->_(description));
        monster->hit_points-= damage;
    if (monster->hit_points > 0){
                printf("It's still alive\n");
                return 0;
            
    }
    else{
                printf("It's dead\n");
                return 1;
            
    }

}
Object MonsterProto={
        .init= Monster_init,
        .attack=Monster_attack

};

void* Room_move(void* self, Direction direction)
{
        assert(self);

        Room* room=self;
        Room* next=NULL;
    if (direction == NORTH && room->north){
                printf("you go north into:\n");
                next=room->north;
            
    }
    else if(direction == SOUTH && room->south){
                printf("you go south into:\n");
                next=room->south;
            
    }
    else if (direction == EAST && room->east){
                printf("you go east into:\n");
                next=room->east;
            
    }
    else if(direction == WEST && room->west){
                printf("you go west into:\n");
                next=room->west;
            
    }
    else{
                printf("you cannot go that direction\n");
            
    }
    if (next){
                next->_(describe)(next);
            
    }
        return next;

}
int Room_attack(void* self, int damage)
{
        assert(self);
        assert(damage > 0);
        Room* room=self;
        Monster* monster = room->bad_guy;
    if (monster){
                monster->_(attack)(monster, damage);
                return 1;
            
    }else{
                printf("no monster\n");
                return 0;
            
    }

}
Object RoomProto = {
        .move = Room_move,
        .attack = Room_attack

};
void* Map_move(void* self, Direction direction)
{
        assert(self);
        Map* map = self;
        Room* location=map->location;
        Room* next= NULL;
        next = location->_(move)(location, direction);
    if (next){
                map->location = next;
            
    }
        return next;

}
int Map_attack(void* self, int damage)
{
        assert(self);
        assert(damage > 0);
        Map* map=self;
        Room* location = map->location;
        return location->_(attack)(location, damage);

}

int Map_init(void* self)
{
        assert(self);
        Map* map= self;
        Room *hall = NEW(Room, "the great Hall");
        Room* throne = NEW(Room, "the throne room");
        Room* arena = NEW(Room, "the arena with the monster");
        Room* kitchen = NEW(Room, "Kitchen, you have the knife now");

        arena->bad_guy = NEW(Monster, "the evil minotaur");
        hall->north = throne;
        throne->west = arena;
        throne->east = kitchen;
        throne->south = hall;
        arena->east = throne;
        kitchen->west = throne;

        map->start = hall;
        map->location = hall;

        return 1;

}

Object MapProto = {
        .init = Map_init,
        .move = Map_move,
        .attack = Map_attack

};

