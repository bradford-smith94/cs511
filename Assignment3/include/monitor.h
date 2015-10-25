/* Bradford Smith (bsmith8)
 * CS 511 Assingment 3 monitor.h
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

#include "cart.h"
#include "q.h"

struct monitor_t {
    char checkOrder[4];
    struct cart_t* cart;
    sem_t semLock;
    char nextDir;
} gl_mon;

static pthread_mutex_t gl_monLock = PTHREAD_MUTEX_INITIALIZER;

void monitor_init();
void monitor_arrive(struct cart_t*);
void monitor_cross(struct cart_t*);
void monitor_leave(struct cart_t*);
void monitor_shutdown();

#endif /* _MONITOR_H_ */
