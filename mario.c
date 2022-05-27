# include <stdio.h>
# include <cs50.h>

int main(void)
{
    int n, i, j, k, l;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (i = 1; i <= n; i++)
    {
        for (j = n - i; j > 0; j--)
        {
            printf(" ");
        }
        
        for (k = 1; k < i + 1; k++)
        {
            printf("#");
        }
      
        
        {
            printf("  ");
        }
        for (l = 1; l < i + 1; l++)
        {
            printf("#");
        }       
        printf("\n");
    }
    
}
