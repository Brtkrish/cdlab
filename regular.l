%{
#include <stdio.h>
%}

%%
0*1*    {
            int zeros = 0, ones = 0;
            for (int i = 0; i < yyleng; i++)
            {
                if (yytext[i] == '0') zeros++;
                else ones++;
            }
            if (zeros == ones && zeros > 0)
                printf("Accepted: 0^%d 1^%d\n", zeros, ones);
            else
                printf("Rejected: number of 0s and 1s is not equal\n");
        }
.*      { printf("Rejected: not of the form 0^n 1^n\n"); }
%%

int yywrap() { return 1; }

int main()
{
    printf("Enter a string of 0s and 1s: ");
    yylex();
    return 0;
}
