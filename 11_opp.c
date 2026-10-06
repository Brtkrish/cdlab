#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

char precedence[6][6] = {
/*       +    *    (    )    i    $ */
/* + */ {'>', '<', '<', '>', '<', '>'},
/* * */ {'>', '>', '<', '>', '<', '>'},
/* ( */ {'<', '<', '<', '=', '<', ' '},
/* ) */ {'>', '>', ' ', '>', ' ', '>'},
/* i */ {'>', '>', ' ', '>', ' ', '>'},
/* $ */ {'<', '<', '<', ' ', '<', '='}
};

char terminals[] = "+*()i$";

int indexOf(char c)
{
    for (int i = 0; i < 6; i++)
        if (terminals[i] == c) return i;
    return -1;
}

int main()
{
    char input[100];
    printf("Enter expression using i for identifier: ");
    scanf("%s", input);
    strcat(input, "$");

    /* operand/operator adjacency check (e.g. rejects i+*i, (+i), i(i) ) */
    int expectOperand = 1, depth = 0;
    for (int k = 0; input[k] != '$'; k++)
    {
        char c = input[k];
        if (expectOperand && (c == 'i' || c == '(')) { if (c == '(') depth++; }
        else if (!expectOperand && (c == '+' || c == '*')) expectOperand = 1;
        else if (!expectOperand && c == ')' && depth > 0) depth--;
        else { printf("String Rejected\n"); return 0; }
        if (c == 'i' || c == ')') expectOperand = 0;
    }
    if (expectOperand || depth) { printf("String Rejected\n"); return 0; }

    stack[++top] = '$';
    int ip = 0;

    while (1)
    {
        char a = stack[top], b = input[ip];

        if (a == '$' && b == '$')
        {
            printf("String Accepted\n");
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
        }
        else
        {
            char last;
            do
            {
                last = stack[top--];
                if (top < 0) { printf("String Rejected\n"); return 0; }
                a = stack[top];
            } while (precedence[indexOf(a)][indexOf(last)] != '<');
        }
    }
    return 0;
}
