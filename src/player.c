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

//Prototypes
static void playerEncounterMonster(Player* player, int monsterStrength);
static void getPlayerInput(const char* prompt, char* inputBuffer, size_t size);
static void fight();
static void flee();
static void stats();

//Functions
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
    

    char decision[BUFFERSIZE];
    getPlayerInput("Would you like to fight or flee? (/stats to check your stats)\n", decision, sizeof(decision));

    while(1){
        if (strcmp(decision, "fight") == 0){
            fight();
            break;
        }
        else if(strcmp(decision, "flee") == 0){
            flee();
            break;
        }
        else if (strcmp(decision, "/stats") == 0){
            stats();
            break;
        }
        else printf("Unrecognized input. Accepted inputs are 'fight', 'flee', or '/stats'\n"); 
    }








    }

}

static void fight(Player* player, int monsterStrength) {
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
            printf("Your health is now %d\n", player->health);
        }
    }
}

static void flee(Player* player, int monsterStrength){
    int cost = monsterStrength + (monsterStrength / 3);
    printf("The monster doesn't let you run for free, it will cost %d coins\n", cost);
    printf("Do you still want to flee?(y/n)\n");
}

static void stats(Player* player, int monsterStrength){
    printf("You are %s", player->name);
    printf("You have %d", player->)
}
static void getPlayerInput(const char* prompt, char* inputBuffer, size_t size){
    printf("%s", prompt);
    if (fgets(inputBuffer, size, stdin) == NULL){
        fprintf(stderr, "ERROR: Failed to get input\n");
        exit(1);
    }

    for(char* p = inputBuffer; *p != '\0'; p++) {
        *p = tolower(*p); //Make lowercase
        if(*p == '\n') {
            *p = '\0'; //Get rid of \n at end of input
            break;
        }
    }
    return;
}