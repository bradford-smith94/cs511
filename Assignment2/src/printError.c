/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 printError.c
 * 10/07/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "utils.h"

/* pre: takes in a char* message
 * post: prints out message with error text flushes standard out (just to be
 *      sure) and then exits with -1
 */
void printError(char* message)
{
    printf("[ERROR]\t%s\n", message);
    fflush(stdout);
    exit(-1);
}
