#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for(int i = 0; i < candidate_count; i++) //iterate over all candidates
    {
        if (strcmp(name, candidates[i].name) == 0) //if name voted matches a candidates name
        {
            candidates[i].votes++; //add vote to that candidates vote count
            return true;
        }
    }
    return false; //return false if does not match any candidates names
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int win_votes = 0; //the winning number of votes starts at 0
    for (int i = 0; i < candidate_count; i++) //iterate over all candidates
    {
        if (candidates[i].votes > win_votes) //if a candidates votes are greater than the winning number of votes, then
        {
            win_votes = candidates[i].votes; //set that candidates votes to the 'new' winning number of votes
        }
    }

    for (int i = 0; i < candidate_count; i++) //iterate over all candidates
    {
        if (candidates[i].votes == win_votes) //if a candidates votes matches the winning number of votes, then
        {
            printf("%s\n", candidates[i].name); //print that candidates name
        }
    }
    return;
}

