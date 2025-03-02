#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stack.h"

int main (void) {

    /*Crear un stack*/
    stack s = stack_empty();
    for (unsigned int i=0; i<6; i++){
        s = stack_push(s,i);
    }


    /*Prueba de stack_size*/
    unsigned int x = stack_size(s);
    printf ("El largo del stack antes del pop es: %u\n", x);


    /*Prueba de stack_pop*/
    s = stack_pop(s);
    x = stack_size(s);
    printf ("El largo del stack despues del pop es: %u\n", x);


    /*Prueba de stack_top*/
    stack_elem num = stack_top(s);
    printf("El tope del stack es %d\n", num);


    /*Prueba de stack_to_array*/
    stack_elem *array;
    array = stack_to_array(s);
    unsigned int length = stack_size(s);
    
    printf("El arreglo del stack es [");
    for (unsigned i=0; i<length-1; i++){
        printf("%d,",array[i]);
    }
    printf("%d]\n",array[length-1]);
    
    free(array);


    /*Prueba de stack_is_empty*/
    for(unsigned int i=0; i<length; i++){
        s = stack_pop(s);
    }
    if (stack_is_empty(s)){
        printf("El stack esta vacio\n");
    }


    /*Otra prueba para stack_to_array*/
    array = stack_to_array(s);
    if (array==NULL){
        printf("stack_to_array funciona bien pues para un stack vacio devolvio el puntero NULL\n");
    }


    /*Destroy*/
    s = stack_destroy(s);


    return EXIT_SUCCESS;
}