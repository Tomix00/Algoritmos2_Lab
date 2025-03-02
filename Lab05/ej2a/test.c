#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void array_show(stack_elem *array,char *name, unsigned int size){
    printf("%s: ",name);
    if(size>0){
        printf("[%d",array[0]);
        for(unsigned int i=1u;i<size;i++){
            printf(",%d",array[i]);
        }
        printf("]\n");
    }else{
        printf("[]\n");
    }
}


int main(void){

    unsigned int size;
    bool is_empty;
    stack_elem top;
    stack_elem *array;
    
    /*creacion de un stack*/
    stack st = stack_empty();
    stack empty_st = stack_empty();

    /*calculo de tamaño*/
    size = stack_size(st);
    printf("Tamaño actual del stack 'st' : %u\n",size);

    /*prueba de stack_push*/
    st = stack_push(st,1);
    st = stack_push(st,2);
    st = stack_push(st,3);
    st = stack_push(st,4);

    size = stack_size(st);
    printf("Tamaño actual del stack 'st' (after some pushes): %u\n",size);

    /*prueba de stack pop*/
    st = stack_pop(st);

    size = stack_size(st);
    printf("Tamaño actual del stack 'st' (after pop): %u\n",size);

    /*prueba de stack_top*/
    top = stack_top(st);
    printf("El top actual del stack 'st' es: %d\n",top);

    /*prueba de stack_is_empty*/
    is_empty = stack_is_empty(st);
    printf("El stack 'st' %s esta vacio.\n",is_empty ? "si" : "no");

    /*prueba de stack_to_array*/
    array = stack_to_array(st);
    array_show(array,"st",size);

    /*pruebas en stack vacio*/
    size = stack_size(empty_st);
    printf("Tamaño actual del stack 'empty_st' : %u\n",size);

    is_empty = stack_is_empty(empty_st);
    printf("El stack 'empty_st' %s esta vacio.\n",is_empty ? "si" : "no");
    
    array = stack_to_array(empty_st);
    array_show(array,"empty_st",size);

    /*destruccion de los stacks*/
    st = stack_destroy(st);
    empty_st = stack_destroy(empty_st);
    free(array);

    return EXIT_SUCCESS;
}