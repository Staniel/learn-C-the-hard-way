/*************************************************************************
	> File Name: ex19.c
	> Author: Lixin Yao
    */
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include "game.h"
extern Object MapProto;
extern Object RoomProto;
extern Object MonsterProto;

int process_input(Map* game)
{
    assert(game);
    printf("\n> ");
    char ch= getchar();
    getchar();
    int damage = rand() % 4;
    switch(ch){
        case -1:
        printf("you loser\n");
        return 0;
        break;
        case 'n':
        game->_(move)(game, NORTH);
        break;
        case 's':
        game->_(move)(game, SOUTH);
        break;
        case 'e':
        game->_(move)(game, EAST);
        break;
        case 'w':
        game->_(move)(game, WEST);
        break;
        case 'a':
        game->_(attack)(game, damage);
        break;
        case 'l':
        printf("you can go:\n");
        if (game->location->north) printf("NORTH\n");
        if (game->location->south) printf("SOUTH\n");
        if (game->location->east) printf("EAST\n");
        if (game->location->west) printf("WEST\n");
        break;
        default:
        printf("what?\n");
    }
    return 1;
}

int main()
{
    srand(time(NULL));
    Map* game=NEW(Map, "the hall of the Minotaur");
    printf("you enter the ");
    game->location->_(describe)(game->location);
    while(process_input(game));
    return 0;
}
