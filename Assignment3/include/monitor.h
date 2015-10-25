/* Bradford Smith (bsmith8)
 * CS 511 Assingment 3 monitor.h
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _MONITOR_H_
#define _MONITOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include "cart.h"
#include "q.h"

pthread_mutex_t gl_monLock;
pthread_cond_t gl_northCond;
pthread_cond_t gl_southCond;
pthread_cond_t gl_eastCond;
pthread_cond_t gl_westCond;
char gl_direction;
char gl_checkOrder[4];

void monitor_init();
void monitor_arrive(struct cart_t*);
void monitor_cross(struct cart_t*);
void monitor_leave(struct cart_t*);
void monitor_shutdown();

#endif /* _MONITOR_H_ */
