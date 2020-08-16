#include <cs50.h>
#include <stdio.h>

string getCardName(long lastNumber, long evenLastNumber, long oddLastNumber);

int main(void)
{
    long cardNumber = get_long("Number:");

    long numberMultiplier = 100;
    long evenNumberMultiplier = 100;
    long oddNumberMultiplier = 10;
    long evenSummedNumber = 0;
    long oddSummedNumber = 0;
    long evenLastNumber = 0;
    long oddLastNumber = 0;
    long multiplier = 10;
    long cardLength = 0;
    long lastNumber = 0;
    long cardNumber1 = cardNumber;

    for (int i = 0; i < 18; i++)
    {
        long remainder = cardNumber1 % multiplier;
        if (remainder > 0)
        {
            cardLength = i + 1;
            lastNumber = remainder;
        }
        cardNumber1 /= 10;
        multiplier *= 10;
    }

    for (int i = 0; i < cardLength / 2; i++)
    {
        evenLastNumber = ((((cardNumber % evenNumberMultiplier) - (cardNumber % oddNumberMultiplier)) / oddNumberMultiplier));
        long temp = evenLastNumber * 2;
        evenSummedNumber += temp % 10;
        if (temp > 9)
        {
            evenSummedNumber += 1;
        }
        evenNumberMultiplier *= numberMultiplier;
        oddNumberMultiplier *= numberMultiplier;
    }
    evenNumberMultiplier = 10;
    oddNumberMultiplier = 1;
    for (int i = 0; i < (cardLength + 1) / 2; i++)
    {
        oddLastNumber = ((((cardNumber % evenNumberMultiplier) - (cardNumber % oddNumberMultiplier)) / oddNumberMultiplier));
        oddSummedNumber += oddLastNumber;
        evenNumberMultiplier *= numberMultiplier;
        oddNumberMultiplier *= numberMultiplier;
    }

    if ((oddSummedNumber + evenSummedNumber) % 10 == 0 && cardLength >= 13)
    {
        printf("%s", getCardName(lastNumber, evenLastNumber, oddLastNumber));
    }
    else
    {
        printf("%s", getCardName(0, 0, 0));
    }
}

string getCardName(long lastNumber, long evenLastNumber, long oddLastNumber)
{
    if (lastNumber == evenLastNumber && lastNumber == oddLastNumber)
    {
        lastNumber = (evenLastNumber * 10) + oddLastNumber;
    }
    else if (lastNumber == evenLastNumber)
    {
        lastNumber = (evenLastNumber * 10) + oddLastNumber;
    }
    else if (lastNumber == oddLastNumber)
    {
        lastNumber = (oddLastNumber * 10) + evenLastNumber;
    }
    if (lastNumber == 34 || lastNumber == 37)
    {
        return "AMEX\n";
    }
    else if (lastNumber == 51 || lastNumber == 52 || lastNumber == 53 || lastNumber == 54 || lastNumber == 55)
    {
        return "MASTERCARD\n";
    }
    else if (((lastNumber % 100) - (lastNumber % 10)) / 10 == 4)
    {
        return "VISA\n";
    }
    return "INVALID\n";
}
