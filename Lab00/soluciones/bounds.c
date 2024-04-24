#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>
#define ARRAY_SIZE 4


struct bound_data {
    bool is_upperbound;
    bool is_lowerbound;
    bool exists;
    unsigned int where;
};

struct bound_data check_bound(int value, int arr[], unsigned int length) {
    struct bound_data res;
    unsigned int i=0;
    res.is_lowerbound = true;
    res.is_upperbound = true;
    res.exists = false;
    res.where = 0;

    while (i<length){

        res.is_upperbound = res.is_upperbound && (value >= arr[i]);
        res.is_lowerbound = res.is_lowerbound && (value <= arr[i]);

        if (value == arr[i]){
            res.exists = true;
            res.where = i;
        }
        i++;
    }

    return res;
}

void pedir_arreglo(int tam, int a[]){
    int i=0;

    while (i<tam){
        printf("Ingrese valor para la posicion %d: ",i);
        scanf("%d",&a[i]);
        assert((INT_MIN<a[i]) && (a[i]<INT_MAX));
        i++;
    }
}

int pedir_entero(){
    int a;
    printf("Ingrese un entero para comparar: ");
    scanf("%d",&a);
    return a;
}

int main(void) {
    int a[ARRAY_SIZE];
    pedir_arreglo(ARRAY_SIZE,a);
    int value;
    value = pedir_entero();
    struct bound_data result = check_bound(value, a, ARRAY_SIZE);
    
    
    if (result.exists && result.is_lowerbound){
        printf("%d es un minimo, con posicion: %u \n", value, result.where);
    } else if (result.is_lowerbound){
	    printf("%d es un cota inferior. \n", value);
    }

    if (result.exists && result.is_upperbound){
	    printf("%d es un maximo, con posicion: %u \n", value,result.where);	
    } else if (result.is_upperbound){
    	printf("%d es un cota superior. \n", value);
    }

    if (!result.exists && !result.is_lowerbound && !result.is_upperbound){
	    printf("el valor no se encuentra en la lista. \n");
    }
    return EXIT_SUCCESS;
}

