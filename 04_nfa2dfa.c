#include <stdio.h>
#define MAX 20

int main()
{
    int n, m, trans[MAX][MAX][MAX];
    int dfa[MAX][MAX] = {0};
    int states[MAX][MAX] = {0};
    int count = 1;

    printf("Enter number of NFA states: ");
    scanf("%d", &n);
    printf("Enter number of symbols: ");
    scanf("%d", &m);

    printf("Enter NFA transitions (0/1 matrices):\n");
    for (int s = 0; s < m; s++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &trans[s][i][j]);

    states[0][0] = 1;

    for (int i = 0; i < count; i++)
        for (int s = 0; s < m; s++)
        {
            int newset[MAX] = {0};

            for (int j = 0; j < n; j++)
                if (states[i][j])
                    for (int k = 0; k < n; k++)
                        if (trans[s][j][k]) newset[k] = 1;

            int found = -1;

            for (int k = 0; k < count; k++)
            {
                int same = 1;
                for (int j = 0; j < n; j++)
                    if (states[k][j] != newset[j]) same = 0;
                if (same) { found = k; break; }
            }

            if (found == -1)
            {
                found = count++;
                for (int j = 0; j < n; j++)
                    states[found][j] = newset[j];
            }
            dfa[i][s] = found;
        }

    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < count; i++)
    {
        printf("D%d = { ", i);
        for (int j = 0; j < n; j++)
            if (states[i][j]) printf("q%d ", j);
        printf("}\n");

        for (int s = 0; s < m; s++)
            printf("  symbol%d -> D%d\n", s, dfa[i][s]);
    }
    return 0;
}
