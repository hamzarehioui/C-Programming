#include <stdio.h>
#include <string.h>
//THIS IS AN ALUMNI MANAGEMENT DATABASE
void menu(void);
void display(void);
void displaystudents(void);
int search(char*);
struct alumnus{
	char* name;
	char* phone;
	char* email;
	char* address;
	int visit;
};
struct student{
	char* name;
	char* phone;
	char* email;
	char* address;
};

// Let's say AUI only has 4 alumni already in the database to simplify the code
// This is the dataset of alumni at the moment

struct alumnus ex_aui[50]={
	{"John","111","john@aui.ma","MA",1},
	{"Amy","222","amy@aui.ma","US",3},
	{"Jimmy","333","jimmy@aui.ma","GR",0},
	{"Clark","444","clark@aui.ma","NE",7}};
	
// Let's say AUI only has 2 current students in the database to simplify the code
// This is the dataset of current students

struct student aui[50]={
	{"Ron","666","ron@aui.ma","MA"},
	{"Bobby","999","bobby@aui.ma","US"}};

int cntalumnus=4;
int cntstudents=2;

int main() {
	int choice=0;
	char s[10];
	int c;

	while(1){
		menu();
		printf("\n\t\t");
		scanf("%d",&choice);
		switch (choice){
			case 1: display();
				break;
			case 2: printf("\n\t\tWhat is the name? ");
					scanf(" %s",s);
					c=search(s);
					if(c==-1)printf("\n\t\tThere is no alumnus named %s.",s);
					else{
						printf("\n\t\tName : %s",ex_aui[c].name);
						printf("\n\t\tPhone : %s",ex_aui[c].phone);
						printf("\n\t\tAddress : %s",ex_aui[c].address);
						printf("\n\t\tEmail : %s",ex_aui[c].email);	
						printf("\n\t\tVisits after grad : %d",ex_aui[c].visit);		
						printf("\n\t\t.............................");			
					}
				break;
			case 3:	printf("\n\t\tHere are the current students: \n");
					displaystudents();
					printf("\n\t\tWhat is the name? ");
					scanf(" %s",s);
					c=searchstudents(s);
					if(c==-1) printf("\n\t\tThere is no student named %s.",s);
					else {
						cntalumnus++; cntstudents--;
						ex_aui[cntalumnus-1].name=aui[c].name;
						ex_aui[cntalumnus-1].address=aui[c].address;
						ex_aui[cntalumnus-1].email=aui[c].email;
						ex_aui[cntalumnus-1].phone=aui[c].phone;
						aui[c].name[0]=='\0';
						aui[c].address[0]=='\0';
						aui[c].email[0]=='\0';
						aui[c].phone[0]=='\0';				
						printf("\n\t\tSuccessful update!");
					}		
				break;
			case 4:	printf("\n\t\tWhat is the name? ");
					scanf(" %s",s);
					if(search(s)==-1) printf("\n\t\tThere is no alumnus named %s.",s);
					else {
						ex_aui[search(s)].visit++;	
						printf("\n\t\tSuccessful update!");
					}		
				break;
			case 5: printf("\n\t\tHave a good day!\n\n");
					return 0;
				break;
			default: printf("\n\t\tINVALID!");
		}
	}
}

//BELOW ARE THE FUNCTIONS' DEFINITIONS

void menu(void){
	printf("\n\n\t\t**** Alumni Contact List ****");
	printf("\n\t\t[1] Display all the alumni ..");
	printf("\n\t\t[2] Search ..................");	
	printf("\n\t\t[3] Add an alumnus ..........");
	printf("\n\t\t[4] Update visits ...........");	
	printf("\n\t\t[5] Quit ....................");
	printf("\n\t\t... Please make a choice  ...\n");
}

void display(void){
	int i;
	for(i=0;i<cntalumnus;i++){
		printf("\n\t\tName : %s",ex_aui[i].name);
		printf("\n\t\tPhone : %s",ex_aui[i].phone);
		printf("\n\t\tAddress : %s",ex_aui[i].address);
		printf("\n\t\tEmail : %s",ex_aui[i].email);	
		printf("\n\t\tVisits after grad : %d",ex_aui[i].visit);		
		printf("\n\t\t.............................");
	}
}

int search(char*s){
	int i;
	for(i=0;i<cntalumnus;i++){
		if(strcasecmp(s,ex_aui[i].name)==0) return i;
	}
	return -1;
}

void displaystudents(void){
	int i;
	for(i=0;i<cntstudents;i++){
		printf("\n\t\tName : %s",aui[i].name);
		printf("\n\t\tPhone : %s",aui[i].phone);
		printf("\n\t\tAddress : %s",aui[i].address);
		printf("\n\t\tEmail : %s",aui[i].email);			
		printf("\n\t\t.............................");
	}
}

int searchstudents(char*s){
	int i;
	for(i=0;i<cntstudents;i++){
		if(strcasecmp(s,aui[i].name)==0) return i;
	}
	return -1;
}