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
    pthread_t fillerThread;
    pthread_t drainerThread;
    FILE* inStream;
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

    cbuf_init();

    /* create 2 pthreads for filler and drainer */
    if (pthread_create(&fillerThread, NULL, (void *) start_filler, (void *) &fillerWait))
        printError("could not create filler thread");
    if (pthread_create(&drainerThread, NULL, (void *) start_drainer, (void *) &drainerWait))
        printError("could not create drainer thread");

    /* wait for threads */
    if (pthread_join(fillerThread, NULL))
        printError("could not join filler thread");
    if (pthread_join(drainerThread, NULL))
        printError("could not join drainer thread");

    /* clear cbuf */
    cbuf_terminate();

    return 0;
}
