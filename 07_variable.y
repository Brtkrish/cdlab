%{
#include <stdio.h>
%}

%token LETTER DIGIT

%%
input:
    variable '\n' { printf("Valid variable\n"); }
    ;

variable:
    LETTER rest
    ;

rest:
      /* empty */
    | rest LETTER
    | rest DIGIT
    ;
%%

int yyerror(char *s)
{
    printf("Invalid variable\n");
    return 0;
}

int main()
{
    printf("Enter variable: ");
    yyparse();
    return 0;
}
