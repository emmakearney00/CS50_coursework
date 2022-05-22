#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2) //case where player 1 has a higher score
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2) //case where player 1 has a higher score
    {
        printf("Player 2 wins!\n");
    }
    else //if neither player 1 or 2 have higher score, must be tie
    {
        printf("Tie!\n");
    }

}

int compute_score(string word)
{
    int score = 0;
    int current_index;
    for (int i = 0, n = strlen(word); i < n; i++) //loop that examines each character of the string
    {
        if (tolower(word[i]) < 'a' || tolower(word[i]) > 'z') //convert to lowercase to check if not a letter
        {
            continue; //skip to next character if not a letter
        }
        else
        {
            current_index = tolower(word[i]) - 'a'; //convert to lower and standardize to match 0, 1, 2... index of POINTS
            score += POINTS[current_index]; //index to find value in points and add to score
        }
    }
    return score;
}

