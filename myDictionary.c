#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mult;
int numberofwords;

typedef struct{
	char word[20];
	char definition[500];
} Word;

Word *myHashTable = NULL; 

void lowercase(char* str){
	int i;
    for(i=0; str[i]!='\0'; i++){
        if(str[i]>='A' && str[i]<='Z'){
            str[i] = str[i] + 32;
        }
    }
}

int hash(char* word){
	unsigned key = 0;
	int SIZE=numberofwords*mult;
	lowercase(word);
	for (key = 0; *word != '\0'; word++)
        key = *word + 41*key;

	return key%SIZE;
}

int menu(void);
void search(char *lookup);

int main(void){
	Word temp; 
	int collisions = 0;
	char lookup[20];
	FILE* fp=fopen("dictionary.bin","rb");

	fread(&numberofwords,sizeof(int),1,fp);

	printf("This dictionary contains %d words!\n",numberofwords);
	printf("The multiplier is the value that we multiply by the number of words to define the size of the table.\n");
	printf("For example, if you define the multiplier as 2, then we will allocate %d cells for the dictionary!\n",2*numberofwords);
	printf("What multiplier would you like to use for the Hash Table? ");
	scanf("%d",&mult);
	while(mult<1){
		printf("ERROR! The multiplier has to be a positive integer!! ");
		scanf("%d",&mult);
	}

	// Allocate Numberofwords*Multiplier cells for the HashTable
	myHashTable = (Word*) malloc(numberofwords*mult*sizeof(Word));

	// Initialize all cells to nullifying character
	for(int i=0;i<numberofwords*mult;i++){
		myHashTable[i].definition[0] = '\0';
		myHashTable[i].word[0] = '\0';
	}

	// Read words from the binary file
	for(int i=0;i<numberofwords;i++){
		fread(&temp,sizeof(Word),1,fp);
		int n = hash(temp.word);
		// If nth cell is empty then fill it
		if(myHashTable[n].word[0] == '\0') myHashTable[n] = temp;
		else {
			collisions++; // Increment collisions counter
			int j; 
			// Find next empty cell
			for(j=n;myHashTable[j].word[0] != '\0' && j<numberofwords*mult;j++);
			// If empty cell was not found, restart at the beginning of the array, else fill it
			if(j == numberofwords*mult) {
				j=0;
				for(;myHashTable[j].word[0] != '\0' && j<n;j++);
				if(j<n) myHashTable[j] = temp;
				else printf("- %s cannot be inserted!\n",temp.word);
			}
			else myHashTable[j] = temp;
		}
	}

	// Close binary file
	fclose(fp);

	printf("Your Hash Table with a multiplier %d had %d collisions.\n",mult,collisions);

	int flag = menu();

	while(1){
		switch(flag){
			case 1:		// Display ALL words with definitions
				for(int i=0;i<numberofwords*mult;i++)
					if(myHashTable[i].word[0]!='\0')
						printf("(Index: %d- HashIndex: %d)\n%s - Definition: %s\n",i,hash(myHashTable[i].word),myHashTable[i].word,myHashTable[i].definition);
				break;
			case 2: 	// Display ALL words without definitions
				for(int i=0;i<numberofwords*mult;i++)
					if(myHashTable[i].word[0]!='\0')
						printf("(Index: %d- HashIndex: %d) %s\n",i,hash(myHashTable[i].word),myHashTable[i].word);
				break;
			case 3: 	// Look up a word
				printf("What word are you looking for? ");
				scanf("%s",lookup);
				search(lookup);
				break;
			case 4:		printf("Goodbye!\n");
				return 0;
				break;
			default:	printf("This command does not exist!\n");
				break;
		}
		flag = menu();
	}

	return 0;
}

void search(char *lookup){
	int n = hash(lookup);
	int time = 0,i;
	
	// Use the hash first
	if(strcasecmp(lookup,myHashTable[n].word)==0) {
		printf("%s - Def: %s\n",myHashTable[n].word,myHashTable[n].definition);
		printf("Found in %d time!\n",time);
		return;
	}

	// If it is not found, look through all following values
	for(i=n+1;i<numberofwords*mult;i++){
		time++;
		if(strcasecmp(lookup,myHashTable[i].word)==0) {
			printf("%s - Def: %s\n",myHashTable[i].word,myHashTable[i].definition);
			printf("Found in %d time!\n",time);
			return;
		}
		if(myHashTable[i].word[0]=='\0') {
			printf("Word not found!\n");
			return; //If blank space found, stop because word would not be found
		}
	}

	//If it is still not found, restart the array until n and look for it
	for(i=0;i<n;i++){
		time++;
		if(strcasecmp(lookup,myHashTable[i].word)==0) {
			printf("%s - Def: %s\n",myHashTable[i].word,myHashTable[i].definition);
			printf("Found in %d time!\n",time);
			return;
		}
		if(myHashTable[i].word[0]=='\0') {
			printf("Word not found!\n");
			return; //If blank space found, stop because word would not be found
		}
	}

	printf("Word not found!\n");
}

int menu(void){
	int n;
	printf("\n");
	printf("Here are the actions you can take: \n");
	printf("(1) Display all words and their definitions \n");
	printf("(2) Display all words without their definitions \n");
	printf("(3) Look up a word and time complexity \n");
	printf("(4) Quit \n");
	printf("Your option is: ");
	scanf("%d",&n);
	printf("\n");
	return n;
}
