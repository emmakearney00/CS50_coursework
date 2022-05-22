#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    string phrase;
    struct node *next;
}
node;

#define LIST_SIZE 2

bool search(string phrase, node *list);
bool unload(node *list);
void visualizer(node *list);

int main(void)
{
    node *list = NULL; //points to null

    // Add items to list
    for (int i = 0; i < LIST_SIZE; i++)
    {
        string phrase = get_string("Enter a new phrase: ");

        // TODO: add phrase to new node in list
        node *new_node = malloc(sizeof(node)); //cannot make a node but a pointer to a node
        if (new_node == NULL)
        {
            return 1;
        }
        new_node -> phrase = phrase;
        new_node -> next = list;
        list = new_node; //list is not a node but a helper pointer

        // Visualize list after adding a node.
        visualizer(list);
    }

    // Search for phrase in list
    string search_phrase = get_string("Phrase to search for: ");
    if (search(search_phrase, list))
    {
        printf("Recognized the phrase.\n");
    }
    else
    {
        printf("Did not recognize the phrase.\n");
    }

    // Free all memory used
    if (!unload(list))
    {
        printf("Error freeing the list.\n");
        return 1;
    }

    printf("Freed the list.\n");
    return 0;
}

bool search(string phrase, node *list)
{
    // TODO: Search linked list for phrase
    while (list != NULL)
    {
        if (strcmp(phrase, list -> phrase) == 0) //compare phrase that list points to with the list
        {
            return true;
        }
        list = list -> next; //if not true, update list to next pointer to check next node 
    }

    return false;
}

bool unload(node *list)
{
    // TODO: Free all allocated nodes
    return false;
}

void visualizer(node *list)
{
    printf("\n+-- List Visualizer --+\n\n");
    while (list != NULL)
    {
        printf("Location %p\nPhrase: \"%s\"\nNext: %p\n\n", list, list->phrase, list->next);
        list = list->next;
    }
    printf("+---------------------+\n\n");
}