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
            do
            {
                top--;
                a = stack[top];
                x = indexOf(a);
            } while (precedence[x][y] != '<');
        }
    }
    return 0;
}
