#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "rqueue.h"
#include "helpers.h"

#define OPTION_ENQUEUE 'e'
#define OPTION_DEQUEUE 'd'
#define OPTION_REVERT 'r'
#define OPTION_EXIT 'q'

bool option_is_valid (char option) {
    return (option == OPTION_ENQUEUE
            || option == OPTION_DEQUEUE
            || option == OPTION_REVERT
            || option == OPTION_EXIT);
}

char get_option() {
    printf("\n%c Enqueue  \n",OPTION_ENQUEUE);
    printf("%c Dequeue  \n",OPTION_DEQUEUE);
    printf("%c Revert \n",OPTION_REVERT);
    printf("%c Exit \n",OPTION_EXIT);
    char * opt = readline_from_stdin();
    char c = 0;
    if(opt != NULL) {
        c = opt[0];
        free(opt);
        opt = NULL;
    }
    return (c);
}

int read_int() {
    char * l = NULL;
    int e = 0;
    l = readline_from_stdin();
    sscanf(l,"%d",&e);
    free(l);
    l = NULL;
    return e;
}

rqueue_t on_enqueue(rqueue_t q) {
    int e;
    printf("\n Inserte un entero: \n");
    e = read_int();
    q = rqueue_enqueue(q,e);
    rqueue_dump(q);
    return q;
}

void on_dequeue(rqueue_t q) {
    if(!rqueue_is_empty(q)) {
        rqueue_dequeue(q);
    }
    rqueue_dump(q);
}

void on_revert(rqueue_t q) {
    rqueue_revert(q);
    rqueue_dump(q);
}

int main(void) {
    rqueue_t r = NULL;
    char c = 0;
    r = rqueue_empty();
    do {
        c = get_option();
        switch(c) {
            case OPTION_ENQUEUE: r = on_enqueue(r); break;
            case OPTION_DEQUEUE: on_dequeue(r); break;
            case OPTION_REVERT: on_revert(r); break;
            case OPTION_EXIT: break;
            default: printf("Opción inválida \n"); break;
        }
    } while(c != OPTION_EXIT);
    r = rqueue_destroy(r);
}
