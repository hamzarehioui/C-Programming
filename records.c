#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define MAX_COURSES 20
#define MAX_STUDENTS 50

typedef struct {
	char courseid[8];
	int section;
	float grade;
} course;

typedef struct {
	char firstname[15], lastname[15];
	course courses[MAX_COURSES];
} studentRecord;

studentRecord theRecord;

studentRecord NewRecord;

studentRecord students[MAX_STUDENTS] = {{"John","John",{{"MTH1311",2,-1},{"CSC1401",5,-1},{"ARB1201",1,-1},{"FAS0210",2,-1}}},
									   {"Amy","Amy",{{"MTH1312",4,-1},{"CSC2302",3,-1},{"FRN1201",2,-1},{"FAS1210",9,-1}}},
									   {"Emily","Emily",{{"MTH1304",8,-1},{"PSY2303",7,-1},{"PHY1201",6,-1},{"FRN3301",5,-1}}},
									   {"Bob","Bob",{{"MTH1311",2,-1},{"CSC1401",5,-1},{"ARB1201",8,-1},{"FAS0210",2,-1}}}};

typedef struct {
	char firstname[15], lastname[15];
} studentIndex;

studentIndex indeces[MAX_STUDENTS];

void readIndeces(void);
void savetxt(void);
void openbin(void);
int findStudent(char *firstname, char *lastname);
void fillStudent(int index, studentRecord *student);
void menu(void);
void display(void);
void fillnewgrade(int index,studentRecord *student);
void displaytxt(void);
void makenewrecord(int index);

int main(void){
	int indexstudent,flagcourse=0,indexcourse,i;
	char choice,firstnamesearch[15],lastnamesearch[15],courseidsearch[8];

	savetxt();
	readIndeces();
	openbin();

	while(1){
		indexcourse=0;
		indexstudent=0;
		flagcourse=0;
		menu();
		printf("\n\t\t");
		scanf(" %c",&choice);
		switch(choice){
			case '1': displaytxt();
				break;
			case '2': getchar();
					  printf("\n\t\tWhat are the student's first and last name? \n\t\t");
					  scanf("%s %s",firstnamesearch,lastnamesearch);
					  indexstudent=findStudent(firstnamesearch,lastnamesearch);
					  if(indexstudent==-1){
					  	printf("\n\t\tThere is no student named %s %s.",firstnamesearch,lastnamesearch);
					  	break;
					  }
					  fillStudent(indexstudent,&theRecord);
					  display();
				break;
			case '3': getchar();
					  printf("\n\t\tWhat are the student's first and last name? \n\t\t");
					  scanf("%s %s",firstnamesearch,lastnamesearch);
					  indexstudent=findStudent(firstnamesearch,lastnamesearch);
					  if(indexstudent==-1){
					  	printf("\n\t\tThere is no student named %s %s.",firstnamesearch,lastnamesearch);
					  	break;
					  }
					  fillStudent(indexstudent,&theRecord);
					  printf("\n\t\tWhat is the course's ID? \n\t\t");
					  scanf(" %s",courseidsearch);
					  for(i=0;theRecord.courses[i].courseid[0]!=0;i++){
					  	if(strcasecmp(courseidsearch,theRecord.courses[i].courseid)==0) {
					  		flagcourse=1;
					  		indexcourse=i;
					  	}
					  }
					  if(flagcourse==0){
					  	printf("\n\t\t%s %s has no course called %s.",firstnamesearch,lastnamesearch,courseidsearch);
					  	break;
					  }
					  if(theRecord.courses[indexcourse].grade!=-1){
					  	printf("\n\t\tThe %s grade is already filled!\n\t\t",courseidsearch);
					  	break;
					  }
					  printf("\n\t\tWhat is the grade? \n\t\t");
					  scanf("%f",&theRecord.courses[indexcourse].grade);
					  fillnewgrade(indexstudent,&theRecord);
					  printf("\n\t\tSuccessful update!");
				break;
			case '4': getchar();
					  printf("\n\t\tWhat are the student's first and last name? \n\t\t");
					  scanf("%s %s",firstnamesearch,lastnamesearch);
					  for(i=0;indeces[i].firstname[0]!='\0';i++);
					  indexstudent=i;
					  strcpy(indeces[i].firstname,firstnamesearch);
					  strcpy(indeces[i].lastname,lastnamesearch);
					  strcpy(NewRecord.firstname,indeces[i].firstname);
					  strcpy(NewRecord.lastname,indeces[i].lastname);
					  NewRecord.courses[0].courseid[0]='n';
					  for(i=0;i<MAX_COURSES&&strcasecmp(NewRecord.courses[i-1].courseid,"stop");i++){
					  	printf("\n\t\tWrite the course he is taking followed by section number?\n\t\t(or enter ""stop 0"" to stop)\n\t\t");
					  	scanf(" %s %d",NewRecord.courses[i].courseid,&NewRecord.courses[i].section);
					  	NewRecord.courses[i].grade=-1;
					  }
					  if(!strcasecmp(NewRecord.courses[i-1].courseid,"stop")) NewRecord.courses[i-1].courseid[0]='\0';
					  savetxt();
					  readIndeces();
					  makenewrecord(indexstudent);
				break;
			case '5': return 0;
				break;
			default: printf("\n\t\tINVALID CHOICE!");
				break;
		}
	}
}

void display(void){
	int i;
	printf("\n\t\tFull name: %s %s",theRecord.firstname,theRecord.lastname);
	for(i=0;theRecord.courses[i].courseid[0]!='\0';i++){
		if(theRecord.courses[i].grade==-1)
			printf("\n\t\tCourse #%d: %s\tSection #%d\tGrade: NG",i+1,theRecord.courses[i].courseid,theRecord.courses[i].section);
		else
			printf("\n\t\tCourse #%d: %s\tSection #%d\tGrade: %.2f",i+1,theRecord.courses[i].courseid,theRecord.courses[i].section,theRecord.courses[i].grade);
	}
}

void readIndeces(){
	FILE *infile = fopen("index.txt", "r");
	int current = 0;
	while(!feof(infile)) {
		fscanf(infile, "%s %s", indeces[current].firstname, indeces[current].lastname);
		current ++;
	}
	fclose(infile);
}

void savetxt(void){
	FILE* studentfile = fopen("index.txt","r");
	int i;
	if(studentfile==NULL) {
		studentfile = fopen("index.txt","w");
		for(i=0;students[i].firstname[0]!='\0';i++) fprintf(studentfile,"%s %s\n",students[i].firstname,students[i].lastname);
	}
	else { 
		fclose(studentfile);
		studentfile = fopen("index.txt","a");
		for(i=0;indeces[i].firstname[0]!='\0';i++);
		fprintf(studentfile,"%s %s\n",indeces[i-1].firstname,indeces[i-1].lastname);
		fclose(studentfile);
		return;
	}
	fclose(studentfile);
}

void openbin(void){
	FILE* studentfile = fopen("student.bin","rb");
	if(studentfile==NULL) {
		studentfile = fopen("student.bin","wb");
		fwrite(students,sizeof(studentRecord),MAX_STUDENTS,studentfile);
		fclose(studentfile);
	}
	else { 
		fclose(studentfile);
		return;
	}
}

int findStudent(char *firstname, char *lastname) {
	int current = 0;
	while(strcasecmp(firstname, indeces[current].firstname)
		|| strcasecmp(lastname,indeces[current].lastname)){
			current++;
			if(current==MAX_STUDENTS) return -1;
		}
	return current;
}

void fillStudent(int index, studentRecord *student) {
	FILE *rfile = fopen("student.bin", "rb");
	fseek(rfile, index*sizeof(studentRecord), SEEK_CUR);
	fread(student, sizeof(studentRecord), 1, rfile);
	fclose(rfile);
}

void fillnewgrade(int index, studentRecord *student) {
	FILE *rfile = fopen("student.bin", "rb+");
	fseek(rfile, index*sizeof(studentRecord), SEEK_CUR);
	fwrite(student, sizeof(studentRecord), 1, rfile);
	fclose(rfile);
}

void displaytxt(void){
	FILE* studentfile = fopen("index.txt","r");
	int i;
	char fullname[30];
	fullname[0]='f';
	
	for(i=0;!feof(studentfile);i++){
		fscanf(studentfile,"%[^\n]\n",fullname);
		printf("\n\t\t%s",fullname);
	}
	fclose(studentfile);
}

void makenewrecord(int index){
	FILE *rfile = fopen("student.bin", "rb+");
	fseek(rfile, index*sizeof(studentRecord), SEEK_CUR);
	fwrite(&NewRecord, sizeof(studentRecord), 1, rfile);
	fclose(rfile);
}

void menu(void){
	printf("\n\n\t\t****** Students' Records ******");
	printf("\n\t\t[1] Display names .............");
	printf("\n\t\t[2] Display a student's record ");
	printf("\n\t\t[3] Add a grade ...............");
	printf("\n\t\t[4] Add a new record ..........");		
	printf("\n\t\t[5] Quit ......................");
	printf("\n\t\t... Please make a choice  ...\n");
}