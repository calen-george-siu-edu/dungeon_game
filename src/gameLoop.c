#include <stdio.h>
#include "dungeon.h"
#include "player.h"
#include "gameLoop.h"

void gameLoop(Player* player, Room *dungeonHead) {
    Room *currentRoom = dungeonHead;
    int roomIndex = 0;
    while (currentRoom != NULL && player->health > 0) {
        printf("You are in room %d.\n", roomIndex + 1);
        displayRoom(currentRoom);
        playerAction(player, currentRoom);
        if (player->health <= 0) {
            printf("%s has fallen in battle...\n", player->name);
            break;
        }
        currentRoom = currentRoom->next;
        roomIndex++;
    }
    if (player->health > 0) {
        printf("Congratulations, %s! You've cleared the dungeon!\n", player->name);
    }
}