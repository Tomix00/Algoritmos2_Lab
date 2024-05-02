#include "pair.h"

pair_t pair_new(int x, int y){
    pair_t p;
    p.values[0] = x;
    p.values[1] = y;
    return p;
}

int pair_first(pair_t p){
    int fst;
    fst = p.values[0];
    return fst;
}

int pair_second(pair_t p){
    int snd;
    snd = p.values[1];
    return snd;
}

pair_t pair_swapped(pair_t p){
    int aux;
    aux = p.values[0];
    p.values[0] = p.values[1];
    p.values[1] = aux;
    return p;
}

pair_t pair_destroy(pair_t p){
    p.values[0]=0;
    p.values[1]=0;
    return p;
}