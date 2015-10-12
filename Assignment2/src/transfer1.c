/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 transfer1.c
 * 10/12/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer1.h"

#define usage "[usage]\t ./transfer1 <input file> <output file> <filler wait> <drainer wait>"

/* pre: takes in int argc and char** argv command line arguments
 * post: runs the transfer1 program
 */
int main(int argc, char** argv)
{
    struct s_threadArgs fillerArgs;
    struct s_threadArgs drainerArgs;
    pthread_t fillerThread;
    pthread_t drainerThread;
    char* inFile;
    char* outFile;
    int fillerWait;
    int drainerWait;

    if (argc != 5)
    {
        printf("%s\n", usage);
        exit(0);
    }

    inFile = argv[1];
    outFile = argv[2];
    fillerWait = atoi(argv[3]);
    drainerWait = atoi(argv[4]);

    /* setup thread args */
    fillerArgs.waitTime = fillerWait;
    fillerArgs.fileName = inFile;

    drainerArgs.waitTime = drainerWait;
    drainerArgs.fileName = outFile;

    cbuf_init();
    if (sem_init(&gl_sem, 0, 1) == -1)
        printError("unable to initialize semaphore");
    printf("buffer size: %d\n", cbuf_space_available());

    /* create 2 pthreads for filler and drainer */
    if (pthread_create(&fillerThread, NULL, &start_filler, (void *) &fillerArgs))
        printError("could not create filler thread");
    if (pthread_create(&drainerThread, NULL, &start_drainer, (void *) &drainerArgs))
        printError("could not create drainer thread");

#ifdef DEBUG
    printDebug("[main]\twaiting for threads...");
#endif

    /* wait for threads */
    if (pthread_join(fillerThread, NULL))
        printError("could not join filler thread");
    if (pthread_join(drainerThread, NULL))
        printError("could not join drainer thread");

#ifdef DEBUG
    printDebug("[main]\tfreeing memory and quitting...");
#endif

    cbuf_terminate();
    if (sem_destroy(&gl_sem) == -1)
        printError("unable to destroy semaphore");

    return 0;
}
