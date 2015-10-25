/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_cross.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_cross(struct cart_t* cart)
{
    /* get monitor lock */
    pthread_mutex_lock(&gl_monLock);

    if (gl_direction == '\0')
        gl_direction = cart->dir;
    else
    {
        /* wait on direction */
        switch (cart->dir)
        {
            fprintf(stderr, "Cart %i from direction %c must wait before entering intersection\n",
                    cart->num,
                    cart->dir);
            case Q_NORTH:
                pthread_cond_wait(&gl_northCond, &gl_monLock);
                break;
            case Q_SOUTH:
                pthread_cond_wait(&gl_southCond, &gl_monLock);
                break;
            case Q_EAST:
                pthread_cond_wait(&gl_eastCond, &gl_monLock);
                break;
            case Q_WEST:
                pthread_cond_wait(&gl_westCond, &gl_monLock);
                break;
        }
    }
    fprintf(stderr, "Cart %i from direction %c allowed to proceed into intersection\n",
            cart->num,
            cart->dir);
    q_cartHasEntered(gl_direction);

    /* it takes 10 seconds for a cart to cross */
    sleep(10);

    fprintf(stderr, "Cart %i from direction %c crosses intersection\n",
            cart->num,
            cart->dir);

    /* drop monitor lock */
    pthread_mutex_unlock(&gl_monLock);
}
