#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    uint8_t buffer[512];
    FILE *fr;
    fr = fopen("card.raw", "r");

    do
    {
        fread(&buffer, sizeof(char), 512, fr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
        }
    }
    while (getc(fr) != EOF)

}
