/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 trafficmgr.h
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _TRAFFICMGR_H_
#define _TRAFFICMGR_H_

/* C things */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/* my things */
#include "cart.h"
#include "q.h"
#include "monitor.h"

/* This is the main header file for the Traffic Management program */
int     main(int, char**);
void*   thread_start(void*);

#endif /* _TRAFFICMGR_H_ */
