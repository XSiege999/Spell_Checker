// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"
int size_of_dict = 0; //Declare a global variable to keep a track of words in the dictionary

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;  //what about apostrophes eg: "What?!", she screamed.

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    for (node *tmp = table[index]; tmp != NULL; tmp = tmp->next)
    {
        int i = strcasecmp(word, (tmp->word));
        if (i == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Check isalpha to the character otherwise, go to the next character(?)
    char ch = tolower(word[0]);
    unsigned int key;
    key = (ch - 97);
    return key;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Open the file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    //Set all values of every array-element of hash table to NULL
    for (int p = 0; p < N; p++)
    {
        table[p] = NULL;
    }

    //Declare the placeholder "word" variable
    char dict_word[LENGTH + 1];

    //Iterate through for every word in the dictionary
    while (fscanf(file, "%s", dict_word) != EOF)
    {
        node *entry = malloc(sizeof(node));
        if (entry == NULL)
        {
            return false;
        }
        strcpy(entry->word, dict_word);

        int index = hash(dict_word);

        if (table[index] == NULL)
        {

            entry->next = NULL;
            table[index] = entry;
        }
        else
        {
            entry->next = table[index]; //new element points to the old head of the linked list
            table[index] = entry; //new head of the linked list
        }
        size_of_dict += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (size_of_dict > 0)
    {
        return size_of_dict;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp1 = table[i];
        while (tmp1 != NULL)
        {
            node *tmp2 = tmp1;
            tmp1 = tmp1->next;
            free(tmp2);
        }
    }
    return true;
}
