%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
int valid = 0;
%}

%token EMAIL INVALID

%%
S : EMAIL        { valid = 1; }
  | INVALID      { valid = 0; }
  ;
%%

int main() {
    printf("Enter an email address:\n");
    if (yyparse() == 0 && valid)
        printf("✅ Valid email address\n");
    else
        printf("❌ Invalid email address\n");
    return 0;
}

void yyerror(const char *s) {
    // suppress automatic error message
}
