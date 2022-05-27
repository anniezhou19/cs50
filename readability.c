#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int index(string text);

int main(void)
{
    string text = get_string("Text: ");
    int grade = index(text);
   
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int index(string text)
{
    int letter = 0;
    int word = 1;
    int sentence = 0;
   
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (isalpha(text[i]))
        {
            letter++;
        }
        if (text[i] == ' ')
        {
            word ++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence++;
        }
    }
   
    float index = 0.0588 * (100 * (float)letter / word) - 0.296 * (100 * (float)sentence / word) - 15.8;
    return round(index);
  
}
