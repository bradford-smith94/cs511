/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 start_filler.c
 * 10/11/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer1.h"
#include "utils.h"

void start_filler(struct s_threadArgs args)
{
    FILE* inStream;
    char* line;
    int quit;

    if ((inStream = fopen(args.fileName, "r")) == NULL)
        printError("[filler]\tcould not open input file");

    quit = 0;
    while (!quit)
    {
        usleep(args.waitTime);

        /* read line from file */

        /* lock the semaphore */
        if (sem_wait(&gl_sem) == -1)
            printError("[filler]\tcould not lock semaphore");

        /* write line to cbuf */

        /* unlock the semaphore */
        if (sem_post(&gl_sem) == -1)
            printError("[filler]\tcould not unlock semaphore");
    }
}
