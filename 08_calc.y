%{
#include <stdio.h>
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
input:
    expression '\n' { printf("Result = %d\n", $1); }
    ;

expression:
      expression '+' expression { $$ = $1 + $3; }
    | expression '-' expression { $$ = $1 - $3; }
    | expression '*' expression { $$ = $1 * $3; }
    | expression '/' expression { $$ = $1 / $3; }
    | '-' expression %prec UMINUS { $$ = -$2; }
    | '(' expression ')' { $$ = $2; }
    | NUMBER { $$ = $1; }
    ;
%%

int yyerror(char *s)
{
    printf("Invalid expression\n");
    return 0;
}

int main()
{
    printf("Enter expression: ");
    yyparse();
    return 0;
}
