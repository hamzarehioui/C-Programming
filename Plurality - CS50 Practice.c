#include <stdio.h>
#include <string.h>
#include <cs50.h>

const int MAX=9;
bool vote(string name,int n);
void print_winner(void);
typedef struct{
    string name;
    int vote;
} candidate;

candidate candidates[MAX];

int main(int argc,string argv[]){
    if(argc<3 ||argc>MAX+1){
        printf("No less than 2 and no more than %d candidates! ",MAX);
        return 1;
    }
    int n=argc-1;


    for(int i=0;i<n;i++){
        candidates[i].name=argv[i+1];
        candidates[i].vote=0;
    }

    int number = get_int("Number of voters: ");

    for(int i=0;i<number;){
        string name = get_string("Vote: ");
        if(vote(name,n)==true) i++;
        else printf("Invalid vote.\n");
    }

    print_winner();

    return 0;
}

bool vote(string name,int n){
    for(int i=0;i<n;i++){
        if(strcmp(name,candidates[i].name)==0){
            candidates[i].vote++;
            return true;
        }
    }
    return false;
}

void print_winner(void){
    int ind_max_votes=0;
    for(int i=0;i<MAX;i++){
        if(candidates[i].vote>candidates[ind_max_votes].vote)
            ind_max_votes=i;
    }
    for(int i=0;i<MAX;i++){
        if(candidates[i].vote==candidates[ind_max_votes].vote)
            printf("%s\n",candidates[i].name);
    }
}