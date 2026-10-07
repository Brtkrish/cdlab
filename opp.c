#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

char precedence[6][6] = {
    {'>', '<', '<', '>', '<', '>'},
    {'>', '>', '<', '>', '<', '>'},
    {'<', '<', '<', '=', '<', ' '},
    {'>', '>', ' ', '>', ' ', '>'},
    {'>', '>', ' ', '>', ' ', '>'},
    {'<', '<', '<', ' ', '<', '='}
};
char terminals[] = "+*()i$";

int indexOf(char c)
{
    for (int i = 0; i < 6; i++)
        if (terminals[i] == c) return i;
    return -1;
}

void show(const char *action)
{
    printf("Stack: ");
    for (int i = 0; i <= top; i++) printf("%c", stack[i]);
    printf("   %s\n", action);
}

int topTerminal()
{
    int t = top;
    while (t >= 0 && stack[t] == 'E') t--;
    return t;
}

int main()
{
    char input[100];
    printf("Enter expression using i for identifier: ");
    scanf("%s", input);
    strcat(input, "$");
    stack[++top] = '$';
    int ip = 0;

    while (1)
    {
        int t = topTerminal();
        char a = stack[t], b = input[ip];

        if (a == '$' && b == '$')
        {
            if (top == 1 && stack[1] == 'E') printf("String Accepted\n");
            else                              printf("String Rejected\n");
            break;
        }

        int x = indexOf(a), y = indexOf(b);
        if (x == -1 || y == -1 || precedence[x][y] == ' ')
        {
            printf("String Rejected\n");
            break;
        }

        if (precedence[x][y] == '<' || precedence[x][y] == '=')
        {
            stack[++top] = b;
            ip++;
            show("Shift");
        }
        else
        {
            int cur = t, below;
            while (1)
            {
                below = cur - 1;
                while (below >= 0 && stack[below] == 'E') below--;
                if (below < 0) { printf("String Rejected\n"); return 0; }
                if (precedence[indexOf(stack[below])][indexOf(stack[cur])] == '<')
                    break;
                cur = below;
            }
            char handle[100];
            int len = top - below;
            strncpy(handle, stack + below + 1, len);
            handle[len] = '\0';

            if (!strcmp(handle, "i")   || !strcmp(handle, "E+E") ||
                !strcmp(handle, "E*E") || !strcmp(handle, "(E)"))
            {
                top = below;
                stack[++top] = 'E';
                show("Reduce");
            }
            else
            {
                printf("String Rejected\n");
                break;
            }
        }
    }
    return 0;
}
