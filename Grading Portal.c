/***************************************************************
THIS IS A PROGRAM FOR PROFESSORS TO MANAGE THEIR CLASSES
WELCOME, WHOEVER LOGS IN WITH A RIGHT PASSWORD CAN ACCESS 
THE GRADING PORTAL IN WHICH HE OR SHE CAN INPUT ALL GRADES 
OF ANY SECTION AND AFTER FILLING ALL STRUCTURES, THE PROGRAM
WILL ALLOW THE USER TO PRINT A SECTION REPORT WITH EACH STUDENT'S
NAME, MAJOR AND FINAL GRADE;

THE LOGIN INFO IS THE FOLLOWING: 
username(ALL CAPS): PROFESSOR (or) GRADER
password(ALL CAPS): DATA (for both accounts)
*****************************************************************/

#include <stdio.h>
#include <string.h>
int search(char*);
void menu(void);
void display(void);
int checklog(char*s,int n);

/*To make the code short, let's suppose there are 3 students in each section.
in every section and you can add as many students as 
you want and as many sections as you want.
*/

struct login{
	char user[20];
	char pw[20];
};

struct login signin[2] = {{"PROFESSOR","DATA"},{"GRADER","DATA"}};

struct student{
	char fullname[20];
	char major[7];
	double quizz[5];	//25% of final grade
	double midterm;		//25% of final grade
	double finalexam;	//30% of final grade
	double absences;	//20% of final grade
	double final;
};

struct section{
	char* place;
	char* timeslot;
	struct student edu[3];
};

//Now we'll declare 2 sections for the professor

struct section s1 = {"B8B Room 7","TR 2:30pm-3:20pm",
		{{"Bob Bob","BSCSC",{0,0,0,0,0},0,0,0,0},
		{"Amy Amy","BSEMS",{0,0,0,0,0},0,0,0,0},
		{"Ron Ron","BSGE",{0,0,0,0,0},0,0,0,0}}};
		
struct section s2;
/*
We won't be using section 2 here it is only here 
to show that there can be as many sections as possible
*/

char signinstring[20];
/*
This is the string where the name of the user is saved
so as to print (the username)'s Portal
*/

int n = 0; /*
Counter to check if all needed grades are filled to enable printing
*/

int main(void){
	int choice=0,i,b,c,g;//choices and flag and counters
	int flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flag6=0,flag7=0,flag8=0;//for already filled arrays
	char s[20],junk;//search inquiry and new line junk
	char username[20],password[20]; // login info
	int sec; //section number
	
	printf("\n\n\t\t**** This is your Portal ****");
	
	printf("\n\t\tINPUT USERNAME : ");
	scanf("%s",username);
	while(checklog(username,1)==0){
		printf("\t\tWRONG USERNAME! ");
		printf("\n\t\tINPUT USERNAME : ");
		scanf(" %s",username);
	}
	printf("\n\t\tINPUT PASSWORD : ");
	scanf("%s",password);
	while(checklog(password,2)==0){
		printf("\t\tWRONG PASSWORD!");
		printf("\n\t\tINPUT PASSWORD : ");
		scanf(" %s",password);
	}
	
	printf("\n\n\t\t**** %s's Portal ****",signinstring);
	printf("\n\t\t[1] Access Section 1 ......");
	printf("\n\t\t[2] Access Section 2 ......");
		
	printf("\n\t\tINPUT SECTION : ");
	scanf("%d",&sec);
	
	while(sec!=1){
		printf("\n\t\tSECTION %d DOESN'T EXIST YET!",sec);
		printf("\n\t\tINPUT SECTION : ");
		scanf("%d",&sec);	
	}
	
	while(1>0){
		menu();
		printf("\n\t\t");
		scanf("%d",&choice);
		switch(choice){
			case 1: if(flag1==0){for(i=0;i<3;i++){
				printf("\n\t\tQuizz 1 of %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].quizz[0]);
				}
				n++;
				flag1=1;} else printf("\n\t\tQuizz 1 is already filled.");
				break;
			case 2: if(flag2==0){for(i=0;i<3;i++){
				printf("\n\t\tQuizz 2 of %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].quizz[1]);
				}
				n++;
				flag2=1;} else printf("\n\t\tQuizz 2 is already filled.");
				break;
			case 3: if(flag3==0){for(i=0;i<3;i++){
				printf("\n\t\tQuizz 3 of %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].quizz[2]);
				}
				n++;
				flag3=1;} else printf("\n\t\tQuizz 3 is already filled.");
				break;
			case 4: if(flag4==0){for(i=0;i<3;i++){
				printf("\n\t\tQuizz 4 of %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].quizz[3]);
				}
				n++;
				flag4=1;} else printf("\n\t\tQuizz 4 is already filled."); 
				break;
			case 5: if(flag5==0){for(i=0;i<3;i++){
				printf("\n\t\tQuizz 5 of %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].quizz[4]);
				}
				n++;
				flag5=1;} else printf("\n\t\tQuizz 5 is already filled."); 
				break;
			case 6: if(flag6==0){for(i=0;i<3;i++){
				printf("\n\t\tMidterm of %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].midterm);
				}
				n++;
				flag6=1;} else printf("\n\t\tMidterm is already filled."); 
				break;
			case 7: if(flag7==0){for(i=0;i<3;i++){
				printf("\n\t\tFinal Exam %s: ",s1.edu[i].fullname);
				scanf("%lf",&s1.edu[i].finalexam);
				}
				n++;
				flag7=1;} else printf("\n\t\tFinal Exam is already filled."); 
				break;
			case 8: printf("\n\t\tWho is absent today? ");
					scanf("%c",&junk);
					gets(s);
					b=search(s);
					if(b==-1) printf("\n\t\tThere is no student named %s.",s);
					else {
						s1.edu[b].absences++;
						printf("\n\t\tSuccessful update!");
					}
				break;
			case 9: for(i=0;i<3;i++){
					s1.edu[i].final=((s1.edu[i].quizz[0]+s1.edu[i].quizz[1]+
					s1.edu[i].quizz[2])/3)*0.25+((40-s1.edu[i].absences)*100/40)*0.2+
					s1.edu[i].final*0.3+s1.edu[i].midterm*0.25;
					}
					display();
				return 0;
				break;	
		}
			
	}
	
	
}

void menu(void){
	printf("\n\n\t\t**** Professor's Portal ****");
	printf("\n\t\t[1] Add QUIZZ 1 ...........");
	printf("\n\t\t[2] Add QUIZZ 2 ...........");	
	printf("\n\t\t[3] Add QUIZZ 3 ...........");	
	printf("\n\t\t[4] Add QUIZZ 4 ...........");	
	printf("\n\t\t[5] Add QUIZZ 5 ...........");	
	printf("\n\t\t[6] Add Midterm ...........");
	printf("\n\t\t[7] Add Final Exam ........");
	printf("\n\t\t[8] Update Absence ........");
	if(n==7) printf("\n\t\t[9] Print Class Report .....");
	printf("\n\t\t... Please make a choice  ...\n");
}

int search(char*s){
	int i;
	for(i=0;i<3;i++){
		if(strcasecmp(s,s1.edu[i].fullname)==0) return i;
	}
	return -1;
}

void display(void){
	int i;
	printf("\n\t\t**************** Final Section Report ******************\n");
	printf("\n\t\tPlace: %s\tTime Slot: %s\n",s1.place,s1.timeslot);
	for(i=0;i<3;i++){
		printf("\n\t\tName: %s\tMajor: %s\tFinal Grade: %.2f",s1.edu[i].fullname,s1.edu[i].major,s1.edu[i].final);
	}
	printf("\n\n\t\t********************************************************\n\n\n");
}

int checklog(char*s,int n){
	int i;
	if(n==1) {
		for(i=0;i<2;i++){
		if(strcmp(s,signin[i].user)==0) {strcpy(signinstring,signin[i].user);			
		return 1;}
		}
	return 0;
	}
	if(n==2) {
		for(i=0;i<2;i++){
		if(strcmp(s,signin[i].pw)==0) return 1;			
		}
	return 0;
	}

}