/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 rw.c
 * 10/12/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "rw.h"
#include "utils.h"

#define usage "[usage]\t./rw <input file> <output file>"

/* pre: takes in int argc and char** argv command line arguments
 * post: runs the rw program
 */
int main(int argc, char** argv)
{
    FILE* inStream;
    FILE* outStream;
    size_t size;
    char* inFile;
    char* outFile;
    char* line;
    int n;

    if (argc != 3)
    {
        printf("%s\n", usage);
        exit(0);
    }

    inFile = argv[1];
    outFile = argv[2];

    if ((inStream = fopen(inFile, "r")) == NULL)
        printError("could not open input file");
    if ((outStream = fopen(outFile, "w")) == NULL)
        printError("could not open output file");

    line = NULL;
    size = 0;
    while ((n = getline(&line, &size, inStream)) != -1)
    {
        /* write line to output file here */
        fwrite(line, 1, n, outStream);
    }
    free(line);

    if (errno)
        printError("getline failed!");

    fclose(inStream);
    fclose(outStream);

    return 0;
}
