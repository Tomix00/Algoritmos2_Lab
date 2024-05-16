#include "strfuncs.h"

size_t string_length(const char *str){
    char *aux=str;
    size_t count=0;
    while (*aux!='\0'){
        count++;
    }
    
    return count;
}

char *string_filter(const char *str, char c){
    char *aux=str;
    size_t count=0;
    while(*aux!='\0'){
        if(*aux==c){
            count++;
        }
    }
    
    size_t len = string_length(str);
    printf("cantidad de '%c' es: %ld\n",c,count);
    printf("tamño del original: %ld\n",len);
    printf("tamaño arreglo final: %ld\n",len - count);

    return "hola";
}