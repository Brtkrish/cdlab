#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

int reduce(char next)
{
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    if (top >= 2 &&
        stack[top-2] == 'E' &&
        stack[top-1] == '+' &&
        stack[top] == 'E' &&
        next != '*')          /* * has higher precedence: shift first */
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    if (top >= 2 &&
        stack[top-2] == 'E' &&
        stack[top-1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    if (top >= 2 &&
        stack[top-2] == '(' &&
        stack[top-1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

void display()
{
    for (int i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int main()
{
    char input[100];

    printf("Enter expression using i for identifier: ");
    scanf("%s", input);
    strcat(input, "$");

    int i = 0;

    while (1)
    {
        if (reduce(input[i]))
        {
            printf("Stack: ");
            display();
            printf("  Reduce\n");
        }
        else if (input[i] != '$')
        {
            stack[++top] = input[i++];
            printf("Stack: ");
            display();
            printf("  Shift\n");
        }
        else
        {
            if (top == 0 && stack[0] == 'E')
                printf("Accepted\n");
            else
                printf("Rejected\n");
            break;
        }
    }
    return 0;
}
