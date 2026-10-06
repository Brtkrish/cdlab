%{
#include "y.tab.h"
#include <string.h>
%}

%%
[0-9]+ { yylval.str = strdup(yytext); return ID; }
[ \t] ;
\n return '\n';
. return yytext[0];
%%
