/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_leave.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_leave(struct cart_t* cart)
{
    /* if the monitor cart is not this cart, we wait */
    if (gl_mon.cart->num != cart->num)
        sleep(10);

    gl_mon.cart = NULL;

    /* give up the lock */
    sem_post(&gl_mon.semLock);
}
