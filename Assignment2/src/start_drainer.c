/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 start_drainer.c
 * 10/11/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer1.h"

void* start_drainer(void *input)
{
    struct s_threadArgs args;
    FILE* outStream;
    char* line;
    int quit;
    int n;

    args = *((struct s_threadArgs*)input);

    if ((outStream = fopen(args.fileName, "w")) == NULL)
        printError("[drainer]\tcould not open output file");

    line= NULL;
    quit = 0;
    while (!quit)
    {
        while (!cbuf_data_is_available())
        {
            printf("drain thread: no new string in buffer\n");
            usleep(args.waitTime);
        }

        /* lock the semaphore */
        if (sem_wait(&gl_sem) == -1)
            printError("[drainer]\tcould not lock semaphore");

        /* read line from cbuf */
        if ((n = cbuf_copy_out(line)))
            printf("drain thread: read [%s] from buffer (nread=%d)\n",
                    line,
                    n);
        else
            printError("[drainer]\tcould not read from buffer");

        /* unlock the semaphore */
        if (sem_post(&gl_sem) == -1)
            printError("[drainer]\tcould not unlock semaphore");

        if (!strcmp(line, "QUIT"))
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
}
