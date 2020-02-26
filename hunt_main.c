#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hunt.h"

Treasure *myTreasures;
Room *theHouse;

int main(void){
	char* filename = "house.txt",*clue,search[20],*s;
	FILE* filefound = fopen(filename,"r");
	Room *copy;
	Clue *clues;
	myTreasures = NULL;
	if(filefound==NULL){
		printf("\n\tGAME FILE NOT FOUND!!\n");
		return 1;
	}
	fclose(filefound);
	clue = makeHouse(filename);
	copy = theHouse;
	printf("**************************** TREASURE HUNT ****************************\n");
	printf("\tWelcome to the most exciting Treasure Hunt in history!\n\n");
	printf("\tYou are now in the AUI campus as we speak...\n");
	printf("\tMORE PRECISELY, you are in the %s... Scary, isn't it?\n",theHouse->roomName);
	printf("\n\tThe first clue... is ..... %s!\n",clue);
	
	while(1){
			printf("\nDo you want to look in the %s",copy->roomName);
			while(copy->next!=NULL){
				copy = copy->next;
				printf(" or in the %s",copy->roomName);
			}
			copy = theHouse;
			printf("? ");
			scanf("%s",search);
			while(1){
				if(strcasecmp(copy->roomName,search)==0) break;
				copy = copy->next;	
				if(copy==NULL){
					copy = theHouse;
					printf("\tThere is no room called %s!\n",search);
					printf("\tSorry for the hassle, but TRY AGAIN IF YOU WANT TO WIN! ");
					scanf("%s",search);
					copy = theHouse;
				}
			}				
		printf("\nOOOOOH, now you're in the %s!\n",copy->roomName); 
		printf("\tNow we're looking for %s in %s! SOOOO EXCITING!\n",clue,copy->roomName);
		clues = copy->clues;
		s = checkRoom(clue,copy);
		copy->clues = clues;
		if(s==NULL) {
			printf("\tBAD NEWS!! %s was not found in %s!\n",clue,copy->roomName);
			copy = theHouse;
		}
		else if(strcmp(s,"Finished!")==0){
			strcpy(clue,s);
			printf("\tCongratulations, %s was found in %s!\n\n",clue,copy->roomName);
			printf("\n\tI have some good and sad news!\n");	
			printf("\nYou have won! We hope you liked your PRIZES!!!!\n");
			listTreasures();
			getchar();
			return 0;
		}
		else {
			printf("\tCongratulations, %s was found in %s!\n\n",clue,copy->roomName);
			strcpy(clue,s);		
			listTreasures();
			printf("\n\tYour next clue is .... %s!\n",clue);
			copy = theHouse;
		}	
	}

	return 0;
}

