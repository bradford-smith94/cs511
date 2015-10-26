/* Bradford Smith (bsmith8)
 * CS 511 Assingment 3 monitor.h
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _MONITOR_H_
#define _MONITOR_H_

/* C things */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

/* my things */
#include "cart.h"
#include "q.h"

/* global monitor variables */
pthread_mutex_t gl_monLock; /* lock */
pthread_cond_t gl_northCond; /* condition signalling north is next */
pthread_cond_t gl_southCond; /* condition signalling south is next */
pthread_cond_t gl_eastCond; /* condition signalling east is next */
pthread_cond_t gl_westCond; /* condition signalling west is next */
char gl_direction; /* the direction currently moving through the intersection */
char gl_checkOrder[4]; /* the order that directions should be checked for waiting carts */

/* This is the header file for the monitor interface that controlls the
 * intersection in the Traffic Management program */
void monitor_init();
void monitor_arrive(struct cart_t*);
void monitor_cross(struct cart_t*);
void monitor_leave(struct cart_t*);
void monitor_shutdown();

#endif /* _MONITOR_H_ */
