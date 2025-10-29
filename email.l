%{
#include "email.tab.h"
%}

%option noyywrap

%%
[a-zA-Z0-9_.]+[@][a-zA-Z0-9_]+[.][a-zA-Z]+   return EMAIL;
.                                             return INVALID;
\n                                            return 0;
%%
