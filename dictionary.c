// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 50000;
int counter = 0;

// Hash table
node *table[N];
bool loaded;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    char checkword[strlen(word)];
    strcpy(checkword, word);
    for (int i = 0; checkword[i] != '\0'; i++)
    {
        checkword[i] = tolower(checkword[i]);
    }
    int index_cursor = hash(checkword);
    node *cursor = table[index_cursor];
    
    if (cursor != NULL)
    {
        if (strcasecmp(cursor->word, checkword) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO _ use djb2 hash function _ written by Daniel J. Bernstein
    unsigned int hash = 5381;

    for (int i = 0; word[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) + *word; /* hash * 33 + *word */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    // Use fopen, remember to check if return value is NULL
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Read Strings from file one at a time
    // Use fscanf(file, "%s", word)
    // fscanf will return EOF once i reaches end of file
    char word[LENGTH + 1];
    while (fscanf(dict, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            free(n);
            return false;
        }
        // Create a new node for each word
        // Use malloc, check if return value is NULL, copy word into node using strcpy
        else
        {
            strcpy(n->word, word);
            n->next = NULL;

            // Hash word to obtain a hash value
            unsigned int index = hash(word);

            // Insertnode into hash table at that location
            node *head = table[index];
            if (head == NULL)
            {
                table[index] = n;
                counter++;
            }
            else
            {
                n->next = table[index];
                table[index] = n;
                counter++;
            }
        }
    }
    fclose(dict);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    if (!loaded)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            node *head = table[i];
            while (head != NULL)
            {
                node *tmp = head;
                head = head->next;
                free(tmp);
            }
        }
    }
    return true;
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
