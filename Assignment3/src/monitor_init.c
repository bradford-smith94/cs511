/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_init.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_init()
{
    gl_mon.cart = NULL;
    gl_mon.nextDir = '\0';
    gl_mon.checkOrder[0] = Q_NORTH;
    gl_mon.checkOrder[1] = Q_WEST;
    gl_mon.checkOrder[2] = Q_SOUTH;
    gl_mon.checkOrder[3] = Q_EAST;
    if (sem_init(&gl_mon.semLock, 0, 1) == -1)
    {
        printf("[ERROR]\tcould not initialize semaphore\n");
        exit(5);
    }
}
