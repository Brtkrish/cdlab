%{
#include "y.tab.h"
%}

%%
"for"       return FOR;
[a-zA-Z]    return ID;
[0-9]+      return NUM;
"++"        return INC;
"="         return '=';
";"         return ';';
"("         return '(';
")"         return ')';
"<"         return '<';
[ \t\n] ;
. return yytext[0];
%%
