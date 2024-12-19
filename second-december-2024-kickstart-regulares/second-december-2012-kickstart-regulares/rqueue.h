#ifndef RQUEUE_H
#define RQUEUE_H
#include <stdbool.h>

typedef struct  _rqueue_t *rqueue_t;
typedef int elem_t;



rqueue_t rqueue_empty();
rqueue_t rqueue_enqueue(rqueue_t q, elem_t e);
bool rqueue_is_empty(rqueue_t q);
elem_t rqueue_fst(rqueue_t q);
void rqueue_dequeue(rqueue_t q);
void rqueue_revert(rqueue_t q);
rqueue_t rqueue_destroy(rqueue_t q);
void rqueue_dump(rqueue_t q);

#endif
