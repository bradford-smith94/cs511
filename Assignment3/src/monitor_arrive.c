/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_arrive.c
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_arrive(struct cart_t* cart)
{
    /* get monitor lock */
    pthread_mutex_lock(&gl_monLock);

    fprintf(stderr, "Cart %i arrives at intersection from direction %c\n",
            cart->num,
            cart->dir);

    /* drop monitor lock */
    pthread_mutex_unlock(&gl_monLock);
}
