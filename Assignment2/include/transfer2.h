/* Bradford Smith (bsmith8)
 * CS 511 Assignment 2 transfer2.h
 * 10/12/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _TRANSFER2_H_
#define _TRANSFER2_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#include "cbuf.h"
#include "utils.h"

/* the message filler and drainer should use to signal quit */
#define quitWord "QUIT"

struct s_threadArgs
{
    int waitTime;
    char* fileName;
};

/* global semaphores */
sem_t gl_sem_mutex;
sem_t gl_sem_spaces;
sem_t gl_sem_items;

/* This is the header file for CS 511 Assignment 2 Part 2: transfer2 */

int     main(int, char**);
void*   start_filler2(void*);
void*   start_drainer2(void*);

#endif /* _TRANSFER2_H_ */
