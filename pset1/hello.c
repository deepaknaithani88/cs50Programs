#include <cs50.h>
#include <stdio.h>

#define MAX 9

int preferences[MAX][MAX];

int main(void)
{

    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
    int age[] = { 1, 2, 3, 4, 5 , 6};
    string names[] = {"Deepak", "Amit", "Danish", "Manisha"};
    int ageLength = sizeof age / sizeof age[0];
    int nameLength = sizeof names / sizeof names[0];
    printf("%lu\n", (sizeof age));
    printf("%i\n", ageLength);
    printf("%lu\n", (sizeof names));
    printf("%i\n", nameLength);

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
        {
            preferences[i][j] = i + j;
        }
    }

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            printf("%i%s", preferences[i][j], " ");
        }
        printf("\n");
    }
}
