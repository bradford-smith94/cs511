/* Bradford Smith (bsmith8)
 * CS 511 Assignment 1 printError.c
 * 09/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "primes.h"

/* pre: takes in a char* message
 * post: prints out message with error text and exits with -1
 */
void printError(char* message)
{
    printf("[ERROR]\t%s\n", message);
    fflush(stdout);
    exit(-1);
}
