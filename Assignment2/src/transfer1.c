/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 transfer1.c
 * 10/10/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "transfer1.h"
#include "utils.h"
#include "cbuf.h"

#define usage "[usage]\t ./transfer1 <input file> <output file> <filler wait> <drainer wait>"

int main(int argc, char** argv)
{
    struct s_threadArgs fillerArgs;
    struct s_threadArgs drainerArgs;
    pthread_t fillerThread;
    pthread_t drainerThread;
    FILE* outStream;
    char* inFile;
    char* outFile;
    int fillerWait;
    int drainerWait;

    if (argc != 5)
        printf("%s\n", usage);

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

    /* create 2 pthreads for filler and drainer */
    if (pthread_create(&fillerThread, NULL, (void *) start_filler, (void *) &fillerArgs))
        printError("could not create filler thread");
    if (pthread_create(&drainerThread, NULL, (void *) start_drainer, (void *) &drainerArgs))
        printError("could not create drainer thread");

    /* wait for threads */
    if (pthread_join(fillerThread, NULL))
        printError("could not join filler thread");
    if (pthread_join(drainerThread, NULL))
        printError("could not join drainer thread");

    cbuf_terminate();
    if (sem_destroy(&gl_sem) == -1)
        printError("unable to destroy semaphore");

    return 0;
}
