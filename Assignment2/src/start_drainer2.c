/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 start_drainer2.c
 * 10/12/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer2.h"

void* start_drainer2(void *input)
{
    struct s_threadArgs args;
    FILE* outStream;
    char* line;
    int quit;
    int n;
    int m;

    args = *((struct s_threadArgs*)input);
#ifdef DEBUG
    printf("[DEBUG]\t[drainer]\targs.waitTime: %d\n", args.waitTime);
    fflush(stdout);
#endif

    if ((outStream = fopen(args.fileName, "w")) == NULL)
        printError("[drainer]\tcould not open output file");

    line= NULL;
    quit = 0;
    while (!quit)
    {
        /* wait */
        usleep(args.waitTime);

        /* decrement items by 1 */
        if (sem_wait(&gl_sem_items) == -1)
            printError("[drainer]\tcould not decrement items semaphore");

        /* make sure line has enough space */
        m = cbuf_data_is_available();
        line = realloc(line, m*sizeof(char));

        /* lock the mutex semaphore */
        if (sem_wait(&gl_sem_mutex) == -1)
            printError("[drainer]\tcould not lock semaphore");

        /* read line from cbuf */
        if ((n = cbuf_copy_out(line)))
            printf("drain thread: read [%s] from buffer (nread=%d)\n",
                    line,
                    n);
        else
            printError("[drainer]\tcould not read from buffer");

        /* unlock the mutex semaphore */
        if (sem_post(&gl_sem_mutex) == -1)
            printError("[drainer]\tcould not unlock semaphore");

        /* increment spaces by size of line */
        for (m = 0; m < n; m++)
            if (sem_post(&gl_sem_spaces) == -1)
                printError("[drainer]\tcould not increment spaces semaphore");

        /* check for quitWord */
        if (!strcmp(line, quitWord))
        {
#ifdef DEBUG
            printDebug("[drainer]\tquitting...");
#endif
            quit = 1;
        }
        else
        {
            /* write to file */
            if (n != fwrite(line, 1, n, outStream))
                printError("[drainer]\tcould not write to output file");
        }
    }
    free(line);
    fclose(outStream);

    return 0;
}
