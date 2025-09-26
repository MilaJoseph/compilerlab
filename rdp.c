#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define SIZE 20

void E();
void Eprime();
void T();
void Tprime();
void F();

int i=0,error;
char input[SIZE];

void F(){
        if(isalnum(input[i])){
                i++;
        }else if(input[i]=='('){
                i++;
                E();
                if(input[i]==')'){
                        i++;
                }else{
                        error=1;
                }
        }else{
                error=1;
        }
}

void Tprime(){
        if(input[i]=='*' || input[i]=='/'){
                i++;
                F();
                Tprime();
        }
}

void T(){
        F();
        Tprime();
}

void Eprime(){
        if(input[i]=='+' || input[i]=='-'){
                i++;
                T();
                Eprime();
        }
}

void E(){
        T();
        Eprime();
}


void main(){
        printf("Enter an arithmetic expression: ");
        scanf(" %[^\n]",input);

        E();

        if(!error && i==strlen(input)){
                printf("ACCEPTED!!\n");
        }else{
                printf("REJECTED!!\n");
        }
}
