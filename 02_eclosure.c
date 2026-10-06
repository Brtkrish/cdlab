#include <stdio.h>

int n, epsilon[20][20], visited[20];

void dfs(int state)
{
    visited[state] = 1;
    for (int i = 0; i < n; i++)
        if (epsilon[state][i] && !visited[i])
            dfs(i);
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &epsilon[i][j]);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            visited[j] = 0;

        dfs(i);

        printf("E-closure(q%d) = { ", i);
        for (int j = 0; j < n; j++)
            if (visited[j])
                printf("q%d ", j);
        printf("}\n");
    }
    return 0;
}
