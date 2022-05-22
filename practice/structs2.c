#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    float win;
}
candidate;

candidate get_candidate(string prompt);

int main(void)
{
    //declare a candidate array
    candidate candidates[3];
    bool found;

    //Add candidates to an array
    for (int i = 0; i < 3; i++)
    {
        candidates[i] = get_candidate("Enter a candidate ");
    }
    //Print candidates once done
    for (int i = 0; i < 3; i++)
    {
        if(candidates[i].win >= .51)
        {
            printf("%f", candidates[i].win);
            break; //continues program but stops loop
        }
    }
    if (found == false)
    {
        printf("Not found.");
    }

}

candidate get_candidate(string prompt)
{
    candidate candidates;
    candidates.name = get_string("What is the candidate's name? ");
    candidates.win = get_float("What is the candidate's probability of winning? ");
    return candidates;
}





