#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
int pos = 0;
int depth = 0;

void E();
void T();
void F();

void trace(const char *text)
{
    for (int i = 0; i < depth; i++) printf("    ");
    printf("%-14s [remaining: %s]\n", text, input[pos] ? input + pos : "end");
}

void match(char c)
{
    if (input[pos] == c)
    {
        char text[20];
        sprintf(text, "match '%c'", c);
        trace(text);
        pos++;
    }
    else
    {
        printf("Invalid expression\n");
        exit(1);
    }
}

void E()
{
    trace("E -> T {+ T}");
    depth++;
    T();
    while (input[pos] == '+')
    {
        match('+');
        T();
    }
    depth--;
}

void T()
{
    trace("T -> F {* F}");
    depth++;
    F();
    while (input[pos] == '*')
    {
        match('*');
        F();
    }
    depth--;
}

void F()
{
    if (isalpha(input[pos]))
    {
        char text[20];
        sprintf(text, "F -> id '%c'", input[pos]);
        trace(text);
        pos++;
    }
    else if (input[pos] == '(')
    {
        trace("F -> ( E )");
        depth++;
        match('(');
        E();
        match(')');
        depth--;
    }
    else
    {
        printf("Invalid expression\n");
        exit(1);
    }
}

int main()
{
    printf("Enter expression: ");
    scanf("%s", input);

    E();

    if (input[pos] == '\0')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
