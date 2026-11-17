// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Headers
#include "dungeon.h"
#include "player.h"
#include "gameLoop.h"


// Function Prototypes
void playGame(int numRooms);

// Main Function
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_rooms>\n", argv[0]);
        return 1;
    }

    int numRooms = atoi(argv[1]);
    if (numRooms <= 0) {
        printf("Number of rooms should be a positive integer.\n");
        return 1;
    }

    playGame(numRooms);

    return 0;
}

void playGame(int numRooms) {
    srand((unsigned int)time(NULL)); // Seed the random number generator

    Room *dungeonHead = createDungeon(numRooms); // Create the dungeon

    Player player = {"Adventurer", 20, 100}; // Create a player with 20 strength and 100 health

    gameLoop(&player, dungeonHead); // Start the game loop

    deleteDungeon(dungeonHead); // Cleanup
}




