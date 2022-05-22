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
    candidate new_candidate = get_candidate("Enter a candidate");
    printf("Candidate' name is %s, and candidate's probability is %f\n", new_candidate.name, new_candidate.win);
}

candidate get_candidate(string prompt)
{
    candidate new_candidate;
    printf("%s\n", prompt);
    new_candidate.name = get_string("What is the candidate's name? ");
    new_candidate.win = get_float("What is the candidate's probability of winning? ");
    return new_candidate;
}
