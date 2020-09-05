#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    int fileNameCounter = 11;
    char filename[7];
    sprintf(filename, "%03i.jpg", fileNameCounter);
    int n = 100;
    printf("%i\n",n);
    printf("%p\n",&n);
    printf("%s\n", filename);
}