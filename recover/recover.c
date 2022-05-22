#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512
#define FILENAME_SIZE 8

typedef uint8_t BYTE;

int main(int argc, char *argv[])
//return error if argument count not equal to 2
{
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    //Open memory card
    FILE *input = fopen(argv[1], "r");

    //check if file valid
    if (!input)
    {
        printf("File could not be opened\n");
        return 1;
    }

    //allocate memory for buffer and names of files
    BYTE buffer[BLOCK_SIZE];
    char filename[FILENAME_SIZE];
    int counter = 0;
    FILE *output = NULL;
    bool first_jpg = false;
    bool found_jpg = false;

    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE) //repeat until end of card
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) //start of new jpeg
        {
            found_jpg = true;
            if (!first_jpg) //first jpeg
            {
                sprintf(filename, "%03i.jpg", counter++);
                output = fopen(filename, "w");
                fwrite(buffer, BLOCK_SIZE, 1, output);
            }
            else
            {
                fclose(input); //close current file
                sprintf(filename, "%03i.jpg", counter); //make a new jpg
                output = fopen(filename, "w"); //make a new jpg
                counter++;
            }
        }
        else
        {
            if (found_jpg) //already found jpeg
            {
                fwrite(buffer, 1, BLOCK_SIZE, input);
            }
        }

    }

//close all open files
    fclose(newfile)


}

