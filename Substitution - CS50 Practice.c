#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int check_for_number(string s);
int check_for_rep(string s);

int main(int argc,string argv[]){

    if (argc==1){
        printf("Usage: ./substitution key\n");
        return 1;
    } else if(strlen(argv[1])!=26){
        printf("Key must contain 26 characters.\n");
        return 1;
    } else if(check_for_number(argv[1])==0){
        printf("Usage: ./substitution key\n");
        return 1;
    } else if(check_for_rep(argv[1])==0){
        printf("No repeated characters in key\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    for(int i=0,n=strlen(plaintext);i<n;i++){
        if(plaintext[i]>='A'&&plaintext[i]<='Z'){
            printf("%c",toupper(argv[1][(int)plaintext[i]-65]));
        }
        else if(plaintext[i]>='a'&&plaintext[i]<='z'){
            printf("%c",tolower(argv[1][(int)plaintext[i]-97]));
        }
        else printf("%c",plaintext[i]);}

    printf("\n");
}

int check_for_number(string s){
    for(int i=0,n=strlen(s);i<n;i++){
        if(s[i]>='0'&&s[i]<='9'){
            return 0;
        }
    }
    return 1;
}

int check_for_rep(string s){
    for(int i=0,n=strlen(s);i<n;i++){
        for(int j=0;j<n;j++){
            if(toupper(s[i])==toupper(s[j])&&j!=i) return 0;
        }
    }
    return 1;
}