%{
#include "y.tab.h"
%}
%option noyywrap
%%
[_a-zA-Z] {return alpha;}
[0-9] {return number;}
\n {return '\n';}
. {return yytext[0];}
%%
