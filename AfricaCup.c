#include <stdio.h>
#include <string.h>
#define MAX_TEAMS 4

struct player {
	char name[20];
	int age;
	int number;
};

struct team { 
	int size;
	struct player play[11]; 
	char name[20];
	int flag_match;
};

struct ranking {
	struct team *t[MAX_TEAMS];
	int score[MAX_TEAMS];
	int goals[MAX_TEAMS];
	int size;
};

struct time {
	int hour,minutes;
	int d,m,y;
};

struct match {
	char location[20];
	struct team *team1, *team2;
	int score1, score2;
	char *status;
	struct time t;
};

void display(struct team *t);
void display_without(struct team *t);
int search(char* s,struct team *t1,struct team *t2,struct team *t3,struct team *t4);
void set_ranking(struct ranking *theRanking, struct match *theMatch);
void sort(struct ranking *theRanking);
void display_ranking(struct ranking *theRanking);
void swap_struct(struct team *A, struct team *B);
void swap_int(int *A, int *B);
void menu(void);

int main() {
	struct team t1 = {11,{
		{"Drew",25,1},{"Jack",26,2},{"Luke",21,3},
		{"Max",24,4},{"Tom",23,5},{"Cole",30,6},
		{"Finn",25,7},{"Jake",20,8},{"Jude",28,9},
		{"Nate",27,10},{"Ace",29,11}
						},"Zimbabwe",0 };
	struct team t2 = {11,{
		{"Drew",25,1},{"Jack",26,2},{"Luke",21,3},
		{"Max",24,4},{"Tom",23,5},{"Cole",30,6},
		{"Finn",25,7},{"Jake",20,8},{"Jude",28,9},
		{"Nate",27,10},{"Ace",29,11}
						},"Congo" ,0};
	struct team t3 = {11,{
		{"Drew",25,1},{"Jack",26,2},{"Luke",21,3},
		{"Max",24,4},{"Tom",23,5},{"Cole",30,6},
		{"Finn",25,7},{"Jake",20,8},{"Jude",28,9},
		{"Nate",27,10},{"Ace",29,11}
						},"Madagascar",0 };
	struct team t4 = {11,{
		{"Drew",25,1},{"Jack",26,2},{"Luke",21,3},
		{"Max",24,4},{"Tom",23,5},{"Cole",30,6},
		{"Finn",25,7},{"Jake",20,8},{"Jude",28,9},
		{"Nate",27,10},{"Ace",29,11}
						},"Namibia" ,0};


	struct match matches[MAX_TEAMS/2] = {};

	struct ranking theRanking;
	theRanking.size = 0;
	theRanking.t[0] = &t1;
	theRanking.score[0] = 0;
	theRanking.goals[0] = 0;
	theRanking.size = 1;
	theRanking.t[1] = &t2;
	theRanking.score[1] = 0;
	theRanking.goals[1] = 0;
	theRanking.size = 2;
	theRanking.t[2] = &t3;
	theRanking.score[2] = 0;
	theRanking.goals[2] = 0;
	theRanking.size = 3;
	theRanking.t[3] = &t4;
	theRanking.score[3] = 0;
	theRanking.goals[3] = 0;
	theRanking.size = 4;

	int i,b,cntmatch=0,play;
	char junk,s1[20],s2[20],s[20],choice;
	int flag_rank=0;
	int flag_playedmatches=0;
 	
 	while(1){
 		menu();
 		scanf(" %c",&choice);

 		switch(choice){
 			case '1': printf("\n\t\tDo you also want to display the players? \n\t\t(y for yes,n for no): ");
					scanf(" %s",s);
					if(strcasecmp(s,"y")==0){
						for(i=0;i<MAX_TEAMS;i++){
 							display(theRanking.t[i]);
 						}
 					} else if(strcasecmp(s,"n")==0){
 						for(i=0;i<MAX_TEAMS;i++){
 							display_without(theRanking.t[i]);
 						}

 					} else printf("\n\t\tInvalid Choice! ");
 					
 				break;
 			case '2': if(cntmatch!=2){
 					printf("\n\t\tWho is the first team? ");
					scanf(" %s",s1);
					b=search(s1,&t1,&t2,&t3,&t4);
					switch(b){
						case 0: if(t1.flag_match==0) {
									matches[cntmatch].team1=&t1;
									t1.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case 1: if(t2.flag_match==0) {
									matches[cntmatch].team1=&t2;
									t2.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case 2: if(t3.flag_match==0) {
									matches[cntmatch].team1=&t3;
									t3.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case 3: if(t4.flag_match==0) {
									matches[cntmatch].team1=&t4;
									t4.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case -1: printf("\n\t\tERROR! ");
							return 1;
							break;
					}
					printf("\n\t\tWho is the second team? ");
					scanf(" %s",s2);
					b=search(s2,&t1,&t2,&t3,&t4);
					switch(b){
						case 0: if(t1.flag_match==0) {
									matches[cntmatch].team2=&t1;
									t1.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case 1: if(t2.flag_match==0) {
									matches[cntmatch].team2=&t2;
									t2.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case 2: if(t3.flag_match==0) {
									matches[cntmatch].team2=&t3;
									t3.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match!  ");
									return 1;
								}
							break;
						case 3: if(t4.flag_match==0) {
									matches[cntmatch].team2=&t4;
									t4.flag_match=1;
								} else {
									printf("\n\t\tERROR! Team already in a match! ");
									return 1;
								}
								break;
						case -1: printf("\n\t\tERROR! ");
							return 1;
							break;
					}
					matches[cntmatch].status = "Not yet played";
					printf("\n\t\tWhere is this match happening? : ");
					scanf(" %s",matches[cntmatch].location);
					printf("\n\t\tWrite the date in this format? dd/mm/yy : ");
					scanf("%d/%d/%d",&matches[cntmatch].t.d,&matches[cntmatch].t.m,&matches[cntmatch].t.y);
					printf("\n\t\tWrite the time in this format? hh:mm : ");
					scanf("%d:%d",&matches[cntmatch].t.hour,&matches[cntmatch].t.minutes);
					cntmatch++;
					} else printf("\n\t\tThere are already two planned matches!");
 				break;
 			case '3': if(cntmatch!=2) printf("\n\t\tYou should plan two matches before playing them! ");
 					else{
 					if(strcmp(matches[0].status,"Played")==0 && strcmp(matches[1].status,"Played")==0) printf("\n\t\tBoth matches are played!");
 					else {
 					printf("\n\t\t[%d] %s \tvs.\t %s\t- %s",1,matches[0].team1->name,matches[0].team2->name,matches[0].status);
 					printf("\n\t\t[%d] %s \tvs.\t %s\t- %s",2,matches[1].team1->name,matches[1].team2->name,matches[1].status);
 					printf("\n\t\tWhich match do you want to play? ");
					scanf("%d",&play);

					if(play-1>=MAX_TEAMS/2 || play-1<0) printf("\n\t\tInvalid Choice! ");
					else if(strcmp(matches[play-1].status,"Played")==0) printf("\n\t\tMatch already played! ");
					else {
						printf("\n\t\tWhat is the score of %s? ",matches[play-1].team1->name);
						scanf("%d",&matches[play-1].score1);
						printf("\n\t\tWhat is the score of %s? ",matches[play-1].team2->name);
						scanf("%d",&matches[play-1].score2);
						matches[play-1].status = "Played";
						set_ranking(&theRanking,&matches[play-1]); 
						flag_playedmatches++;
						 }
						}
					}
 				break;
 			case '4': if(cntmatch<2) printf("\n\t\tYou should plan both matches before displaying the info! ");
 					else if(flag_rank==1) printf("\n\t\tBoth matches have already happened! ");
 						else {
 						for(i=0;i<MAX_TEAMS/2;i++){
 							printf("\n\t\t[%d] %s \tvs.\t %s\t- %s",i+1,matches[i].team1->name,matches[i].team2->name,matches[i].status);
 							printf("\n\t\tLocation : %s\t Date : %d/%d/%d\t Time : %d:%d",matches[i].location,matches[i].t.d,matches[i].t.m,matches[i].t.y,matches[i].t.hour,matches[i].t.minutes);
 						}
 					}
 				break;
 			case '5': if(cntmatch<2) printf("\n\t\tYou should plan both matches before displaying the ranking! ");
 					else if (flag_playedmatches!=2) printf("\n\t\tYou should play both matches before displaying the ranking! ");
				 	else {
 						sort(&theRanking);
 						display_ranking(&theRanking);
 						flag_rank=1;
 					}
 				break;
 			case '6': printf("\n\t\tGoodbye! ");
 				return 0;
 				break;
 			default: printf("\n\t\tInvalid Choice! ");

 		}
	}
	
}
void display(struct team *t){
	int i;
	printf("\n\n\t\t%25s",t->name);
	printf("\n\t\t Country : %s ",t->name);
	for(i=0;i<11;i++){
		printf("\n\t\t Player #%d : %s\tAge: %d\tNumber: %d",i+1,t->play[i].name,t->play[i].age,t->play[i].number);
	}
}

void display_without(struct team *t){
	printf("\n\t\t Country : %s ",t->name);
}

void menu(void){
	printf("\n\n\t\t******* AFRICA CUP *******");
	printf("\n\t\t[1] Display teams .........");
	printf("\n\t\t[2] Plan a match ..........");
	printf("\n\t\t[3] Play a match ..........");	
	printf("\n\t\t[4] Display match info ....");	
	printf("\n\t\t[5] Display ranking .......");	
	printf("\n\t\t[6] Quit ..................");		
	printf("\n\t\t... Please make a choice  ...\n");
	printf("\n\t\t");
}

int search(char* s,struct team *t1,struct team *t2,struct team *t3,struct team *t4){
 	if(strcasecmp(t1->name,s)==0) return 0;
 	if(strcasecmp(t2->name,s)==0) return 1;
 	if(strcasecmp(t3->name,s)==0) return 2;
 	if(strcasecmp(t4->name,s)==0) return 3;
 	return -1;
}

void set_ranking(struct ranking *theRanking, struct match *theMatch) {
	struct team *t1, *t2;
	int t1num, t2num;
	t1 = (*theMatch).team1;
	t2 = theMatch->team2;
	
	for(t1num = 0; 
		t1num < MAX_TEAMS && theRanking->t[t1num]!= t1; 
		t1num++);
	for(t2num = 0; 
		t2num < MAX_TEAMS && theRanking->t[t2num]!= t2; 
		t2num++);
	
	if(theMatch->score1 > theMatch->score2)
		theRanking->score[t1num] += 3;
	else if(theMatch->score2 > theMatch->score1)
		theRanking->score[t2num] += 3;
	else {
		theRanking->score[t1num] ++;
		theRanking->score[t2num] ++;
		}
		
	theRanking->goals[t1num] += theMatch->score1;
	theRanking->goals[t2num] += theMatch->score2;

}

void sort(struct ranking *theRanking) {

	int i,j;

	for (i = 0; i < MAX_TEAMS-1; i++) {   
        for (j = 0; j < MAX_TEAMS - i -1; j++) { 
            if (theRanking->score[j] < theRanking->score[j+1]) {  
               	swap_struct(theRanking->t[j],theRanking->t[j + 1]);
               	swap_int(&theRanking->score[j],&theRanking->score[j + 1]);
               	swap_int(&theRanking->goals[j],&theRanking->goals[j + 1]);
            }
        }
    }
}

void display_ranking(struct ranking *theRanking){
	int i;
	printf("\n\tTEAM NAME\tSCORE\tGOALS");
	for(i=0;i<MAX_TEAMS;i++){
		printf("\n\t%10s\t%d\t%d",theRanking->t[i]->name,theRanking->score[i],theRanking->goals[i]);
	}

}

void swap_struct(struct team *A, struct team *B){
    struct team temp = *A;
    *A = *B;
    *B = temp;
}

void swap_int(int *A, int *B){
    int temp = *A;
    *A = *B;
    *B = temp;
}
