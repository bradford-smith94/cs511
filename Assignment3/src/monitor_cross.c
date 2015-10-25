/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_cross.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_cross(struct cart_t* cart)
{
    /* if the monitor cart is not this cart, we wait */
    if (gl_mon.cart->num != cart->num)
        sleep(10);

    q_cartHasEntered(gl_mon.cart->dir);

    /* it takes a cart 10 seconds to cross the intersection */
    sleep(10);
}
