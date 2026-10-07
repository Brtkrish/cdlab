%{
#include <stdio.h>
%}

%%
.*HELLO.*     { printf("Rejected: String contains HELLO\n"); }
.*           { printf("Accepted: String does not contain HELLO\n"); }
%%

int yywrap() { return 1; }

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}
