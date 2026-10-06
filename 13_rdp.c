#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
int pos = 0;

void E();
void T();
void F();

void match(char c)
{
    if (input[pos] == c) pos++;
    else
    {
        printf("Invalid expression\n");
        exit(1);
    }
}

void E()
{
    T();
    while (input[pos] == '+')
    {
        match('+');
        T();
    }
}

void T()
{
    F();
    while (input[pos] == '*')
    {
        match('*');
        F();
    }
}

void F()
{
    if (isalpha(input[pos]))
        pos++;
    else if (input[pos] == '(')
    {
        match('(');
        E();
        match(')');
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
