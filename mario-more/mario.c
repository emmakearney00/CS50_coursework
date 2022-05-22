#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //declare height
    int height;
    do
    {
        //ask for height
        height = get_int("What height? ");
    }
    //ask for height again if conditions not met
    while(height < 1 | height > 8);

}
printf(" /n)


