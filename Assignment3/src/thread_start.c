/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 thread_start.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "trafficmgr.h"

/* pre: takes in a void* d (this must be a character, NOT POINTER, specifically
 *      one of 'Q_NORTH', 'Q_SOUTH', 'Q_EAST', 'Q_WEST' defined in 'q.h')
 * post: runs all the carts in the q for direction d through the monitor
 * return: NULL
 */
void* thread_start(void* d)
{
    char direction;
    struct cart_t* cart;

    /* dirty cast hack to get char value stored in pointer -- dereferencing
     * causes segmentation fault */
    direction = (char)((unsigned long)d);

    fprintf(stderr, "Thread for direction %c starts\n", direction);
    cart = q_getCart(direction);

    while (cart != NULL)
    {
        fprintf(stderr, "Thread for direction %c gets cart %i\n",
                direction,
                cart->num);
        monitor_arrive(cart);
        monitor_cross(cart);
        monitor_leave(cart);
        cart = q_getCart(direction);
    }

    fprintf(stderr, "Thread for direction %c stops\n", direction);

    return NULL;
}
