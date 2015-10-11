/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 start_filler.c
 * 10/11/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer1.h"

void* start_filler(void *input)
{
    struct s_threadArgs args;
    FILE* inStream;
    size_t size;
    char* line;
    int quit;
    int n;

    args = *((struct s_threadArgs*)input);

    if ((inStream = fopen(args.fileName, "r")) == NULL)
        printError("[filler]\tcould not open input file");

    line= NULL;
    size = 0;
    quit = 0;
    while (!quit)
    {
        /* read line from file */
        n = getline(&line, &size, inStream);
        if (n <= 0)
        {
#ifdef DEBUG
            printDebug("[filler]\tquitting...");
#endif
            quit = 1;
            line = "QUIT";
        }

        while (cbuf_space_available() < n)
        {
            printf("fill thread: could not write [%s] -- not enough space (%d)\n",
                    line,
                    n);
            usleep(args.waitTime);
        }

        /* lock the semaphore */
        if (sem_wait(&gl_sem) == -1)
            printError("[filler]\tcould not lock semaphore");

        /* write line to cbuf */
        if ((cbuf_copy_in(line)) == n)
            printf("fill thread: wrote [%s] into buffer (nwritten=%d)\n",
                    line,
                    n);
        else
            printError("[filler]\tcould not write to buffer");

        /* unlock the semaphore */
        if (sem_post(&gl_sem) == -1)
            printError("[filler]\tcould not unlock semaphore");
    }
    free(line);

    fclose(inStream);
}
