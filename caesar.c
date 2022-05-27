#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    for (int i = 0, len = strlen(argv[1]); i < len; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    
    int k = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (islower(plaintext[i]))
        {
            printf("%c", (((plaintext[i] - 'a') + k) % 26) + 'a');
        }
        else if (isupper(plaintext[i]))
        {
            printf("%c", (((plaintext[i] - 'A') + k) % 26) + 'A');
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
