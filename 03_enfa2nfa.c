#include <stdio.h>
#define MAX 20

int n, symbols, eps[MAX][MAX], trans[MAX][MAX][MAX];
int closure[MAX][MAX], visited[MAX];

void dfs(int state)
{
    visited[state] = 1;
    for (int i = 0; i < n; i++)
        if (eps[state][i] && !visited[i])
            dfs(i);
}

void findClosure()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++) visited[j] = 0;
        dfs(i);
        for (int j = 0; j < n; j++) closure[i][j] = visited[j];
    }
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);
    printf("Enter number of input symbols: ");
    scanf("%d", &symbols);

    printf("Enter epsilon transition matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &eps[i][j]);

    printf("Enter transitions for each symbol (0/1 matrix):\n");
    for (int s = 0; s < symbols; s++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                scanf("%d", &trans[s][i][j]);

    findClosure();

    printf("\nEpsilon-free NFA transitions:\n");
    for (int i = 0; i < n; i++)
        for (int s = 0; s < symbols; s++)
        {
            int result[MAX] = {0};

            for (int k = 0; k < n; k++)
                if (closure[i][k])
                    for (int j = 0; j < n; j++)
                        if (trans[s][k][j])
                            for (int x = 0; x < n; x++)
                                if (closure[j][x]) result[x] = 1;

            printf("q%d -- symbol%d --> { ", i, s);
            for (int j = 0; j < n; j++)
                if (result[j]) printf("q%d ", j);
            printf("}\n");
        }
    return 0;
}
