#include <stdio.h>
#include <ctype.h>
#include <string.h>

int isKeyword(char *s)
{
    char *keywords[] = {"int","float","char","if","else",
                        "for","while","return","void"};
    int n = sizeof(keywords) / sizeof(keywords[0]);

    for (int i = 0; i < n; i++)
        if (strcmp(s, keywords[i]) == 0)
            return 1;
    return 0;
}

int main()
{
    char input[500], token[100];
    int i = 0, j;

    printf("Enter the source code:\n");
    fgets(input, sizeof(input), stdin);

    while (input[i] != '\0')
    {
        if (isspace(input[i]))
            i++;
        else if (isalpha(input[i]) || input[i] == '_')
        {
            j = 0;
            while (isalnum(input[i]) || input[i] == '_')
                token[j++] = input[i++];
            token[j] = '\0';

            if (isKeyword(token))
                printf("%s : KEYWORD\n", token);
            else
                printf("%s : IDENTIFIER\n", token);
        }
        else if (isdigit(input[i]))
        {
            j = 0;
            while (isdigit(input[i]))
                token[j++] = input[i++];
            token[j] = '\0';
            printf("%s : NUMBER\n", token);
        }
        else
        {
            printf("%c : OPERATOR/SYMBOL\n", input[i]);
            i++;
        }
    }
    return 0;
}
