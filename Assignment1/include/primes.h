/* Bradford Smith (bsmith8)
 * CS 511 Assignment 1 primes.h
 * 09/27/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _PRIMES_H_
#define _PRIMES_H_

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/select.h>

struct s_proc
{
    int pid;
    int fifofd;
    int pipefd[2];
    int num;
    char fifoname[15];
    char flag; /* in place of a boolean */
};

/* This is the header for CS 511 Assignment 1 the primes calculator
 */
int     main(int, char**);
void    printError(char*);
void    printDebug(char*);
int     findPrimes(int, int, struct s_proc);

#endif /* _PRIMES_H_ */
