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
static void fight(Player* player, int monsterStrength);
static void flee(Player* player, int monsterStrength);
static void stats(Player* player, int monsterStrength);

//Functions
void playerAction(Player* player, Room* room) {
    switch (room->type) {
        case MONSTER:
            printf("A monster appears! It has a strength of %d!\n", room->value);
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
    
    char decision[BUFFERSIZE];
    getPlayerInput("Would you like to fight or flee? (/stats to check your stats)\n", decision, sizeof(decision));

    if (strcmp(decision, "fight") == 0) fight(player, monsterStrength);
    else if(strcmp(decision, "flee") == 0) flee(player, monsterStrength);
    else if (strcmp(decision, "/stats") == 0) stats(player, monsterStrength);
    else {
        printf("Unrecognized input.\n");
        playerEncounterMonster(player,monsterStrength);
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
    char decision[BUFFERSIZE];
    int cost = monsterStrength + (monsterStrength / 3); //1.33 * monsterstrength
    printf("The monster doesn't let you run for free, it will cost %d coins\n", cost);
    getPlayerInput("Do you still want to flee?(y/n)\n", decision, sizeof(decision));
    if(strcmp(decision, "y") == 0) {
        if( (int) player->coins >= cost){
            player->coins -= cost;
            printf("The monster accepted your payment, you now have %d coins\n", player->coins);
        } else {
            printf("Dude ur broke asf, you gotta fight the monster:(\n");
            fight(player,monsterStrength);
        }
    } else if (strcmp(decision, "n") == 0) {
        playerEncounterMonster(player,monsterStrength);
    } else {
        printf("Unrecognized input, try again\n");
        flee(player,monsterStrength);
    }
}

static void stats(Player* player, int monsterStrength){
    printf("-You are %s\n", player->name);
    printf("-You have %d hp\n", player->health);
    printf("-You have level %d strength\n", player->strength);
    printf("-You have %d coins\n", player->coins);
    playerEncounterMonster(player, monsterStrength);
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