#ifndef RQUEUE_H
#define RQUEUE_H
#include <stdbool.h>

typedef struct  _rqueue_t *rqueue_t;
typedef int elem_t;

/**
    @brief Create an empty rqueue
    @return An empty rqueue
*/
rqueue_t rqueue_empty();

/**
    @brief Add one element to the rqueue
    @param q rqueue
    @param e An element to enqueue into the rqueue
    @return rqueue with one more element
*/
rqueue_t rqueue_enqueue(rqueue_t q, elem_t e);

/**
    @brief Check if the rqueue is empty
    @param q rqueue
    @return True or False
*/
bool rqueue_is_empty(rqueue_t q);

/**
    @brief Get the first element of the rqueue
    @param q rqueue
    @return The first element of the rqueue
    @note Only applies to non empty rqueue
*/
elem_t rqueue_fst(rqueue_t q);

/**
    @brief Delete one element from the rqueue
    @param q rqueue
    @note Only applies to non empty rqueue
*/
void rqueue_dequeue(rqueue_t q);

/**
    @brief Change the orientation to read the rqueue
    @param q rqueue
*/
void rqueue_revert(rqueue_t q);

/**
    @brief Destroy the rqueue
    @param q rqueue
    @return NULL
    @note all memories resources are freed
*/
rqueue_t rqueue_destroy(rqueue_t q);

void rqueue_dump(rqueue_t q);

#endif
