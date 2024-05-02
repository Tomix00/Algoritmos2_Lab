#include <stdlib.h>
#include "pair.h"

struct s_pair_t{
    elem fst;
    elem snd;
}

pair_t pair_new(int x, int y){
    pair_t p=NULL;

    p = malloc(sizeof(struct s_pair_t));
    p->fst = x;
    p->snd = y;
    return p;
}

int pair_first(pair_t p){
    elem fst = (*p).fst;
    return fst;
}

int pair_second(pair_t p){
    elem snd = (*p).snd;
    return snd;
}

pair_t pair_swapped(pair_t p){
    pair_t q = NULL;
    q = malloc(sizeof(struct s_pair_t));  
    q->fst = p->snd;
    q->snd = p->fst;
    

    return q;
}

pair_t pair_destroy(pair_t p){
    free(p);
    p = NULL;
    return p;
}
