// Implements a dictionary's functionality
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Word count in dictionary
int word_count = 0;

// Choose number of buckets in hash table
const unsigned int N = 'z' * (LENGTH + 1); //max sum of ASCII values is 45 consecutive z's

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int n = hash(word); //hash word
    node *cursor = table[n]; //locate correct linked list

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0) //check if cursor pointing at the same word as word
        {
            return true;
        }
        cursor = cursor->next; //if not the same word, move cursor to next node and repeat
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;
    unsigned int length = strlen(word);
    for (int i = 0; i < length; i++) //goes through each letter in a word
    {
        index = index + tolower(word[i]); //sums up ASCII values of characters in word, max sum is < N - 1
    }
    return index % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); //create file pointer "file"
    if (!file) //check if file is null
    {
        return false;
    }
    char buffer[LENGTH + 1]; //array of characters with size = length of longest word
    while (fscanf(file, "%s", buffer) != EOF) //until reaches end of file
    {
        node *n = malloc(sizeof(node)); //allocate memory for word and pointer
        if (n == NULL) //make sure enough memory exists
        {
            return false;
        }
        strcpy(n->word, buffer); //copy word from buffer into word of node n

        unsigned int code = hash(n->word); //hash takes word as input and index/code for table as output

        if (table[code] == NULL) //if there are no other words in this linked list
        {
            n->next = NULL;
        }
        else
        {
            n->next = table[code]; //point to first word in linked list
        }

        table[code] = n; //make header point to new node as first node in linked list

        word_count++; //count total words in dictionary
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++) //for each linked list located by table[i]
    {
        node *cursor = table[i]; //cursor pointing to head of linked list
        while (cursor != NULL)
        {
            node *tmp = cursor; //tmp points to same place as cursor
            cursor = cursor->next; //move cursor to point to next node
            free(tmp); //free the node tmp points to, without losing track of next node
        }
        if (cursor == NULL && i == N - 1) //if reach last linked list
        {
            return true; 
        }
    }
    return false;
}









