#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXTREASURES 5
#define MAXROOMS 10
#define MAXEDGES 5
#define MAXLONGDESC 2

typedef struct {
	char name[10];
	int takescore;
	int depositscore;
	int taken;
	int alreadytaken; // So as to not keep on adding taken to myScore if the user takes and drops more than once
} Treasure;

typedef struct {
	char key[10];
	char target[10];
	int score;
	int visited; // So as to not keep on adding score to myScore if the user goes through the edge more than once
} Edge;

typedef struct {
	int score;
	int visited; // So as to not keep on adding score to myScore if the user comes to the room more than once
	char name[10];
	char shortdesc[40];
	char longdesc[MAXLONGDESC][400];
	Edge edges[MAXEDGES];
	Treasure treasures[MAXTREASURES];
} Room;

typedef struct {
	int numRooms;
	Room rooms[MAXROOMS];
} Adventure;

Treasure myTreasures[MAXTREASURES]; 
int myScore = 0;
int MAXSCORE = 0; // For the "out of MAXSCORE points"
Adventure Ad; // Global var for the adventure
Room *firstRoom; // First room to drop all myTreasures in it

//Load adventure from a text file
int loadAdventure(char* filename);
//Display myScore
void score(void);
//Look for an edge and return the destination
Room* findRoom(Room *cur,char* edge);
//Add a treasure to myTreasures if it is in the room
Treasure addTreasure(Room *cur,char* treasure);
//Drop a treasure in a room and add it to the treasures of that room
void drop(Room* theRoom,char* word);
//Display long description and treasures and myTreasures
void look(Room* theRoom);
//Add a treasure to myTreasures
void take(Room* theRoom,char* word);
//Display help message
void help(void);

int main(void){
	//To check if such a file exists
	int check = loadAdventure("adventure.txt");
	if(check == 0) return 0;
	char word[20];
	Room *theRoom = &Ad.rooms[0]; //Pointer to current room
	firstRoom = &Ad.rooms[0]; //Pointer to the first room
	
	printf("%s\n",theRoom->shortdesc);
	
	while(myScore<MAXSCORE){
		//Add room score to myScore only once
		if(theRoom->visited == 0){
			myScore+=theRoom->score;
			theRoom->visited = 1;
		}		
		fgets(word,19,stdin);
		word[strlen(word)-1] = '\0';
		
		  //If the input is Help
		if(strncasecmp(word,"Help",4)==0){
			help();
		} //If the input is Go
		else if(strncasecmp(word,"Go",2)==0){
			char where[10],junk[10];
			Room* lastroom = theRoom;
			sscanf(word,"%s %s",junk,where);
			theRoom = findRoom(theRoom,where);
			if(lastroom!=theRoom) printf("%s\n",theRoom->shortdesc);
		} //If the input is Look
		else if(strncasecmp(word,"Look",4)==0){
			look(theRoom);
		} //If the input is Take
		else if(strncasecmp(word,"Take",4)==0){
			take(theRoom,word);
			look(theRoom);
		} //If the input is Drop
		else if(strncasecmp(word,"Drop",4)==0){
			drop(theRoom,word);
			if(myScore<MAXSCORE) look(theRoom);
		} //If the input is Score
		else if(strncasecmp(word,"Score",5)==0) 
			score();
		  //If the input is Quit
		else if(strncasecmp(word,"Quit",4)==0) {
			printf("Oh, that's sad! ");
			score();
			return 0;
		} // If the input is not a valid one
		else printf("I don't know how to \"%s\".\n",word);
	}
	
	printf("Congratulations! ");
	score();
	return 0;
}

void score(void){
	printf("You have earned %d out of %d points.\n",myScore,MAXSCORE);
}

void help(void){
	printf("I will help you explore the world and find treasures. You must find all of the treasures and bring them back to the beginning. You can tell me instructions like \"go\", \"look\", \"take\", \"drop\", and \"score\".\n");
}

Treasure addTreasure(Room *cur,char* treasure) {
	for(int i=0;i<MAXTREASURES;i++){
		if(strcasecmp(cur->treasures[i].name,treasure)==0){
			if(cur->treasures[i].taken == 0){
				if(!cur->treasures[i].alreadytaken) myScore+=cur->treasures[i].takescore;
				cur->treasures[i].taken = 1; // Mark as taken
				cur->treasures[i].alreadytaken = 1; //Mark as already taken for the Drop 
			}
			return cur->treasures[i];
		}
	}
}

void take(Room* theRoom,char* word){
	int index = -1,r,checkif;
	char junk[10],treasure[10];
	sscanf(word,"%s %s",junk,treasure); 
	// Check if I already own this treasure or not
	for(checkif=0;strcasecmp(myTreasures[checkif].name,treasure)&& checkif<MAXTREASURES;checkif++); 
	if (checkif<MAXTREASURES)  printf("You already have a *%s*.\n",treasure);
	else {
		// Find first empty cell in myTreasures
		for(r=0;myTreasures[r].name[0]!='\0';r++);
		// Look for treasure in this room
		for(int i=0;i<MAXTREASURES && theRoom->treasures[i].name[0]!='\0';i++)
			if(!strcasecmp(theRoom->treasures[i].name,treasure))
				index = i;
		// If index does not change then it is not found, else add it to myTreasures
		if(index==-1) printf("There is no treasure called *%s*.\n",treasure);
		else myTreasures[r] = addTreasure(theRoom,treasure);
	}
}

Room* findRoom(Room *cur,char* edge) {
	char key[10];
	key[0]='\0';
	// Look through all edges in current room 
	for(int i=0;i<MAXEDGES;i++){
		// If edge is found
		if(strcasecmp(cur->edges[i].key,edge)==0){
			// Remember destination name
			strcpy(key,cur->edges[i].target);
			if(cur->edges[i].visited == 0){
				// Mark edge as visited and add it to myScore if it has never been visited
				myScore+=cur->edges[i].score;
				cur->edges[i].visited = 1;
			}
		}
	}
	if(key[0]=='\0') {
		// If edge is not found
		printf("I don't know how to go to \"%s\"\n",edge);
		return cur;
	}
	// If edge was found
	for(int i=0;i<MAXROOMS;i++) {
		// Return the address of the destination room
		if(strcasecmp(Ad.rooms[i].name,key)==0)
			return &Ad.rooms[i];
	}
	
}

void drop(Room* theRoom,char* word){
	char junk[10],treasure[10];
	int i;
	sscanf(word,"%s %s",junk,treasure); 
	// Look for the treasure in myTreasures
	for(i=0;strcasecmp(myTreasures[i].name,treasure)&&i<MAXTREASURES;i++);
	// If it is not found
	if(i == MAXTREASURES) printf("You have no treasure called *%s*.\n",treasure);
	// Else if the player is in the firstRoom
	else if(theRoom == firstRoom) {
		// Add the deposit score to myScore
		Treasure empty;
		myScore+= myTreasures[i].depositscore;
		myTreasures[i] = empty;
		myTreasures[i].name[0] = '\0';
	} 
	else {
		// If not in the firstRoom, add myTreasure to the Room and remove it from mine
		int j;
		Treasure empty;
		for(j=0;j<MAXTREASURES && theRoom->treasures[j].name[0]!='\0';j++);
		theRoom->treasures[j] = myTreasures[i]; 
		myTreasures[i] = empty;
		myTreasures[i].name[0] = '\0';
	} 
}

void look(Room* theRoom){
	// Function for printing
	int first1=0,first2=0; // Flags for "and a" in the printing
	int flag1=0,flag2=0; // Flags for the dots after myTreasures and the Treasures in the Room
	printf("%s ",theRoom->longdesc[0]);
	for(int i=0;i<MAXTREASURES && theRoom->treasures[i].name[0]!='\0';i++)
		if(!theRoom->treasures[i].taken){
			if(first1==0) {
				printf("You see a *%s* ",theRoom->treasures[i].name);		
				flag1 = 1;
				first1++;
			}
			else printf("and a *%s* ",theRoom->treasures[i].name);		
		}
	if(flag1==1) printf(".");
	for(int i=0;i<MAXTREASURES;i++)
		if(myTreasures[i].name[0]!='\0'){
			if(first2==0) {
				printf("You are holding a *%s* ",myTreasures[i].name);
				flag2 = 1;
				first2++;
			}
		else printf("and a *%s* ",myTreasures[i].name);
		}	
	if(flag2==1) printf(".");
	printf("\n");
}

int loadAdventure(char* filename){
	FILE* ptr = fopen(filename,"r");
	char word[400];
	int j,k,l;
	if(ptr == NULL) {
		printf("ERROR! <%s> not found!\n",filename);
		return 0;
	}
	fscanf(ptr,"%d\n",&Ad.numRooms);
	fgets(word,400,ptr);
	// READ ROOM DATA
	for(int i=0;i<Ad.numRooms;i++){
		// ROOM NAME
		sscanf(word,"%s %d",Ad.rooms[i].name,&Ad.rooms[i].score);
		Ad.rooms[i].visited = 0;
		MAXSCORE+=Ad.rooms[i].score;
		// SHORT DESCRIPTION
		fgets(word,400,ptr);
		word[strlen(word)-1] = '\0';
		strcpy(Ad.rooms[i].shortdesc,word);	
		// LONG DESCRIPTIONS
		fgets(word,400,ptr);
		j=0;
		while(word[0]!='('){
			word[strlen(word)-1] = '\0';
			strcpy(Ad.rooms[i].longdesc[j],word);
			fgets(word,400,ptr);
			j++;
		}
		// EDGES AND PATHS
		k=0;
		while(word[0]=='('){
			sscanf(word,"(%s %s %d",
				Ad.rooms[i].edges[k].key
				,Ad.rooms[i].edges[k].target,
				&Ad.rooms[i].edges[k].score);
			MAXSCORE+=Ad.rooms[i].edges[k].score;
			Ad.rooms[i].edges[k].key[strlen(Ad.rooms[i].edges[k].key)-1] = '\0';
			Ad.rooms[i].edges[k].visited = 0;
			fgets(word,400,ptr);
			k++;
		}
		// TREASURES
		l=0;
		while(word[0]=='*'){
			sscanf(word,"*%s %d %d",
				Ad.rooms[i].treasures[l].name,
				&Ad.rooms[i].treasures[l].takescore,
				&Ad.rooms[i].treasures[l].depositscore);
			MAXSCORE+=Ad.rooms[i].treasures[l].takescore;
			MAXSCORE+=Ad.rooms[i].treasures[l].depositscore;
			Ad.rooms[i].treasures[l].taken = 0;
			Ad.rooms[i].treasures[l].name[strlen(Ad.rooms[i].treasures[l].name)-1] = '\0';
			if(feof(ptr)) return 1;
			fgets(word,400,ptr);
			l++;
		}		
	}
	return 1;
}