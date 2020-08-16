#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    int keyLength = strlen(argv[1]);
    if (keyLength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    string key = argv[1];

    char smallCase[keyLength];
    char upperCase[keyLength];

    for (int i = 0; i < keyLength; i++)
    {
        int characterCount = 0;
        for (int j = 0; j < keyLength; j++)
        {
            if (tolower(key[i]) == tolower(key[j]))
            {
                characterCount += 1;
            }
            if (characterCount > 1)
            {
                printf("Character %c is repeated in your key.\n", key[i]);
                return 1;
            }
        }
        if (islower(key[i]) || isupper(key[i]))
        {

            smallCase[i] = tolower(key[i]);
            upperCase[i] = toupper(key[i]);
        }
        else
        {
            printf("You have entered character %c other than alphabet.\n", key[i]);
            return 1;
        }
    }
    string message = get_string("plaintext: ");

    int messageLength = strlen(message);
    printf("ciphertext: ");
    for (int i = 0; i < messageLength; i++)
    {
        if (islower(message[i]))
        {
            int c = (int) message[i];
            int index = c - 97;
            printf("%c", smallCase[index]);
        }
        else if (isupper(message[i]))
        {
            int c = (int) message[i];
            int index = c - 65;
            printf("%c", upperCase[index]);
        }
        else
        {
            printf("%c", message[i]);
        }
    }
    printf("\n");
    return 0;
}