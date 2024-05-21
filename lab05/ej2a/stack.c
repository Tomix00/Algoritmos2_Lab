#include <stdlib.h>
#include <assert.h>

#include "stack.h"

struct _s_stack{
    stack_elem elem;
    stack next;
};

stack stack_empty(){
    return NULL;
}

//misma idea que addl
stack stack_push(stack s , stack_elem e){
    stack new_stack;

    new_stack = malloc(sizeof(struct _s_stack));    
    new_stack->elem = e;
    new_stack->next = s;

    return new_stack;
}

//misma idea que tail
stack stack_pop(stack s){
    assert(!stack_is_empty(s));

    // stack ptr_stack = s;
    // s = s->next;
    // free(ptr_stack);
    // ptr_stack = NULL;
    // return s;

    stack ptr_stack = s;
    ptr_stack = ptr_stack->next;
    free(s);

    return ptr_stack;
}

unsigned int stack_size(stack s){
    stack ptr_stack = s;
    unsigned int size=0;
    
    while(ptr_stack != NULL){
        ptr_stack = ptr_stack->next;
        size++;
    }
    return size;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));

    stack ptr_stack = s;
    stack_elem elem = ptr_stack->elem;

    return elem;
}

bool stack_is_empty(stack s){
    bool res;
    res = (s == NULL);
    return res;
}

stack_elem *stack_to_array(stack s){
    unsigned int size = stack_size(s);
    
    stack_elem *array=NULL;
    
    if(size>0){
        stack ptr_stack = s;
        array = calloc(size,sizeof(stack_elem));

        // unsigned int i=size;
        // while(ptr_stack->next != NULL){
        //     array[i] = ptr_stack->elem;
        //     ptr_stack = ptr_stack->next;
        //     i--;
        // }

        for(int i=size-1;i>=0;i--){
            array[i] = ptr_stack->elem;
            ptr_stack = ptr_stack->next;
        }
    }

    return array;
}

stack stack_destroy(stack s){
    if (s != NULL){
        stack_destroy(s->next);
        free(s);
    }
    s = NULL;

    return s;
}