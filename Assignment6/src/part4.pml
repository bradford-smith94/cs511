/* Bradford Smith (bsmith8)
 * CS 511 Assignment 6 part4.pml
 * 12/08/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

chan monlock = [1] of {bit}; /* monitor lock */
chan launchpad = [1] of {bit}; /* "launchpad" lock */
chan intersection = [1] of {bit}; /* intersection lock */
byte carts = 0; /* count of carts in the intersection */

/* runs all simulated monitor functions for each "cart" */
proctype monitor_funcs(byte N) {
    /* monitor arrive */
    monlock ? 1;
    launchpad ? 1; /* get the launchpad lock */
    monlock ! 1;

    /* monitor cross */
    monlock ? 1;
    intersection ? 1; /* get the intersection lock */
    carts = carts + N; /* add this cart (1) to the count */
    assert(carts == 1 || carts == 0); /* assert */
    launchpad ! 1; /* drop launchpad lock */
    monlock ! 1;

    /* monitor leave */
    monlock ? 1;
    carts = carts - N; /* remove this cart (1) from the count */
    intersection ! 1; /* drop the intersection lock */
    monlock ! 1;
}

proctype main() {
    byte carts[4] = 1; /* all bytes initialized to 1 */
    byte i = 0;

    do
    :: i > 3 -> break
    :: else ->
        run monitor_funcs(carts[i]);
        i = i + 1
    od
}

init {
    /* initialize locks */
    monlock ! 1;
    launchpad ! 1;
    intersection ! 1;
    /* run 4 instances (1 for each simulated direction */
    atomic {
        run main();
        run main();
        run main();
        run main()
    }
    printf("simulation passed assertion!\n");
}
