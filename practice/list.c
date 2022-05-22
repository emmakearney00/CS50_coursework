#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //dynamically allocate array of size 3
    int *list = malloc(3 * sizeof(int)); //creating array of size three putting it on heap
    if (list == NULL)
    {
        return 1;
    }
    //can treat like an array and find memory
    list[0] = 1; // *list = 1 is same thing
    list[1] = 2; //*(list + 1) = 2
    list[2] = 3;

    //time passes.. add a number 4?

    //Resize old array to be of size 4
    int *tmp = realloc(list, 4 * sizeof(int)); //grows array for you or moves the location, automatically frees old list 
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }

    //add fourth number
    tmp[3] = 4;

    //free old array
    free(list); //freeing chunk of memory that begins at address in list, not freeing variable per say so can use in line below

    list = tmp; //pointing at new chunk of memory, //when you free list, same thing as freeing tmp

    for (int i = 0; i < 4; i++)
    {
        printf("%i\n", list[i]);
    }

    free(list); //free new list before ending
    return 0;
}