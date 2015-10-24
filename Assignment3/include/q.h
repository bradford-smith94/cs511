#ifndef _Q_
#define _Q_

#include "cart.h"

#define Q_NORTH 'n'
#define Q_SOUTH 's'
#define Q_EAST 'e'
#define Q_WEST 'w'

extern void q_init();
extern struct cart_t *q_getCart(char);
extern void q_putCart(char);
extern int q_cartIsWaiting(char);
extern void q_cartHasEntered(char);
extern void q_print(char);
extern void q_shutdown();

#endif /* _Q_ */
