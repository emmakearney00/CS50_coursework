#include <stdio.h>
#include <stdlib.h>

typdef struct node //type def lets us just use "node"
{
    int number;
    struct node *next;
}
node;

int main(void
{
    //List of size
    node *list = NULL;

    //add a number to list
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n -> number = 1
    n -> next = NULL

    //Update list to point to new node
    list = n;

    //Add a number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n -> number = 2;
    n -> next = NULL;
    list -> next = n;

    //add a number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list -> next); //free second node first
        free(list); //free list (first node) last
        return 1;
    }
    n -> number = 3;
    n -> next = NULL;
    list -> next -> next = n;

    //cannot used square bracket notation with linked lists

    //Print numbers
    for (node *tmp = list; tmp != NULL; tmp = tmp -> next) //pointing finger to beginning of node
    {
        printf("%i\n", tmp -> number)
    }

    //Free list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    return 0;
}