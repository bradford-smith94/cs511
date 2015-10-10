#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "cbuf.h"


char *cbuf_buffer;             /* the buffer */
int cbuf_amount;               /* amount of data in the buffer */
int cbuf_first_data;           /* index of first byte that is data */
int cbuf_first_free;           /* index of first byte that is free */
#define ZERO_BYTE '\0'


void cbuf_init() {
  cbuf_buffer = calloc(CBUF_CAPACITY, 1);
  cbuf_amount = 0;
  cbuf_first_data = 0;
  cbuf_first_free = 0;
}


void cbuf_terminate() {
  free(cbuf_buffer);
}


void cbuf_print() {
  int i;

  printf("cbuf_buffer = ");
  for (i=0; i<CBUF_CAPACITY; i++)
    printf(cbuf_buffer[i]==ZERO_BYTE ? "%x" : "%c", cbuf_buffer[i]);
  printf("\n");
  printf("cbuf_amount = %i\n", cbuf_amount);
  printf("cbuf_first_data = %i\n", cbuf_first_data);
  printf("cbuf_first_free = %i\n", cbuf_first_free);
}


int cbuf_data_is_available() {
  return (cbuf_amount > 0);
}


int cbuf_space_available() {
  return (CBUF_CAPACITY - cbuf_amount);
}


/*
 *  try to copy in zero-terminated string
 *  return amount that was copied in
 */
#define COPY_BYTE_IN(x)	       \
  {			       \
    cbuf_buffer[to] = (x);     \
    if (to == CBUF_CAPACITY-1) {		\
      to = 0;					\
    } else {					\
      to++;					\
    }						\
  }

int cbuf_copy_in(char *string) {
  int to, from;

  if (strlen(string)+1 > (CBUF_CAPACITY - cbuf_amount))
    return 0;
  to = cbuf_first_free;
  for (from=0; from<strlen(string); from++)
    COPY_BYTE_IN(string[from]);
  COPY_BYTE_IN(ZERO_BYTE);
  cbuf_first_free = to;
  cbuf_amount = cbuf_amount + strlen(string) + 1;
  return strlen(string) + 1;
}


/*
 *  copy out next zero-terminated string
 *  return amount that was copied out
 */
int cbuf_copy_out(char *data) {
  int from, amount;
  char ch;

  if (cbuf_amount == 0)
    return 0;
  from = cbuf_first_data;
  amount = 0;
  do {
    ch = cbuf_buffer[from];
    data[amount++] = ch;
    if (from == CBUF_CAPACITY-1) {
      from = 0;
    } else {
      from++;
    }
  } while (ch != ZERO_BYTE);
  cbuf_amount = cbuf_amount - amount;
  cbuf_first_data = from;
  return amount;
}


#if 0
int main() {
  char ignore[CBUF_CAPACITY];

  cbuf_init();
  cbuf_print();

  printf(">>> copy_in returns %i\n", cbuf_copy_in("hello"));
  cbuf_print();

  printf(">>> copy_out returns %i\n", cbuf_copy_out(ignore));
  cbuf_print();

  printf(">>> copy_in returns %i\n", cbuf_copy_in("OK"));
  cbuf_print();

  printf(">>> copy_in returns %i\n", cbuf_copy_in("OK"));
  cbuf_print();

  printf(">>> copy_out returns %i\n", cbuf_copy_out(ignore));
  cbuf_print();

  printf(">>> copy_in returns %i\n", cbuf_copy_in("Bbye"));
  cbuf_print();

  printf(">>> copy_out returns %i\n", cbuf_copy_out(ignore));
  cbuf_print();

  return EXIT_SUCCESS;
}
#endif
