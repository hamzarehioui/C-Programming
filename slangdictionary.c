#include<stdio.h>
#include<string.h>

void menu(void);
void display(int i);
void remove_dash(char*string);
void remove_spaces(char*string);
void search(char*query);
void list_all_words_withoutdef(void);
void list_all_words_withdef(void);
void add(char*newword);
void remove_return(char*string);

int main(void){
	char choice,c;
	char query[20],junk,newword[10];

	while(1){
	menu();
	scanf(" %c",&choice);
		switch(choice){
			case '1': printf("\n\t\tWhat word are you looking for? ");
					  scanf("%c",&junk);
					  fgets(query,19,stdin);
					  remove_return(query);
					  remove_spaces(query);
					  search(query);
				break;
			case '2': printf("\n\t\tWith (y) or without (n) definitions? ");
					  scanf(" %c",&c);
					  if(c=='n'||c=='N') list_all_words_withoutdef();
					  else if(c=='y'||c=='Y') list_all_words_withdef();
					  else printf("\n\t\tINVALID CHOICE!");
				break;
			case '3': printf("\n\t\tIt looks like you discovered a new slang word!");
					  printf("\n\t\tWhat is the new word? (MAX 20 CHARACTERS)");
					  scanf("%c",&junk);
					  fgets(newword,19,stdin);
					  remove_return(newword);
					  remove_spaces(newword);
					  add(newword);
				break;
			case '4': printf("\n\t\tGoodbye!");
					  return 0;
				break;
			default: printf("\n\t\tINVALID CHOICE!");
				break;
		}
	}
	
}

void menu(void){
	printf("\n\n\t\t**** SLANG  DICTIONARY ****");
	printf("\n\t\t[1] Search for a word .....");
	printf("\n\t\t[2] List all words ........");	
	printf("\n\t\t[3] Add a word ............");	
	printf("\n\t\t[4] Quit ..................");
	printf("\n\t\t... Please make a choice ...\n\t\t");
}
void search(char*query){
	FILE *dic=fopen("slangdictionary.txt","r");	
	char wordtodef[20],junk[300],definition[300],choice,j;
	while(!feof(dic)){
		fscanf(dic,"%s ",wordtodef);
		if(strcasecmp(wordtodef,query)==0) {
				remove_dash(wordtodef);
				printf("%s : \n",wordtodef);
				fgets(definition,299,dic);
				printf("%s",definition);
				fclose(dic);
				return;
			}
		fgets(junk,299,dic);
	}
	remove_dash(query);
	printf("\n\t\t%s not found in our slang!",query);
	printf("\n\t\tDo you know what %s means? (y) or (n)",query);
	scanf(" %c",&choice);
	remove_spaces(query);
	if(choice=='n'||choice=='N') {
		printf("\n\t\tI have some bad news, neither do I! ");
		fclose(dic);
	}
	else if(choice=='y'||choice=='Y') {
		scanf("%c",&j);
		add(query);
	}
	else printf("\n\t\tINVALID CHOICE!");
	fclose(dic);
}
void remove_spaces(char*string){
	for(int i=0;string[i]!='\0';i++){
		if(string[i]==' ') string[i]='-';
	}
}
void remove_dash(char*string){
	for(int i=0;string[i]!='\0';i++){
		if(string[i]=='-') string[i]=' ';
	}
}
void list_all_words_withdef(void){
	FILE *dic=fopen("slangdictionary.txt","r");	
	char wordtodef[20],junk[300],lastword[20];
	fscanf(dic,"%s\n",wordtodef);
	while(!feof(dic)){
		remove_dash(wordtodef);
		printf("%s :\n",wordtodef);
		fgets(junk,299,dic);
		printf("%s",junk);
		fscanf(dic,"%s\n",wordtodef);
		if(feof(dic)){
			fclose(dic);
			return;
		}
	}

	fclose(dic);
}
void list_all_words_withoutdef(void){
	FILE *dic=fopen("slangdictionary.txt","r");	
	char wordtodef[20],junk[300],lastword[20];
	fscanf(dic,"%s\n",wordtodef);
	while(!feof(dic)){
		remove_dash(wordtodef);
		printf("- %s \n",wordtodef);
		fgets(junk,299,dic);
		fscanf(dic,"%s\n",wordtodef);
		if(feof(dic)){
			fclose(dic);
			return;
		}
	}

	fclose(dic);
}
void add(char*newword){
	FILE *dic=fopen("slangdictionary.txt","a");	
	char junk[300],definition[300];
	
	fprintf(dic,"\n%s ",newword);
	remove_dash(newword);
	printf("\n\t\tWhat is the definition of %s? (MAX 300 CHARACTERS)",newword);
	fgets(definition,299,stdin);
	fprintf(dic,"%s",definition);
	fclose(dic);
}
void remove_return(char*string){
	for(int i=0;string[i]!='\0';i++){
		if(string[i]=='\n') {
			string[i]='\0';
			return;
		}
	}
}