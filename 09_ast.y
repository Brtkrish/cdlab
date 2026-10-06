%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char data[20];
    struct Node *left, *right;
} Node;

Node *createNode(char *data, Node *left, Node *right)
{
    Node *n = malloc(sizeof(Node));
    strcpy(n->data, data);
    n->left = left;
    n->right = right;
    return n;
}

void preorder(Node *root)
{
    if (!root) return;
    printf("%s ", root->data);
    preorder(root->left);
    preorder(root->right);
}
%}

%union {
    char *str;
    Node *node;
}

%token <str> ID
%type <node> E T F
%left '+'
%left '*'

%%
input:
    E '\n' {
        printf("Preorder of AST: ");
        preorder($1);
        printf("\n");
    }
    ;

E:
      E '+' T { $$ = createNode("+", $1, $3); }
    | T        { $$ = $1; }
    ;

T:
      T '*' F { $$ = createNode("*", $1, $3); }
    | F        { $$ = $1; }
    ;

F:
      '(' E ')' { $$ = $2; }
    | ID        { $$ = createNode($1, NULL, NULL); }
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
