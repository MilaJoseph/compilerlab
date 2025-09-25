%{
#include<stdio.h>
int yylex();
int yyerror();
%}
%token alpha number
%%
start:S '\n' {printf("Valid identifier\n"); return 0;}
S : alpha A;
A : alpha A
  | number A
  |
  ;
%%
int main(){
        return yyparse();
}
int yyerror(){
        printf("Invalid identifier\n");
}
