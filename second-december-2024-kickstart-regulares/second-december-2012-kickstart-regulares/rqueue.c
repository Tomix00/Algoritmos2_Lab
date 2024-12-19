#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "rqueue.h"
#include "assert.h"

struct _node_t {
    struct _node_t * links[2];
    elem_t value;
};

typedef struct _node_t * node_t;
typedef int orientation_t;

struct _rqueue_t {
    node_t extreme[2];
    orientation_t orientation;
};

static orientation_t current(rqueue_t q) {
    return q->orientation;
}

static orientation_t inverse(rqueue_t q) {
    return 1 - q->orientation;
}

rqueue_t rqueue_empty() {
    rqueue_t new_rq;
    new_rq = NULL;
    new_rq = malloc(sizeof(struct _rqueue_t));

    new_rq->extreme[0]=NULL;
    new_rq->extreme[1]=NULL;
    
    new_rq->orientation = 0;


    return new_rq;
}

bool rqueue_is_empty(rqueue_t q) {
    bool b;
    b = (q->extreme[0] == NULL);
    return b;
}

static node_t create_node(elem_t e) {
    node_t new_node;
    new_node = NULL;    
    new_node = malloc(sizeof(struct _node_t));

    new_node->links[0]=NULL;
    new_node->links[1]=NULL;
    new_node->value = e;

    return new_node;
}

rqueue_t rqueue_enqueue(rqueue_t q, elem_t e) {
    node_t new_node = NULL;
    node_t aux = NULL;
    orientation_t prev;
    orientation_t next;
    orientation_t fst;
    orientation_t lst;
    
    fst = current(q);
    lst = inverse(q);
    prev = current(q);
    next = inverse(q);

    assert(q != NULL);
    new_node = create_node(e);
    
    if(rqueue_is_empty(q)) {
        q->extreme[prev] = new_node;
        q->extreme[lst] = new_node;
        
    }
    else {
        aux = q->extreme[fst];
        new_node->links[prev] = NULL;
        new_node->links[next] = aux; 
        aux->links[prev] = new_node;
        q->extreme[fst] = new_node;

    }
    return q;
}

elem_t rqueue_fst(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));
    return q->extreme[current(q)]->value;
}

void rqueue_dequeue(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));
    
    orientation_t prev;
    orientation_t next;
    orientation_t fst;
    orientation_t lst;

    fst = current(q);
    lst = inverse(q);
    prev = current(q);
    next = inverse(q);

    node_t aux1 = NULL;
    node_t aux2 = NULL;

    aux1 = q->extreme[fst]; 
    aux2 = aux1->links[next];
    
    if(q->extreme[fst] == q->extreme[lst]){
        free(aux1);
        q->extreme[fst] = NULL;
        q->extreme[lst] = NULL;
        
    }else{
        free(aux2->links[prev]);
        aux2->links[prev] = NULL;
        q->extreme[fst] = aux2; 
    }
    
}

void rqueue_revert(rqueue_t q) {
    q->orientation = inverse(q);
}

rqueue_t rqueue_destroy(rqueue_t q) {
    while(!(rqueue_is_empty(q))){
        rqueue_dequeue(q);
    }
    free(q);
    q = NULL;

    return q;
}

void rqueue_dump(rqueue_t q) {
    orientation_t next;
    orientation_t fst;
    node_t aux = NULL;
    elem_t elem;
    assert(q != NULL);
    next = inverse(q);
    fst  = current(q);
    aux = q->extreme[fst];
    printf("\n Queue:");
    while(aux != NULL) {
        elem = aux->value;
        printf("%d ",elem);
        aux = aux->links[next];
    }
    printf("\n");
}
