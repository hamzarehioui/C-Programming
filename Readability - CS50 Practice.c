#include <stdio.h>
#include <cs50.h>

int length(string s);
int word(string s);
int sentence(string s);

int main(void){
    string s = get_string("Input: ");
    double index = 0.0588 * (double)length(s)/word(s)*100 - 0.296 * (double)sentence(s)/word(s)*100 - 15.8;

    if(index<1) printf("Before Grade 1\n");
    else if(index<=16) printf("Grade %.f\n",index);
    else printf("Grade 16+\n");
}

int length(string s){
    int letters=0;
    for(int i=0;s[i]!='\0';i++){
        if(s[i]>='a'&&s[i]<='z') letters++;
        if(s[i]>='A'&&s[i]<='Z') letters++;
    }
    return letters;
}

int word(string s){
    int spaces=1;

    for(int i=0;s[i]!='\0';i++){
        if(s[i]==' ') spaces++;
    }
    return spaces;
}

int sentence(string s){
    int sentences=0;

    for(int i=0;s[i]!='\0';i++){
        if(s[i]=='!'||s[i]=='.'||s[i]=='?') sentences++;
    }
    return sentences;
}