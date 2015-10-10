/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 printDebug.c
 * 10/07/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "utils.h"

/* pre: takes in a char* message
 * post: prints out message with debug text and flushes standard out to make
 *      sure the message is seen when intended
 */
void printDebug(char* message)
{
    printf("[DEBUG]\t%s\n", message);
    fflush(stdout);
}
