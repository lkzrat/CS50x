// Implements a dictionary's functionality

#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 100;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Setting pointer to search
    node *ptr = table[hash(word)];

    // Searching word
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int points = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        points += tolower(word[i]) - 97;
    }

    points = points % N;

    return points;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Opening dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // Setting word
    char w[LENGTH + 1];

    while (fscanf(dict, "%s", w) != EOF)
    {
        // Creates new node
        node *ptr = malloc(sizeof(node));
        if (ptr == NULL)
        {
            return false;
        }

        // Copys the word into node->word
        strcpy(ptr->word, w);

        ptr->next = NULL;

        // Puts a new node with a word in the table
        int i = hash(w);

        if (table[i] == NULL)
        {
            table[i] = ptr;
        }
        else
        {
            ptr->next = table[i];
            table[i] = ptr;
        }
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Set the word counter
    int counter = 0;

    // Scans the tabel array
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            counter++;
            ptr = ptr->next;
        }
    }

    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *ptr = table[i]->next;
            free(table[i]);
            table[i] = ptr;
        }
    }
    return true;
}
