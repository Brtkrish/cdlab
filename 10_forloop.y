%{
#include <stdio.h>
%}

%token FOR ID NUM INC

%%
statement:
    FOR '(' initialization ';' condition ';' increment ')'
    { printf("Valid FOR statement\n"); }
    ;

initialization: ID '=' NUM ;
condition: ID '<' NUM ;
increment: ID INC ;
%%

int yyerror(char *s)
{
    printf("Invalid FOR statement\n");
    return 0;
}

int main()
{
    printf("Enter FOR statement: ");
    yyparse();
    return 0;
}
