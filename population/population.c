#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //Create an integer start_size that holds start size
    int start_size;
    do
    {
        start_size = get_int("What's the start size? ");
    }
    while (start size < 9)

    //Create an integer end_size that holds end size
    int end_size;
    do
    {
        end_size = get_int("End size? ");
    }
    while (end_size < start_size);

    // Create integer years that holds number of years
    int years = 0;

    // TODO: Calculate number of years until we reach start_size = end_size
        //Run a loop that depends on the start_size in relation to the end_size
    while (start_size < end_size)
    {
        start_size = start_size + (round(start_size) / 3) - (round(start_size) / 4);
        years++;
    }
    //print number of years
    printf("The number of years is %i\n", years);
}
