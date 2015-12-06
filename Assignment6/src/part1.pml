/* Bradford Smith (bsmith8)
 * CS 511 Assignment 6 part1.pml
 * 12/05/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

/*  n is global  */
byte n;

/*  argument N is the limit  */
proctype incrementUpToN(byte N) {
    byte i = 1;   /* counter: ranges from 1 to N */
    byte temp;    /* implicitly initialized to 0 */

    do
    :: i > N -> break
    :: else  ->
        temp = n;
        n = temp + 1;
        printf("process %d, i=%d: n changed from %d to %d\n", _pid, i, temp, n);
        i = i + 1
    od
}


init {
    n = 0;
    atomic {
        run incrementUpToN(5)  ;
        run incrementUpToN(5)
    }
    (_nr_pr == 1) -> printf("at end of simulation n = %d\n", n);
    assert(5 <= n && n <= 10);
    printf("simulation passed assertion!\n");
}
