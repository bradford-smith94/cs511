/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_arrive.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_arrive(struct cart_t* cart)
{
    int i;
    int j;

    /* if our direction is not next and nextDir is not NULL, we wait */
    while (gl_mon.nextDir != '\0' && gl_mon.nextDir != cart->dir)
        sleep(10);

    /* get the lock */
    sem_wait(&gl_mon.semLock);

    /* if cart is not Null */
    if (gl_mon.cart != NULL)
    {
        printf("[ERROR]\t[monitor_arrive]\tthere must have been a mistake...\n");
        sem_post(&gl_mon.semLock);
        return;
    }

    /* make cart this one */
    gl_mon.cart = cart;
    fprintf(stderr, "Cart %i arrives at intersection from direction %c\n",
            gl_mon.cart->num,
            gl_mon.cart->dir);

    /* get the next direction */
    gl_mon.nextDir = cart->dir; /* default to this direction */

    /* find what index this direction is */
    for (i = 0; gl_mon.checkOrder[i] != cart->dir; i++);

    /* start there and check directions as defined by gl_mon.checkOrder */
    for (j = (i + 1) % 4; j != i; i++)
    {
        /* update gl_mon.nextDir if direction has a cart waiting */
        if (q_cartIsWaiting(gl_mon.checkOrder[j]))
            gl_mon.nextDir = gl_mon.checkOrder[j];
    }
}
