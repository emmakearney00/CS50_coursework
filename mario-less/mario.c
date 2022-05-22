#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height; //declare height variable
    do
    {
        height = get_int("Height? "); //prompt user for height
    }
    while (height < 1 || height > 8); // prompt again if outside conditions

    for (int row = 0; height > row; row++) //do inner for loops then skip line for each row until row exceeds height inputted
    {
        for(int space = height - row; space > 0 ; space--) //within a row, print a number of spaces equal to height - row, subtracting one space each time until spaces = 0
            {
                printf(" ");
            }
        for (int hash = 0; hash < row; hash++) //within a row, print hashes until hashes exceed the number of rows, increasing hashes by one each time
            {
                printf ("#");
            }
      printf("\n");
    }
}




