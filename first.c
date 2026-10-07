#include <stdio.h>
#include <string.h>
#include <ctype.h>

char productions[20][20];
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
    if (!isupper(c)) { add(result, c); return; }
    for (int i = 0; i < n; i++)
        if (productions[i][0] == c)
        {
            char *rhs = productions[i] + 2;
            if (rhs[0] == '#') { add(result, '#'); continue; }
            int allEps = 1;
            for (int k = 0; rhs[k]; k++)
            {
                char tmp[20] = "";
                FIRST(rhs[k], tmp);
                for (int j = 0; tmp[j]; j++)
                    if (tmp[j] != '#') add(result, tmp[j]);
                if (!strchr(tmp, '#')) { allEps = 0; break; }
            }
            if (allEps) add(result, '#');
        }
}

int firstOfString(char *s, char *out)
{
    for (int k = 0; s[k]; k++)
    {
        char tmp[20] = "";
        FIRST(s[k], tmp);
        for (int j = 0; tmp[j]; j++)
            if (tmp[j] != '#') add(out, tmp[j]);
        if (!strchr(tmp, '#')) return 0;
    }
    return 1;
}

int main()
{
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Use # for epsilon. Example: E=TA\n");
    for (int i = 0; i < n; i++)
        scanf("%s", productions[i]);

    printf("\nFIRST:\n");
    int done[26] = {0};
    for (int i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        if (done[nt - 'A']) continue;
        done[nt - 'A'] = 1;
        FIRST(nt, first[nt - 'A']);
        printf("FIRST(%c) = { ", nt);
        for (int j = 0; first[nt - 'A'][j]; j++)
            printf("%c ", first[nt - 'A'][j]);
        printf("}\n");
    }

    add(follow[productions[0][0] - 'A'], '$');
    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (int p = 0; p < n; p++)
        {
            char lhs = productions[p][0];
            char *rhs = productions[p] + 2;
            for (int i = 0; rhs[i]; i++)
            {
                char B = rhs[i];
                if (!isupper(B)) continue;
                char beta[20] = "";
                strcpy(beta, rhs + i + 1);
                char f[20] = "";
                int nullable = firstOfString(beta, f);
                int before = strlen(follow[B - 'A']);
                for (int j = 0; f[j]; j++) add(follow[B - 'A'], f[j]);
                if (nullable)
                    for (int j = 0; follow[lhs - 'A'][j]; j++)
                        add(follow[B - 'A'], follow[lhs - 'A'][j]);
                if ((int)strlen(follow[B - 'A']) != before) changed = 1;
            }
        }
    }

    printf("\nFOLLOW:\n");
    memset(done, 0, sizeof(done));
    for (int i = 0; i < n; i++)
    {
        char nt = productions[i][0];
        if (done[nt - 'A']) continue;
        done[nt - 'A'] = 1;
        printf("FOLLOW(%c) = { ", nt);
        for (int j = 0; follow[nt - 'A'][j]; j++)
            printf("%c ", follow[nt - 'A'][j]);
        printf("}\n");
    }
    return 0;
}
