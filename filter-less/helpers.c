#include "helpers.h"
#include <math.h>
#include <stdio.h>

int min(int a, int b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //calculate average colors
            avg = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed)/3.0);
            //reassign pixel colors
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            //calculate average colors
            int sepiaRed = min(round(.393 * image[i][j].rgbtRed  + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue), 255);
            int sepiaGreen = min(round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue), 255);
            int sepiaBlue = min(round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue), 255);

            //reassign pixel colors
            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i;
    int j;
    for(i = 0; i < height; i++) //for every row
    {
        for(j = 0; j < round(width/2.0); j++) //for first half of pixels in row
            {
                RGBTRIPLE tmp = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = tmp;
            }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //initialize counters
    RGBTRIPLE copy[height][width];
    float new_red = 0;
    float new_green = 0;
    float new_blue = 0;

    //copy over image pixels to copy
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
            {
                copy[i][j] = image[i][j];
            }
    }

    //search for surrounding pixels
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int counter = 0; //count of surrounding pixels

            for(int h = (i - 1); h < (i + 2); h++) //for each height and width position, determine if surrounding blocks exist in 3X3 box
            {
                for(int w = (j - 1); w < (j + 2); w++)
                {
                    if (w < 0 || w > (width - 1) || h < 0 || h > (height - 1))
                    {
                        continue;
                    }
                    new_red = new_red + copy[h][w].rgbtRed; //sum red content of surrounding blocks
                    new_green = new_green + copy[h][w].rgbtGreen;  //sum green content of surrounding blocks
                    new_blue = new_blue + copy[h][w].rgbtBlue;  //sum blue content of surrounding blocks
                    counter++ ; //count number of surrounding blocks
                }
            }
            image[i][j].rgbtRed = round(new_red / counter);
            image[i][j].rgbtGreen = round(new_green / counter);
            image[i][j].rgbtBlue = round(new_blue / counter);
        }
    }

    return;
}

//define min function used in sepia
int min(int a, int b)
{
    if (b < a)
    {
        return b;
    }
    return a;
}

