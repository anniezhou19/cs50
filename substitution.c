#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0, len_a = strlen(argv[1]); i < len_a; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
        for (int j = i + 1; j < len_a; j++)
        {
            if (toupper(argv[1][j]) == toupper(argv[1][i]))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
    }
    
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");
    
    for (int i = 0, len_p = strlen(plaintext); i < len_p; i++)
    {
        if islower(plaintext[i])
        {
            int index_s = plaintext[i] - 'a';
            printf("%c", tolower(argv[1][index_s]));
        }
        else if isupper(plaintext[i])
        {
            int index_b = plaintext[i] - 'A';
            printf("%c", toupper(argv[1][index_b]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");
    return 0;
}
© 2022 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
