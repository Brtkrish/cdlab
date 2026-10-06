%{
#include <stdio.h>
%}

%%
.*NIYA.*     { printf("Rejected: String contains NIYA\n"); }
.*           { printf("Accepted: String does not contain NIYA\n"); }
%%

int yywrap() { return 1; }

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}
