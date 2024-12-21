/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

unsigned int array_from_file(int array[],unsigned int max_size) {

    unsigned int tamaño;
    fscanf(stdin,"%u",&tamaño);//primera fila->  tamaño del array

    assert(tamaño<max_size);

    for (unsigned int i=0;i<tamaño;i++){
        fscanf(stdin,"%d",&array[i]);
    }

    return tamaño;
    
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i=0;i<length;i++){
        printf("%d,",a[i]);
    }
    printf("]\n");
}


int main(void) {
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];

    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE);

    /*dumping the array*/
    array_dump(array, length);

    return EXIT_SUCCESS;
}