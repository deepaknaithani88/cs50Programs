#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string paragraph = get_string("Text: ");
    int paragraphLength = strlen(paragraph);
    int sentenceCount = 0;
    int wordCount = 0;
    int characterCount = 0;
    for (int i = 0; i < paragraphLength; i++)
    {
        if (paragraph[i] == '.' || paragraph[i] == '!' || paragraph[i] == '?')
        {
            sentenceCount += 1;
            wordCount += 1;
            i += 1;
        }
        else if (paragraph[i] == ' ')
        {
            wordCount += 1;
        }
        else if ((paragraph[i] >= 'a' && paragraph[i] <= 'z') || (paragraph[i] >= 'A' && paragraph[i] <= 'Z'))
        {
            characterCount += 1;
        }
    }

    float letterCountPer100Letters = ((float) characterCount / wordCount) * 100;
    float sentenceCountPer100Letters = ((float) sentenceCount / wordCount) * 100;

    float index = (0.0588 * letterCountPer100Letters) - (0.296 * sentenceCountPer100Letters) - 15.8;

    int roundingindex = index;
    float roundingindexWithPoint5Decimal = roundingindex + 0.50;
    int result = 0;
    if (index >= roundingindexWithPoint5Decimal)
    {
        result = index + 1;
    }
    else
    {
        result = index;
    }
    if (result >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (result <= 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", result);
    }

}