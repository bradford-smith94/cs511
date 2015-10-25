/* Bradford Smith (bsmith8)
 * CS 511 Assingment 3 monitor.h
 * 10/24/2015
 * "I pledge my honor that I have abided by the Stevens Honor System."
 */

#ifndef _MONITOR_H_
#define _MONITOR_H_

#include "cart.h"

void monitor_init();
void monitor_arrive(struct cart_t*);
void monitor_cross(struct cart_t*);
void monitor_leave(struct cart_t*);
void monitor_shutdown();

#endif /* _MONITOR_H_ */
