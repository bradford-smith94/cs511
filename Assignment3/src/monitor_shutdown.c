/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 monitor_shutdown.c
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "monitor.h"

/* pre: monitor has been initialized
 * post: destroys monitor pthread conditions and mutex lock
 */
void monitor_shutdown()
{
    /* destroy pthread conditions */
    if (pthread_cond_destroy(&gl_northCond))
    {
        printf("[ERROR]\tcould not destroy pthread condition\n");
        exit(4);
    }
    if (pthread_cond_destroy(&gl_southCond))
    {
        printf("[ERROR]\tcould not destroy pthread condition\n");
        exit(4);
    }
    if (pthread_cond_destroy(&gl_eastCond))
    {
        printf("[ERROR]\tcould not destroy pthread condition\n");
        exit(4);
    }
    if (pthread_cond_destroy(&gl_westCond))
    {
        printf("[ERROR]\tcould not destroy pthread condition\n");
        exit(4);
    }

    /* destroy mutex lock */
    if (pthread_mutex_destroy(&gl_monLock))
    {
        printf("[ERROR]\tcould not destroy pthread mutex lock\n");
        exit(4);
    }
}
