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
    room->value = (room->type == MONSTER) ? (rand() % 5 + 1) * 10 : (rand() % 50 + 10);
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