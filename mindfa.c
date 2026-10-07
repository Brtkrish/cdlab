#include <stdio.h>

int main()
{
    int n, m, trans[20][10], final[20], group[20];

    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of symbols: ");
    scanf("%d", &m);

    printf("Enter transition table:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);

    printf("Enter 1 for final state, 0 otherwise:\n");
    for (int i = 0; i < n; i++) scanf("%d", &final[i]);

    for (int i = 0; i < n; i++) group[i] = final[i];

    int changed = 1;

    while (changed)
    {
        changed = 0;
        int newgroup[20], groups = 0;

        for (int i = 0; i < n; i++)
        {
            int found = -1;

            for (int j = 0; j < i; j++)
            {
                int same = (group[i] == group[j]);

                if (same)
                    for (int k = 0; k < m; k++)
                        if (group[trans[i][k]] != group[trans[j][k]])
                            same = 0;

                if (same) { found = newgroup[j]; break; }
            }

            if (found == -1) found = groups++;
            newgroup[i] = found;
        }

        for (int i = 0; i < n; i++)
        {
            if (group[i] != newgroup[i]) changed = 1;
            group[i] = newgroup[i];
        }
    }

    printf("\nMinimized DFA groups:\n");
    for (int g = 0; g < n; g++)
    {
        int printed = 0;
        for (int i = 0; i < n; i++)
            if (group[i] == g)
            {
                if (!printed)
                {
                    printf("Group %d: ", g);
                    printed = 1;
                }
                printf("q%d ", i);
            }
        if (printed) printf("\n");
    }
    return 0;
}
