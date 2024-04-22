#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "array_helpers.h"


unsigned int array_from_file(int array[],unsigned int max_size,const char *filepath) {

    FILE *lista = fopen (filepath, "r");
    unsigned int longitud;
    fscanf (lista, "%u", &longitud);
    assert (longitud<max_size);
    unsigned int i=0;
    while (i<longitud) {
        fscanf (lista, "%d", &array[i]);
        i=i+1;
    }
    fclose (lista);

    return longitud;
}

void array_dump(int a[], unsigned int length) {

    printf("[ ");
    for (unsigned int cont = 0; cont<length; cont++) {
        printf("%d ", a[cont]);
    } 
    printf("]\n");
}

bool array_is_sorted(int a[], unsigned int length){
    bool orden = true;
    for(unsigned int i=0;i<length-1;i++){
        orden = orden && (a[i]<=a[i+1]);
    }
    return orden;
}