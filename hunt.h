#include <stdio.h>

typedef struct r Room;
typedef struct c Clue;
typedef struct t Treasure;

struct r {
	char *roomName;
	Clue *clues;
	Treasure *treasures;
	Room *next;
};

struct c {
	char *clue;
	char *nextClue;
	Clue *next;
};

struct t {
	char *treasure;
	int value;
	Treasure *next;
};

extern Treasure *myTreasures;
extern Room *theHouse;

void listTreasures();

char* checkRoom(char *myClue, Room *room);

char* makeHouse(char *filename);

