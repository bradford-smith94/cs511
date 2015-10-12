/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 transfer2.c
 * 10/12/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer2.h"
#include "utils.h"

#define usage "[usage]\t ./transfer2 <input file> <output file> <filler wait> <drainer wait>"

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        printf("%s\n", usage);
        exit(0);
    }
}
