#include <stdlib.h>
#include <assert.h>
#include "stack.h"

/*
cuanto es capacity y size?
default capacity = 10
default size = 1
*/

struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
};

bool invrep(stack s){
    bool res = (s->size)<=(s->capacity);

    return res;
}

stack stack_empty(){
    stack new_stack = malloc(sizeof(struct _s_stack));
    new_stack->capacity = 10;
    new_stack->size = 0;
    new_stack->elems = malloc(sizeof(stack_elem)*new_stack->capacity);
    
    return new_stack;
}

stack stack_push(stack s,stack_elem e){
    stack new_stack = s;

    if(s->size == s->capacity){
        new_stack->capacity = new_stack->capacity*2;
        new_stack->elems = realloc(new_stack->elems,sizeof(stack_elem)*new_stack->capacity);
    }

    new_stack->elems[new_stack->size] = e;
    new_stack->size++;

    return new_stack;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    assert(invrep(s));

    stack new_stack = s;

    new_stack->size--;

    assert(invrep(new_stack));

    return new_stack;
}

unsigned int stack_size(stack s){
    assert(invrep(s));
    unsigned int size = 0;

    size=s->size;
    
    return size;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    assert(invrep(s));

    stack_elem res = s->elems[s->size-1];

    return res;
}

bool stack_is_empty(stack s){
    assert(invrep(s));

    bool res = (s->size==0);

    return res;
}

stack_elem *stack_to_array(stack s){
    assert(invrep(s));

    stack_elem *array;
    unsigned int size = stack_size(s);

    if(size==0){
        array = NULL;
    }
    else{
        array = calloc(size, sizeof(stack_elem));

        for (unsigned int i=0; i<size; i++){
            array[i] = (s->elems)[i];
        }
    }

    return array;
}

stack stack_destroy(stack s){
    assert(invrep(s));

    free(s->elems);
    s->elems=NULL;
    free(s);
    s = NULL;
    
    return s;
}

