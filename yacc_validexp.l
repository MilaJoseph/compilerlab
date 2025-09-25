%{
#include "y.tab.h"
%}
%option noyywrap
%%
[_a-zA-Z][_a-zA-Z0-9]+ {return id;}
[0-9]+ {return num;}
\n {return '\n';}
. {return yytext[0];}
%%
