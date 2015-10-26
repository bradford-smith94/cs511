/* Bradford Smith (bsmith8)
 * CS 511 Assignment 3 main.c
 * 10/25/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "trafficmgr.h"

/* pre: takes in int argc and char** argv (command line arguments)
 * post: runs the traffic manager program
 * return: 0 on success, something else on error
 */
int main(int argc, char** argv)
{
    pthread_t threadN;
    pthread_t threadS;
    pthread_t threadE;
    pthread_t threadW;
    int i;

    if (argc != 2)
    {
        printf("[usage]\t %s <string of direction letters>\n", argv[0]);
        exit(1);
    }

    q_init();
    monitor_init();

    /* validate input and initialize q's */
    for (i = 0; i < strlen(argv[1]); i++)
    {
        /* if not valid exit with error */
        if (argv[1][i] != Q_NORTH && argv[1][i] != Q_SOUTH
                && argv[1][i] != Q_EAST && argv[1][i] != Q_WEST)
        {
            printf("[ERROR]\tinput string must contain only the letters: '%c', '%c', '%c' and '%c'\n",
                    Q_NORTH,
                    Q_SOUTH,
                    Q_EAST,
                    Q_WEST);
            exit(2);
        }
        else
        {
            /* add cart to q corresponding to direction of cart travel */
            if (argv[1][i] == Q_NORTH)
                q_putCart(Q_NORTH);
            else if (argv[1][i] == Q_SOUTH)
                q_putCart(Q_SOUTH);
            else if (argv[1][i] == Q_EAST)
                q_putCart(Q_EAST);
            else
                q_putCart(Q_WEST);
        }
    } /* end for loop: validate and initialize */

    /* start threads */
    if (pthread_create(&threadN, NULL, &thread_start, (void*) Q_NORTH))
    {
        printf("[ERROR]\tcould not create thread\n");
        exit(3);
    }
    if (pthread_create(&threadS, NULL, &thread_start, (void*) Q_SOUTH))
    {
        printf("[ERROR]\tcould not create thread\n");
        exit(3);
    }
    if (pthread_create(&threadE, NULL, &thread_start, (void*) Q_EAST))
    {
        printf("[ERROR]\tcould not create thread\n");
        exit(3);
    }
    if (pthread_create(&threadW, NULL, &thread_start, (void*) Q_WEST))
    {
        printf("[ERROR]\tcould not create thread\n");
        exit(3);
    }

    /* wait for threads */
    if (pthread_join(threadN, NULL))
    {
        printf("[ERROR]\tcould not join thread\n");
        exit(4);
    }
    if (pthread_join(threadS, NULL))
    {
        printf("[ERROR]\tcould not join thread\n");
        exit(4);
    }
    if (pthread_join(threadE, NULL))
    {
        printf("[ERROR]\tcould not join thread\n");
        exit(4);
    }
    if (pthread_join(threadW, NULL))
    {
        printf("[ERROR]\tcould not join thread\n");
        exit(4);
    }

    monitor_shutdown();
    q_shutdown();

    return 0;
}
