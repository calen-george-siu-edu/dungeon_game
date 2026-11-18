//Libaries
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Headers
#include "dungeon.h"
#include "player.h"

//Macro
#define BUFFERSIZE 100


static PlayerDecision getPlayerDecision();
static void playerEncounterMonster(Player* player, int monsterStrength);

void playerAction(Player* player, Room* room) {
    switch (room->type) {
        case MONSTER:
            playerEncounterMonster(player, room->value);
            break;
        case TREASURE:
            printf("You found a treasure worth %d coins!\n", room->value);
            player->coins += room->value;
            break;
        case EMPTY:
            printf("There's nothing here...\n");
            break;
    }
}

static void playerEncounterMonster(Player* player, int monsterStrength) {
    // Simple encounter mechanism
    
    printf("A monster appears! It has a strength of %d!\n", monsterStrength);

    PlayerDecision decision = getPlayerDecision();
    
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

static PlayerDecision getPlayerDecision() {
    printf("Would you like to fight or flee? (/stats to check your stats)\n");
    char buffer[BUFFERSIZE];
    while(fgets(buffer, BUFFERSIZE, stdin)){

        for(char* p = buffer; *p != '\0'; p++) {
            *p = tolower(*p); //Make lowercase
            if(*p == '\n') {
                *p = '\0'; //Get rid of \n at end of input
                break;
            }
        }
        if (strcmp(buffer, "fight") == 0) return FIGHT;
        else if(strcmp(buffer, "flee") == 0) return FLEE;
        else if (strcmp(buffer, "/stats") == 0) return VIEWSTATS;
        else printf("Unrecognized input. Accepted inputs are 'fight', 'flee', or '/stats'\n"); 
    }
    //On fail
    fprintf(stderr, "ERROR: Getting user input failed\n");
    exit(1);

}