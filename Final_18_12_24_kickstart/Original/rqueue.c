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
    rqueue_t new_rqueue;
    new_rqueue = NULL;
    new_rqueue = malloc(sizeof(struct _rqueue_t));  //must free after all nodes are freed

    new_rqueue->extreme[0] = NULL;  //left corner 
    new_rqueue->extreme[1] = NULL;  //right corner
    new_rqueue->orientation = 0;    //from left to right(->)

    return new_rqueue;
}

bool rqueue_is_empty(rqueue_t q) {
    bool b;

    b = (q->extreme[0]==NULL && q->extreme[1]==NULL);

    return b;
}

static node_t create_node(elem_t e) {
    node_t new_node;
    new_node = NULL;
    new_node = malloc(sizeof(struct _node_t));  //must free before free rqueue

    new_node->links[0] = NULL;
    new_node->links[1] = NULL;
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

    prev = current(q);
    next = inverse(q);
    fst = current(q);
    lst = inverse(q);

    assert(q != NULL);

    new_node = create_node(e);
    
    if(rqueue_is_empty(q)) {
        q->extreme[fst] = new_node;
        q->extreme[lst] = new_node;
    }
    else {
        aux = q->extreme[lst];
        aux->links[next] = new_node;    //add the new node on the far right
        new_node->links[prev] = aux;    //set the previous node of new_node to be the actual one
        new_node->links[next] = NULL;
        q->extreme[lst] = new_node;        
    }
    return q;
}

elem_t rqueue_fst(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));

    elem_t fst;
    fst = q->extreme[current(q)]->value;

    return fst;
}

void rqueue_dequeue(rqueue_t q) {
    assert(q != NULL);
    assert(!rqueue_is_empty(q));

    orientation_t prev;
    orientation_t next;
    orientation_t fst;
    orientation_t lst;

    prev = current(q);
    next = inverse(q);
    fst = current(q);
    lst = inverse(q);

    
    if(q->extreme[fst] == q->extreme[lst]){ //has only one element left
        free(q->extreme[fst]);
        q->extreme[fst] = NULL;
        q->extreme[lst] = NULL;
        
    }else{  //has more than one element
        node_t aux;
        node_t aux2;
        aux = q->extreme[lst];
        aux2 = aux->links[prev];
        free(aux);
        aux2->links[next] = NULL;
        q->extreme[lst] = aux2;        
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
