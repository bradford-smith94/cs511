#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/queue.h>
#include "q.h"
#include "cart.h"


struct q_entry_t {
  struct cart_t *cart;
  struct q_entry_t *next;
};

static pthread_mutex_t QLock = PTHREAD_MUTEX_INITIALIZER;

static struct q_entry_t *northQ;
static int northCartIsWaiting;
static struct q_entry_t *southQ;
static int southCartIsWaiting;
static struct q_entry_t *eastQ;
static int eastCartIsWaiting;
static struct q_entry_t *westQ;
static int westCartIsWaiting;
static int cartNumber;



void q_init() {
  /* mutex initialized statically */
  northQ = NULL;
  northCartIsWaiting = 0;
  southQ = NULL;
  southCartIsWaiting = 0;
  eastQ = NULL;
  eastCartIsWaiting = 0;
  westQ = NULL;
  westCartIsWaiting = 0;
  cartNumber = 0;
  return;
}


/*
 *  Get cart from head of 'dir' queue; if queue is empty return NULL
 *  Caller is responsible for freeing memory once cart_t is no longer needed.
 */
struct cart_t *q_getCart(char dir) {
  struct cart_t *cart = NULL;

  pthread_mutex_lock(&QLock);
  switch (dir) {
  case Q_NORTH:
    if (northQ == NULL)
      break;   /* jump out of switch stmt, execute unlock below */
    cart = northQ->cart;
    northQ = northQ->next;
    northCartIsWaiting = 1;
    break;
  case Q_SOUTH:
    if (southQ == NULL)
      break;   /* jump out of switch stmt, execute unlock below */
    cart = southQ->cart;
    southQ = southQ->next;
    southCartIsWaiting = 1;
    break;
  case Q_EAST:
    if (eastQ == NULL)
      break;   /* jump out of switch stmt, execute unlock below */
    cart = eastQ->cart;
    eastQ = eastQ->next;
    eastCartIsWaiting = 1;
    break;
  case Q_WEST:
    if (westQ == NULL)
      break;   /* jump out of switch stmt, execute unlock below */
    cart = westQ->cart;
    westQ = westQ->next;
    westCartIsWaiting = 1;
    break;
  }
  pthread_mutex_unlock(&QLock);

  return cart;
}


/*
 *  Place new cart at tail of 'dir' queue
 */
void q_putCart(char dir) {
  struct cart_t *cart = malloc(sizeof(struct cart_t));
  struct q_entry_t *newCart = malloc(sizeof(struct q_entry_t));
  if ((cart == NULL) || (newCart == NULL))
    return;

  pthread_mutex_lock(&QLock);
  cart->num = ++cartNumber;
  cart->dir = dir;
  newCart->cart = cart;
  newCart->next = NULL;
  switch (dir) {
  case Q_NORTH:
    if (northQ == NULL) {
      northQ = newCart;
    } else {
      struct q_entry_t *ptr = northQ;
      while (ptr->next != NULL)
	ptr = ptr->next;
      ptr->next = newCart;
    }
    break;
  case Q_SOUTH:
    if (southQ == NULL) {
      southQ = newCart;
    } else {
      struct q_entry_t *ptr = southQ;
      while (ptr->next != NULL)
	ptr = ptr->next;
      ptr->next = newCart;
    }
    break;
  case Q_EAST:
    if (eastQ == NULL) {
      eastQ = newCart;
    } else {
      struct q_entry_t *ptr = eastQ;
      while (ptr->next != NULL)
	ptr = ptr->next;
      ptr->next = newCart;
    }
    break;
  case Q_WEST:
    if (westQ == NULL) {
      westQ = newCart;
    } else {
      struct q_entry_t *ptr = westQ;
      while (ptr->next != NULL)
	ptr = ptr->next;
      ptr->next = newCart;
    }
    break;
  }
  pthread_mutex_unlock(&QLock);
  return;
}


/*
 *  Is there a cart from direction 'dir' waiting to enter intersection?
 */
int q_cartIsWaiting(char dir) {
  int answer;

  pthread_mutex_lock(&QLock);
  switch (dir) {
  case Q_NORTH:
    answer = northCartIsWaiting;
    break;
  case Q_SOUTH:
    answer = southCartIsWaiting;
    break;
  case Q_EAST:
    answer = eastCartIsWaiting;
    break;
  case Q_WEST:
    answer = westCartIsWaiting;
    break;
  }
  pthread_mutex_unlock(&QLock);
  return answer;
}


/*
 *  Mark that cart from direction 'dir' is no longer waiting.
 */
void q_cartHasEntered(char dir) {
  pthread_mutex_lock(&QLock);
  switch (dir) {
  case Q_NORTH:
    northCartIsWaiting = 0;
    break;
  case Q_SOUTH:
    southCartIsWaiting = 0;
    break;
  case Q_EAST:
    eastCartIsWaiting = 0;
    break;
  case Q_WEST:
    westCartIsWaiting = 0;
    break;
  }
  pthread_mutex_unlock(&QLock);
  return;
}


void q_print(char dir) {
  struct q_entry_t *ptr;

  pthread_mutex_lock(&QLock);
  fprintf(stderr, "Direction %c: ", dir);
  switch (dir) {
  case Q_NORTH:
    ptr = northQ;
    break;
  case Q_SOUTH:
    ptr = southQ;
    break;
  case Q_EAST:
    ptr = eastQ;
    break;
  case Q_WEST:
    ptr = westQ;
    break;
  }
  if (ptr != NULL) {
    do {
      fprintf(stderr, "%i -> ", ptr->cart->num);
      ptr = ptr->next;
    } while (ptr != NULL);
  }
  fprintf(stderr, "NULL\n");
  pthread_mutex_unlock(&QLock);
  return;
}


void q_shutdown() {
  if ((northQ != NULL) || northCartIsWaiting)
    fprintf(stderr, "Warning!  There are still entries in the north queue\n");
  if ((southQ != NULL) || southCartIsWaiting)
    fprintf(stderr, "Warning!  There are still entries in the south queue\n");
  if ((eastQ != NULL) || eastCartIsWaiting)
    fprintf(stderr, "Warning!  There are still entries in the east queue\n");
  if ((westQ != NULL) || westCartIsWaiting)
    fprintf(stderr, "Warning!  There are still entries in the west queue\n");
  pthread_mutex_destroy(&QLock);
  return;
}
