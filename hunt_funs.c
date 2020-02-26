#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hunt.h"

extern Treasure *myTreasures;
extern Room *theHouse;

char* makeHouse(char *filename){
	FILE* fp = fopen(filename,"r");
	Room *first=NULL,*myHouse=NULL;
	char *s = (char*) malloc(20);
	Clue *firstclueptr = NULL;
	Treasure *firsttreasureptr = NULL;

	fscanf(fp,"%s",s);
	if(myHouse==NULL) first = myHouse = (Room*) malloc(sizeof(Room));
	while(!feof(fp)){
		firstclueptr = NULL;
		firsttreasureptr = NULL;
		myHouse->roomName = (char*) malloc(strlen(s)+1);
		strcpy(myHouse->roomName,s);
		fscanf(fp,"%s",s);
		myHouse->clues = (Clue*) malloc(sizeof(Clue));
		while(strcmp(s,"done")){
			myHouse->clues->clue = (char*) malloc(strlen(s)+1);
			strcpy(myHouse->clues->clue,s);
			fscanf(fp,"%s",s);
			myHouse->clues->nextClue = (char*) malloc(strlen(s)+1);
			strcpy(myHouse->clues->nextClue,s);
			if(firstclueptr==NULL){
				firstclueptr = myHouse->clues;
			}
			myHouse->clues->next = (Clue*) malloc(sizeof(Clue));
			myHouse->clues = myHouse->clues->next;
			fscanf(fp,"%s",s);
		}
		myHouse->clues->next = NULL;
		myHouse->clues = firstclueptr;
		fscanf(fp,"%s",s);
		myHouse->treasures = (Treasure*) malloc(sizeof(Treasure));	
		while(strcmp(s,"done")){
			myHouse->treasures->treasure = (char*) malloc(strlen(s)+1);
			strcpy(myHouse->treasures->treasure,s);
			fscanf(fp,"%d",&myHouse->treasures->value);
			if(firsttreasureptr	==NULL){
				firsttreasureptr = myHouse->treasures;
			}
			myHouse->treasures->next = (Treasure*) malloc(sizeof(Treasure));
			myHouse->treasures = myHouse->treasures->next;
			fscanf(fp,"%s",s);
		}
		myHouse->treasures->next = NULL;
		myHouse->treasures = firsttreasureptr;
		fscanf(fp,"%s",s);
		myHouse->next = (Room*) malloc(sizeof(Room));
		if(strcmp(s,"done")){
			myHouse = myHouse->next;
		} else {
			myHouse->next = NULL;
			theHouse = first;
			fscanf(fp,"%s",s);
			return s;
		}
	}

}

void addTreasure(Treasure *treasure){
	Treasure *treasurecopy = NULL;
	
	if(myTreasures == NULL){
	    myTreasures = (Treasure*) malloc(sizeof(Treasure));
	    myTreasures->treasure = treasure->treasure;
	    myTreasures->value = treasure->value;
	    return;
	}
	
	treasurecopy = myTreasures;
	while(treasurecopy->next != NULL) treasurecopy = treasurecopy->next;
	treasurecopy->next = (Treasure*) malloc(sizeof(Treasure));
	treasurecopy->next->treasure = treasure->treasure;
	treasurecopy->next->value = treasure->value;
	treasurecopy->next->next = NULL;
	
}

char *checkRoom(char *myClue, Room *room){
	Room *copy = room;
	char *s = (char*)malloc(20);
	Treasure *first = room->treasures;
	

	while(copy->clues->next!=NULL){
		if(strcasecmp(copy->clues->clue,myClue)==0) {
			s = copy->clues->nextClue;
			addTreasure(first);
			return s;
		}
		copy->clues = copy->clues->next;
		first = first->next;	
	}
	return NULL;
}

void listTreasures(){
	Treasure *head = myTreasures;
	
	printf("\tHERE ARE THE TREASURES THAT YOU HAVE EARNED THIS FAR: \n");	
	for(;myTreasures!=NULL;myTreasures = myTreasures->next){
		if(myTreasures->value!=0) printf("\t\t+ %s with a value of %d DHS!\n",myTreasures->treasure,myTreasures->value);
		else printf("\t\t+ You got a(n) %s!\n",myTreasures->treasure);
	}
	myTreasures = head;
}
