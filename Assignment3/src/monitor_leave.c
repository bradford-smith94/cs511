/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_leave.c
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_leave(struct cart_t* cart)
{
    int i;
    int j;
    int signalling;

    /* get monitor lock */
    pthread_mutex_lock(&gl_monLock);

    fprintf(stderr, "[Cart]\tCart %i from direction %c leaves intersection\n",
            cart->num,
            cart->dir);

    /* signal next direction */
    signalling = 0;
    for (i = 0; i < 4 && gl_checkOrder[i] != cart->dir; i++);
    for (j = (i + 1) % 4; j != i && !signalling; j = (j + 1) % 4)
    {
        if (q_cartIsWaiting(gl_checkOrder[i]))
        {
            signalling = 1;
            gl_direction = gl_checkOrder[i];
        }
    }

    /* if not signalling by the end of loop, check current direction */
    if (!signalling)
    {
        if (q_cartIsWaiting(gl_direction))
            signalling = 1;
        else
            gl_direction = '\0';
    }

    if (signalling)
    {
        fprintf(stderr, "[Thread]\tThread for %c signalling thread for %c\n",
                cart->dir,
                gl_direction);
        switch (gl_direction)
        {
            case Q_NORTH:
                pthread_cond_signal(&gl_northCond);
                break;
            case Q_SOUTH:
                pthread_cond_signal(&gl_southCond);
                break;
            case Q_EAST:
                pthread_cond_signal(&gl_eastCond);
                break;
            case Q_WEST:
                pthread_cond_signal(&gl_westCond);
                break;
        }
    }

    /*drop monitor lock */
    pthread_mutex_unlock(&gl_monLock);
}
