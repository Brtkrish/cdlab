#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[20][20];          /* prod[i] = "E=TA", '#' is epsilon */
char first[26][30], follow[26][30];
int n, changed;

int add(char *set, char c)
{
    if (strchr(set, c)) return 0;
    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
    changed = 1;
    return 1;
}

/* add FIRST of string s to set; return 1 if whole string can derive epsilon */
int firstOfString(char *s, char *set)
{
    for (int i = 0; s[i]; i++)
    {
        char c = s[i];
        if (!isupper(c))
        {
            if (c != '#') add(set, c);
            return c == '#';
        }
        int eps = 0;
        for (int j = 0; first[c - 'A'][j]; j++)
        {
            if (first[c - 'A'][j] == '#') eps = 1;
            else add(set, first[c - 'A'][j]);
        }
        if (!eps) return 0;
    }
    return 1;
}

void printSet(char *name, char nt, char *set)
{
    printf("%s(%c) = { ", name, nt);
    for (int i = 0; set[i]; i++) printf("%c ", set[i]);
    printf("}\n");
}

int main()
{
    char order[26], seen[26] = {0};
    int count = 0;

    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Use # for epsilon. Example: E=TA\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", prod[i]);
        int k = prod[i][0] - 'A';
        if (!seen[k]) { seen[k] = 1; order[count++] = prod[i][0]; }
    }

    /* FIRST */
    do {
        changed = 0;
        for (int i = 0; i < n; i++)
            if (firstOfString(prod[i] + 2, first[prod[i][0] - 'A']))
                add(first[prod[i][0] - 'A'], '#');
    } while (changed);

    /* FOLLOW */
    add(follow[prod[0][0] - 'A'], '$');
    do {
        changed = 0;
        for (int p = 0; p < n; p++)
        {
            char lhs = prod[p][0];
            char *rhs = prod[p] + 2;
            for (int i = 0; rhs[i]; i++)
            {
                if (!isupper(rhs[i])) continue;
                char B = rhs[i];
                char tmp[30] = "";
                int saved = changed;
                int eps = firstOfString(rhs + i + 1, tmp);
                changed = saved;   /* tmp is scratch, not a real change */
                for (int j = 0; tmp[j]; j++) add(follow[B - 'A'], tmp[j]);
                if (eps)
                    for (int j = 0; follow[lhs - 'A'][j]; j++)
                        add(follow[B - 'A'], follow[lhs - 'A'][j]);
            }
        }
    } while (changed);

    printf("\nFIRST:\n");
    for (int i = 0; i < count; i++) printSet("FIRST", order[i], first[order[i] - 'A']);
    printf("\nFOLLOW:\n");
    for (int i = 0; i < count; i++) printSet("FOLLOW", order[i], follow[order[i] - 'A']);
    return 0;
}
