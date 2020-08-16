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

// set maximum voter counter while giving votes
int maxVoteCounter;

// Function prototypes
bool vote(string name);
void print_winner(void);
void sortCandidatesByName();

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

    // merge sort
    sortCandidatesByName();

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
    if (strcmp(name, "") == 0)
    {
        return false;
    }
    string result = "";
	int minIndex = 0;
	int maxIndex = candidate_count - 1;
	int mid = 0;
	do
    {
        mid = ((maxIndex - minIndex) / 2);

        if ((minIndex + 1) == (candidate_count - 1)) {
            mid = 1;
        }

        int compare = strcmp(candidates[minIndex + mid].name, name);
        if (compare < 0)
        {
            // modify min index
            minIndex = minIndex + mid;
        }
        else if (compare > 0)
        {
            // modify max index
            maxIndex = maxIndex - mid;
        }
        else if (compare == 0)
        {
            result = name;
            candidates[minIndex + mid].votes += 1;
            if (maxVoteCounter < candidates[minIndex + mid].votes)
            {
                maxVoteCounter = candidates[minIndex + mid].votes;
            }
        }
    } while (strcmp(result, name) != 0 && minIndex != maxIndex);
    if (strcmp(result, name) == 0)
    {
        return true;
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int maxVoteCounterl = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (maxVoteCounterl < candidates[i].votes)
        {
            maxVoteCounterl = candidates[i].votes;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (maxVoteCounterl == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}

void sortCandidatesByName()
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count - i - 1; j++)
        {
            int compare = strcmp(candidates[j].name, candidates[j + 1].name);
            candidate temp;
            if (compare > 0)
            {
                temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }
}
