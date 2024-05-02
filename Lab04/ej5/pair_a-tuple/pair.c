#include "pair.h"
#include <assert.h>

pair_t pair_new(int x, int y){
    pair_t p;
    p.fst = x;
    p.snd = y;
    
    return p;
}

int pair_first(pair_t p){
    int fst;
    fst = p.fst;

    return fst;
}


int pair_second(pair_t p){
    int snd;
    snd = p.snd;

    return snd;
}

pair_t pair_swapped(pair_t p){
    pair_t aux;
    aux.fst=p.snd;
    aux.snd = p.fst;
    
    return aux;
}

pair_t pair_destroy(pair_t p){
    p.fst=0;
    p.snd=0;
    return p;
}
