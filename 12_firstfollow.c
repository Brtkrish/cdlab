#include <stdio.h>
#include <string.h>
#include <ctype.h>

char productions[10][20];
char first[26][20], follow[26][20];
int n;

void add(char *set, char c)
{
    if (!strchr(set, c))
    {
        int len = strlen(set);
        set[len] = c;
        set[len + 1] = '\0';
    }
}

void FIRST(char c, char *result)
{
    if (!isupper(c))
    {
        add(result, c);
        return;
    }

    for (int i = 0; i < n; i++)
        if (productions[i][0] == c)
        {
            char x = productions[i][3];
            if (x == '#') add(result, '#');
            else FIRST(x, result);
        }
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Use # for epsilon. Example: E=TA\n");
    for (int i = 0; i < n; i++)
        scanf("%s", productions[i]);

    printf("\nFIRST:\n");
    for (int i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        if (first[nt-'A'][0] == '\0')
            FIRST(nt, first[nt-'A']);

        printf("FIRST(%c) = { ", nt);
        for (int j = 0; j < strlen(first[nt-'A']); j++)
            printf("%c ", first[nt-'A'][j]);
        printf("}\n");
    }

    add(follow[productions[0][0]-'A'], '$');

    for (int p = 0; p < n; p++)
    {
        char lhs = productions[p][0];

        for (int i = 3; i < strlen(productions[p]); i++)
        {
            char B = productions[p][i];

            if (isupper(B))
            {
                if (i + 1 < strlen(productions[p]))
                {
                    char next = productions[p][i+1];
                    if (!isupper(next))
                        add(follow[B-'A'], next);
                }
                else
                    for (int j = 0; j < strlen(follow[lhs-'A']); j++)
                        add(follow[B-'A'], follow[lhs-'A'][j]);
            }
        }
    }

    printf("\nFOLLOW:\n");
    for (int i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        printf("FOLLOW(%c) = { ", nt);
        for (int j = 0; j < strlen(follow[nt-'A']); j++)
            printf("%c ", follow[nt-'A'][j]);
        printf("}\n");
    }
    return 0;
}
