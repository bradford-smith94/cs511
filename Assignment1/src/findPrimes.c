/* Bradford Smith (bsmith8)
 * CS 511 Assignment 1 findPrimes.c
 * 09/27/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "primes.h"

/* pre: takes in int bottom, int top and a struct s_proc proc
 * post: finds all primes from bottom to top and prints them out on either a
 *      pipe or fifo in proc
 * return: a integer of the number of primes found
 */
int findPrimes(int bottom, int top, struct s_proc proc)
{
    int i;
    int retval;
    char temp[5];

#ifdef DEBUG
    printDebug("[child]\tproc struct:");
    if (proc.flag)
        printf("\tfifo: %s\n", proc.fifoname);
    else
        printf("\tpipe: \n");
#endif

    if (proc.flag)
    {
        if ((proc.fifofd = open(proc.fifoname, O_WRONLY)) == -1)
            printError("[child]\tcouldn't open fifo");
    }
    else
    {
        if (close(proc.pipefd[0]) == -1) /* close the read end of the pipe */
            printError("[child]\tcouldn't close pipe");

    }

    retval = 0;
#ifdef DEBUG
    printf("[DEBUG]\t[child]\tretval is properly set to %d\n", retval);
    fflush(stdout);
#endif

    for (i = bottom; i <= top; i++)
    {
        if (i != 2 && (i % 2 == 0))
            continue;
        else if (i != 3 && (i % 3 == 0))
            continue;
        else if (i != 5 && (i % 5 == 0))
            continue;
        else if (i != 7 && (i % 7 == 0))
            continue;
        else
        {

            /* i is prime */
#ifdef DEBUG
            printf("[DEBUG]\t[child]\tprime:%d\n", i);
            fflush(stdout);
#endif

            sprintf(temp, "%d|", i);
            if (proc.flag)
            {
                /* write to proc.fifoname */
                if (write(proc.fifofd, temp, strlen(temp)) == -1)
                    printError("[child]\tcouldn't write to fifo");
            }
            else
            {
                /* write to proc.pipefd[1] */
                if (write(proc.pipefd[1], temp, strlen(temp)) == -1)
                    printError("[child]\tcouldn't write to pipe");
            }
            retval += 1;
        }
    } /* for */

    if (retval > top - bottom)
        printError("[child]\t can't count");

    if (proc.flag)
    {
        if (close(proc.fifofd) == -1)
            printError("[child]\tcouldn't close fifo");
    }
    else
    {
        if (close(proc.pipefd[1]) == -1)
            printError("[child]\tcouldn't close pipe");
    }

#ifdef DEBUG
    printf("[DEBUG]\t[child]\tfound %d primes\n", retval);
    fflush(stdout);
#endif

    return retval;
}
