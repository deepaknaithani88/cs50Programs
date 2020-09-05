#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    BYTE buffer[512];
    FILE *fr;
    fr = fopen(argv[1], "r");
    int fileNameCounter = 0;
    bool jpegFileStarted = false;
    bool firstTimeFileRead = true;
    int readSize = 0;
    FILE *fo;
    char filename[7];

    do
    {
        readSize = fread(&buffer, sizeof(char), 512, fr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (firstTimeFileRead)
            {
                firstTimeFileRead = false;
            }
            else
            {
                // Close outfile
                fclose(fo);
            }
            jpegFileStarted = true;
            sprintf(filename, "output/%03i.jpg", fileNameCounter);
            fileNameCounter += 1;

            fo = fopen(filename, "w");
        }
        if (jpegFileStarted)
        {
            fwrite(&buffer, sizeof(char), readSize, fo);
        }
    }
    while (readSize == 512);

    // Close infile
    fclose(fr);

}
