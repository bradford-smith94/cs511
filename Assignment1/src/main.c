/* Bradford Smith (bsmith8)
 * CS 511 Assignment 1 main.c
 * 09/27/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#include "primes.h"

#define usage "usage: ./primes <increasing positive integers greater than 2>\n"

/* pre: takes in a int argc and char** argv command line arguments
 * post: searches for prime numbers within ranges given by argv
 * return: 0 on success, undefined on failure
 */
int main(int argc, char** argv)
{
    struct s_proc procs[argc - 1];
    struct timeval tv;
    fd_set rfds;
    char buffer[256];
    char temp[10];
    int limits[argc - 1];
    int i;
    int j;
    int n;
    int childstatus;
    int fd;
    int pid;
    int bottom;
    int top;
    int maxfd;

    /* get limits from argv */
    if (argc < 2)
    {
        printf(usage);
        exit(0);
    }
    else
    {
        argc -= 1;
        for (i = 0; i < argc; i++)
        {
            limits[i] = atoi(argv[i + 1]);
            if (limits[i] <= 2)
            {
                printf(usage);
                exit(0);
            }
        }
    }

#ifdef DEBUG
    printDebug("limits:");
    for (i = 0; i < argc; i++)
    {
        printf("\t[%d]\t%d\n",
                i,
                limits[i]);
    }
#endif

    /* setup initial bounds */
    bottom = 2;
    top = limits[0];

    /* make the children */
    for (i = 0; i < argc; i++)
    {
        if ((i + 1) % 2 == 0)
        {
            /* even process use FIFO */
            sprintf(procs[i].fifoname, "fifo%d.pipe", i + 1);
            if (mkfifo(procs[i].fifoname, 0666) == -1)
                printError("couldn't create fifo");
            procs[i].isFifo = 1;
        }
        else
        {
            /* odd process use pipe */
            if (pipe(procs[i].pipefd) == -1)
                printError("couldn't create pipe");
            procs[i].isFifo = 0;
        }

        if ((pid = fork()) == 0)
        {
            /* child */
#ifdef DEBUG
            printf("[DEBUG]\tnew child, bottom: %d, top: %d\n",
                    bottom,
                    top);
            fflush(stdout);
#endif

            /* find primes from bottom to top */
            _exit(findPrimes(bottom, top, procs[i]));
            /* don't let the children leave here alive */
        }
        else
        {
            /* parent */
            printf("child %d: bottom=%d, top=%d\n",
                    pid,
                    bottom,
                    top);

            procs[i].pid = pid;
            procs[i].num = 0;
            procs[i].isDone = 0;
            if (procs[i].isFifo)
            {
                /* open fifo read-only */
                if ((procs[i].fifofd = open(procs[i].fifoname, O_RDONLY)) == -1)
                    printError("couldn't open fifo");
            }
            else
            {
                /* close write end of pipe */
                if (close(procs[i].pipefd[1]) == -1)
                    printError("couldn't close pipe");
            }

            /* increment bounds if there are more children to go */
            if (i < argc - 1)
            {
                bottom = top + 1;
                top = limits[i + 1];
            }
        }
    } /* for */

    /* loop on select to read from file descriptors */
    while (1)
    {
        /* zero out fd_set */
        FD_ZERO(&rfds);
        maxfd = 0;

        /* fill rfds */
        for (i = 0; i < argc; i++)
        {
            if (!procs[i].isDone)
            {
                if (procs[i].isFifo)
                {
                    /* add fifofd to rfds */
                    FD_SET(procs[i].fifofd, &rfds);
                    if (procs[i].fifofd > maxfd)
                        maxfd = procs[i].fifofd;
                }
                else
                {
                    /* add pipefd to rfds */
                    FD_SET(procs[i].pipefd[0], &rfds);
                    if (procs[i].pipefd[0] > maxfd)
                        maxfd = procs[i].pipefd[0];
                }
            }
        }

        /* set timeouts */
        tv.tv_sec = 0;
        tv.tv_usec = 500;

        /* select will block indefinitely */
        if ((n = select(maxfd + 1, &rfds, NULL, NULL, &tv)) == -1)
            printError("select failed");
        else if (!n)
            break;
        for (i = 0; i < argc; i++)
        {
            if (procs[i].isFifo)
                fd = procs[i].fifofd;
            else
                fd = procs[i].pipefd[0];

            if (FD_ISSET(fd, &rfds))
            {
                n = read(fd, &buffer[0], 255);
                if(n == -1 || n == 0)
                {
#ifdef DEBUG
                    printf("[DEBUG]\tchild %d sent %d primes\n",
                            procs[i].pid,
                            procs[i].num);
                    fflush(stdout);
#endif
                    if ((waitpid(procs[i].pid, &childstatus, 0)) > 0)
                    {
                        FD_CLR(fd, &rfds);
                        if (procs[i].num == WEXITSTATUS(childstatus))
                        {
                            printf("child %d exited correctly\n", procs[i].pid);
                            fflush(stdout);
                            procs[i].isDone = 1;
                        }
                        else
                            printError("child exited incorrectly");
                    }
                }
                else /* no read error */
                {
                    buffer[n] = '\0';
                    for (n = 0, j = 0; buffer[n] != '\0'; n++)
                    {
                        if (buffer[n] == '|')
                        {
                            temp[j] = '\0';
                            j = 0;
                            printf("%s\tis prime\n", &temp[0]);
                            fflush(stdout);
                            procs[i].num++;
                        }
                        else
                            temp[j++] = buffer[n];
                    }
                }
            }
        } /* for */
    } /* while */

    /* after all children have exited, clean up fifos */
    for (i = 0; i < argc; i++)
    {
        if (procs[i].isFifo)
        {
            if (close(procs[i].fifofd) == -1)
                printError("couldn't close fifo");
            if (unlink(procs[i].fifoname) == -1)
                printError("couldn't remove fifo");
        }
    }

    return 0;
} /* main */
