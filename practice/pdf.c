#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    // Check for usage
    if (argc != 2)
    {
        printf("Improper usage.\n");
        return 1;
    }

    // Open file
    FILE *pdf = fopen(argv[1], "r");

    if (pdf == NULL)
    {
        printf("Could not find file.\n");
        return 1;
    }
    printf("%p\n", pdf);

    uint8_t buffer[4];

    fread(buffer, 1, 4, pdf);

    uint8_t sig[] = {0x25, 0x50, 0x44, 0x46};

    for (int i = 0; i < sizeof(int); i++)
    {
        if (buffer[i] != sig[i])
        {
            printf("buffer is not a pdf.\n");
            return 1;
        }
    }
    printf("buffer is a pdf.\n");

}