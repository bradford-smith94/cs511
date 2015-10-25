/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_init.c
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_init()
{
    /* initialize mutex lock */
    if (pthread_mutex_init(&gl_monLock, NULL))
    {
        printf("[ERROR]\tcould not initalize pthread mutex lock\n");
        exit(4);
    }

    /* initialize pthread conditions */
    if (pthread_cond_init(&gl_northCond, NULL))
    {
        printf("[ERROR]\tcould not initialize pthread condition\n");
        exit(4);
    }
    if (pthread_cond_init(&gl_southCond, NULL))
    {
        printf("[ERROR]\tcould not initialize pthread condition\n");
        exit(4);
    }
    if (pthread_cond_init(&gl_eastCond, NULL))
    {
        printf("[ERROR]\tcould not initialize pthread condition\n");
        exit(4);
    }
    if (pthread_cond_init(&gl_westCond, NULL))
    {
        printf("[ERROR]\tcould not initialize pthread condition\n");
        exit(4);
    }

    /* initialize direction */
    gl_direction = '\0';

    /* initialize checkOrder */
    gl_checkOrder[0] = Q_NORTH;
    gl_checkOrder[1] = Q_WEST;
    gl_checkOrder[2] = Q_SOUTH;
    gl_checkOrder[3] = Q_EAST;
}
