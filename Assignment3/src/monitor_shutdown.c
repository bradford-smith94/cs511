/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_shutdown.c
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

void monitor_shutdown()
{
    gl_mon.cart = NULL;
    gl_mon.nextDir = '\0';
    if (sem_destroy(&gl_mon.semLock) == -1)
    {
        printf("[ERROR]\tcould not destory semaphore\n");
        exit(5);
    }
}
