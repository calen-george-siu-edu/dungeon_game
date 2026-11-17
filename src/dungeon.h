#ifndef DUNGEON_H
#define DUNGEON_H

// Enumerations
typedef enum { EMPTY, MONSTER, TREASURE } RoomType;

// Structures
typedef struct Room {
    RoomType type;
    int value;
    struct Room *next;
} Room;

//Function prototypes
Room* createRoom(int index);
Room* createDungeon(int numRooms);
void deleteDungeon(Room *dungeon);
void displayRoom(const Room* room);

#endif