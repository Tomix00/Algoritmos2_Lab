#include "strfuncs.h"

size_t string_length(const char *str){
    const char *aux= str;

    size_t i = 0;

    while(aux[i]!='\0'){
        i++;
    }

    return i;
}

char *string_filter(const char *str, char c){
    const char *aux = str;
    size_t count_c=0u;

    for(unsigned int i=0u;aux[i]!='\0';i++){
        if(aux[i]==c){
            count_c++;
        }
    }
    
    size_t str_length = string_length(str)-count_c;
    char *str_ret=NULL;
    str_ret = malloc(sizeof(char)*(str_length+1));

    unsigned int pos=0u;
    for(unsigned int i=0u;aux[i]!='\0';i++){
        if(aux[i]!=c){
            str_ret[pos]=aux[i];
            pos++;
        }
    }

    return str_ret;
}

bool string_is_symetric(const char *str){
    size_t size = string_length(str)-1;
    size_t i = 0;
    bool ver = true;

    while(i!=size && ver){
        if(str[i]!=str[size]){
            ver = false;
        }
        i++;
        size--;
    }
    return ver;
}