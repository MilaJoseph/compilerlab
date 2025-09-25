%{
int yylex();
int yyerror();
#include<stdio.h>
%}
%token id num

%left '+' '-'
%left '*' '/'
%right '^'
%left '(' ')'
%%
start : E '\n' {printf("Valid Expression\n"); return 0;}
E :     E '+' E
        |E '-' E
        |E '*' E
        |E '/' E
        |E '^' E
        |'(' E ')'
        |num
        |id
        ;
%%
int main(){
        return yyparse();
}
int yyerror(){
        printf("Invalid Expression\n");
}
