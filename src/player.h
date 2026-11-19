#ifndef PLAYER_H
#define PLAYER_H

#include "dungeon.h"
#include "dungeon.h"

typedef struct {
    char* name;
    int strength;
    int health;
    unsigned int coins;
} Player;

void playerAction(Player* player, Room* room);

#endif