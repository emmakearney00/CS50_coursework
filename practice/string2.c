#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string test = get_string("String: ");
    int length = strlen(test);

    for (int i = 0; i < length - 1; i++)
    {
        if(test[i] > test[i + 1]) //not in alphabetical order
        {
            printf("No.\n");
            return 0;
        }
    }
    printf("Yes.\n");
    return 0;
}