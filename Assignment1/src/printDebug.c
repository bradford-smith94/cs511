/* Bradford Smith (bsmith8)
 * CS 511 Assignment 1 printDebug.c
 * 09/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "primes.h"

/* pre: takes in char* message
 * post: prints out message with debug text
 */
void printDebug(char* message)
{
    printf("[DEBUG]\t%s\n", message);
    fflush(stdout);
}
