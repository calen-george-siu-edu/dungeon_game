//Libaries
#include <stdio.h>

// Headers
#include "dungeon.h"
#include "player.h"

static void playerFightMonster(Player* player, int monsterStrength);

void playerAction(Player* player, Room* room) {
    switch (room->type) {
        case MONSTER:
            playerFightMonster(player, room->value);
            break;
        case TREASURE:
            printf("You found a treasure worth %d coins!\n", room->value);
            break;
        case EMPTY:
            printf("There's nothing here...\n");
            break;
    }
}

static void playerFightMonster(Player* player, int monsterStrength) {
    // Simple fight mechanism: if player's strength is higher, they win.
    printf("A monster appears! It has a strength of %d!\n", monsterStrength);
    if (player->strength >= monsterStrength) {
        printf("You defeated the monster!\n");
    } else {
        printf("The monster overpowers you. You flee back to the previous room.\n");
        player->health -= monsterStrength;
        if (player->health <= 0) {
            printf("You have died...\n");
            return;
        } else {
            printf("You survived the encounter, but you are wounded.\n");
        }
    }
}