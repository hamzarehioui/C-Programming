#include <stdio.h>
#include <cs50.h>
#include <math.h>

int digits(long n);
int sum_other(long n);
int sum_not_other(long n);
int sum_up(int n);

int main(void){
    long n = get_long("Number: ");
    long a,b,c,d,e,f;

    a = n/pow(10,digits(n)-1);
    b = n/pow(10,digits(n)-2);
    c = digits(n);
    e = sum_other(n);
    f = sum_not_other(n);
    d = (sum_other(n)+sum_not_other(n))%10;
    
     
    if(d==0){
        if(c==15&&b==37) printf("AMEX\n");
        else if(c==15&&b==34) printf("AMEX\n");
        else if(c==16&&b==51) printf("MASTERCARD\n");
        else if(c==16&&b==52) printf("MASTERCARD\n");        
        else if(c==16&&b==53) printf("MASTERCARD\n");
        else if(c==16&&b==54) printf("MASTERCARD\n");        
        else if(c==16&&b==55) printf("MASTERCARD\n");
        else if(c==13&&a==4) printf("VISA\n");
        else if(c==16&&a==4) printf("VISA\n");
        else printf("INVALID\n");
    }
    else printf("INVALID\n");
    
}

int digits(long n){
    long div = n; 
    int i=0;
    while(div>=1){
        div/=10;
        i++;
    }
    return i;
}

int sum_other(long n){
    long b=n,g;
    int sum=0;
    b/=10;
    while(b>=1){
        g=sum_up((b%10)*2);
        sum+=(g);
        b/=100;
    }
    
    return sum;
}
int sum_not_other(long n){
    long b=n;
    int sum=0;
    
    while(b>=1){
        sum+=b%10;
        b/=100;
    }
    
    return sum;
}
int sum_up(int n){
    int sum=0,b=n;
    
    while(b>=1){
        sum+=b%10;
        b/=10;
    }
    return sum;
}
