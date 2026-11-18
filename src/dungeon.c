//Libraries
#include <stdio.h>
#include <stdlib.h>

//Headers
#include "dungeon.h"

//Prototypes
static Room* createRoom(int index);


static Room* createRoom(int index) {
    Room *room = malloc(sizeof(Room));
    room->type = rand() % 3; // Randomly assign room type
    // Randomly assign room value based on room type 
    // (10-60 for coins treasure, 10-50 strength for monster)
    int min_strength = (index + 1) * 5;
    int max_strength = min_strength * 2; //randoom
    int money = (index + 1) * 5;
    room->value = (room->type == MONSTER) 
                ? (rand() % (max_strength - min_strength + 1)) //uses a different method  to ensure that the the minimum and max stength increases linearly with the depth
                : (rand() % money);//makes it so that as the depth increases, the more treasure there will be in the room
    room->next = NULL;
    return room;
}

Room* createDungeon(int numRooms) {
    Room *head = NULL, *current = NULL;
    for(int i = 0; i < numRooms; ++i) {
        if (i == 0) {
            head = current = createRoom(i);
        } else {
            current->next = createRoom(i);
            current = current->next;
        }
    }
    return head;
}

void deleteDungeon(Room *dungeon) {
    while (dungeon != NULL) {
        Room *temp = dungeon;
        dungeon = dungeon->next;
        free(temp);
    }
}

void displayRoom(const Room* room) {
    const char* roomType = room->type == EMPTY ? "an empty room"
                             : room->type == MONSTER ? "a room with a monster"
                             : "a room with treasure";
    printf("You enter %s.\n", roomType);
}