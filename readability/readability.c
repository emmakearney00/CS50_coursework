
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
//prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    printf("%s\n", text);

    //count number of letters
    int letters = count_letters(text);
    printf("%i letters\n", letters);

    //count number of words
    int words = count_words(text);
    printf("%i words\n", words);

    //count number of sentences
    int sentences = count_sentences(text);
    printf("%i sentences\n", sentences);

    //average letters and setences per 100 words
    float L = letters * 100.0 / words;
    float S = sentences * 100.0 / words;

    //Coleman-Liau index
    float index1 = 0.0588 * L - 0.296 * S - 15.8 ;
    int index = round(index1);

    //print grade levels
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}


int count_letters(string text)
{
    int letter_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) || islower(text[i])) //if a character is either upper or lower, count it.
        {
            letter_count++;
        }
        else
        {
            continue;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ') //if a character is a space, count it toward word count
        {
            word_count++;
        }
        else
        {
            continue;
        }
    }
    return word_count + 1; //last word will not have a space after it
}

int count_sentences(string text)
{
    int sentence_count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?') //if a character is a ., !, or ?, count as sentence
        {
            sentence_count++;
        }
        else
        {
            continue;
        }
    }
    return sentence_count;
}

