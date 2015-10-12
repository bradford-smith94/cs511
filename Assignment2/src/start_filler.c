/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 start_filler.c
 * 10/12/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer1.h"

/* pre: takes in a void* input (which must be a pointer to type
 *      struct s_threadArgs)
 * post: runs the filler thead for transfer1
 * returns: a 0 (don't try dereferencing it) exits on errors
 */
void* start_filler(void *input)
{
    struct s_threadArgs args;
    FILE* inStream;
    size_t size;
    char* line;
    int quit;
    int n;
    int m;

    args = *((struct s_threadArgs*)input);
#ifdef DEBUG
    printf("[DEBUG]\t[filler]\targs.waitTime: %d\n", args.waitTime);
    fflush(stdout);
#endif

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
            quit = 1;
            free(line);
            line = quitWord;
            n = strlen(line) + 1;
#ifdef DEBUG
            printDebug("[filler]\tquitting...");
            printf("\tline: %s, n: %d\n", line, n);
            fflush(stdout);
#endif
        }
        else
            line[n++] = '\0';

        while ((m = cbuf_space_available()) < n)
        {
            printf("fill thread: could not write [%s] -- not enough space (%d)\n",
                    line,
                    m);
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
    fclose(inStream);

    return 0;
}
