#include <stdio.h>
#include <string.h>
//THIS IS AN ALUMNI MANAGEMENT DATABASE

struct alumnus{
	char name[20];
	char phone[20];
	char email[20];
	char address[20];
	int visit;
};
struct student{
	char name[20];
	char phone[20];
	char email[20];
	char address[20];
};

// Let's say AUI only has 4 alumni already in the database to simplify the code
// This is the dataset of alumni at the moment

struct alumnus ex_aui[50]={
	{"John John","111","john@aui.ma","MA",1},
	{"Amy Amy","222","amy@aui.ma","US",3},
	{"Jimmy Jimmy","333","jimmy@aui.ma","GR",0},
	{"Clark Clark","444","clark@aui.ma","NE",7}};
	
// Let's say AUI only has 2 current students in the database to simplify the code

// This is the dataset of current students

struct student aui[50]={
	{"Ron Ron","666","ron@aui.ma","MA"},
	{"Bobby Bobby","999","bobby@aui.ma","US"}};

void savestudents(void){
	FILE* fw=fopen("students.bin","wb");

	fwrite(ex_aui,sizeof(struct alumnus),50,fw);
	fclose(fw);
}

void savealumni(void){
	FILE* fw=fopen("alumni.bin","wb");

	fwrite(aui,sizeof(struct student),50,fw);
	fclose(fw);
}

int fillstudents_and_alumni(void){
	FILE* fr1=fopen("students.bin","rb");
	FILE* fr2=fopen("alumni.bin","rb");
	if(fr1==NULL||fr2==NULL) return 0;
	fread(ex_aui,sizeof(struct alumnus),50,fr1);
	fread(aui,sizeof(struct alumnus),50,fr2);
	fclose(fr1);
	fclose(fr2);
	return 1;
}

void menu(void);
void display(void);
void displaystudents(void);
int search(char*);
int searchstudents(char*s);
void remove_return(char*string);

int main(void) {
	int i;
	char s[10];
	int c;
	char choice;

	fillstudents_and_alumni();
	if(fillstudents_and_alumni()==0){
		savestudents();
		savealumni();
	}


	while(1){
		menu();
		printf("\n\t\t");
		scanf(" %c",&choice);
		switch (choice){
			case '1': display();
				break;
			case '2': printf("\n\t\tWhat is the name? ");
					getchar();
					fgets(s,19,stdin);
					remove_return(s);
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
			case '3':	printf("\n\t\tHere are the current students: \n");
					displaystudents();
					printf("\n\t\tWhat is the name? ");
					getchar();
					fgets(s,19,stdin);
					remove_return(s);
					c=searchstudents(s);
					if(c==-1) printf("\n\t\tThere is no student named %s.",s);
					else {
						for(i=0;ex_aui[i].name[0]!='\0';i++);
						strcpy(ex_aui[i].name,aui[c].name);
						strcpy(ex_aui[i].address,aui[c].address);
						strcpy(ex_aui[i].email,aui[c].email);
						strcpy(ex_aui[i].phone,aui[c].phone);
						aui[c].name[0]='\0';
						aui[c].address[0]='\0';
						aui[c].email[0]='\0';
						aui[c].phone[0]='\0';				
						printf("\n\t\tSuccessful update!");
						savealumni();
					}		
				break;
			case '4':	printf("\n\t\tWhat is the name? ");
					getchar();
					fgets(s,19,stdin);
					remove_return(s);
					if(search(s)==-1) printf("\n\t\tThere is no alumnus named %s.",s);
					else {
						ex_aui[search(s)].visit++;
						savealumni();
						printf("\n\t\tSuccessful update!");
					}		
				break;
			case '5': printf("\n\t\tAdd a student !\n\n");
					for(i=0;aui[i].name[0]!='\0';i++);
					printf("\n\t\tName : ");
					getchar();
					fgets(aui[i].name,19,stdin);
					remove_return(aui[i].name);
					printf("\n\t\tPhone : ");
					fgets(aui[i].phone,19,stdin);
					remove_return(aui[i].phone);
					printf("\n\t\tAddress : ");
					fgets(aui[i].address,19,stdin);
					remove_return(aui[i].address);
					printf("\n\t\tEmail : ");
					fgets(aui[i].email,19,stdin);
					remove_return(aui[i].email);
					printf("\n\t\tSuccessful update!");
					savestudents();
				break;
			case '6': printf("\n\t\tHave a good day!\n\n");
				 	savestudents();
				 	savealumni();
					return 0;
				break;
			default: printf("\n\t\tINVALID!");
		}
	}
}

void menu(void){
	printf("\n\n\t\t**** Alumni Contact List ****");
	printf("\n\t\t[1] Display all the alumni ..");
	printf("\n\t\t[2] Search ..................");	
	printf("\n\t\t[3] Add an alumnus from .....\n\t\t    the student's list ......");
	printf("\n\t\t[4] Update visits ...........");
	printf("\n\t\t[5] Add a student ...........");		
	printf("\n\t\t[6] Quit ....................");
	printf("\n\t\t... Please make a choice  ...\n");
}

void display(void){
	int i;
	for(i=0;ex_aui[i].name[0]!='\0';i++){
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
	for(i=0;ex_aui[i].name[0]!='\0';i++){
		if(strcasecmp(s,ex_aui[i].name)==0) return i;
	}
	return -1;
}

void displaystudents(void){
	int i;
	for(i=0;i<50;i++){
		if(aui[i].name[0]!='\0'){
			printf("\n\t\tName : %s",aui[i].name);
			printf("\n\t\tPhone : %s",aui[i].phone);
			printf("\n\t\tAddress : %s",aui[i].address);
			printf("\n\t\tEmail : %s",aui[i].email);			
			printf("\n\t\t.............................");
		}
	}
}

int searchstudents(char*s){
	int i;
	for(i=0;i<50;i++){
		if(aui[i].name[0]!='\0'){
			if(strcasecmp(s,aui[i].name)==0) return i;
		}
	}
	return -1;
}

void remove_return(char*string){
	int i;
	for(i=0;string[i]!='\0';i++){
		if(string[i]=='\n') {
			string[i]='\0';
			return;
		}
	}
}
