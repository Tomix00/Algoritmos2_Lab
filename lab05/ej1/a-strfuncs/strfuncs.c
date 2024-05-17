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

bool string_is_symmetric(const char *str){
    bool bool_ret;
    size_t length = string_length(str);

    if (length==0 || length==1){
        bool_ret = true;

    }else if(length==2){
        bool_ret = false;

    }else{
        size_t count=0,dec=0;
        bool creciente=false,decreciente=false;
        const char *aux=str;

        unsigned int i=0u;
        while(i<length-1 && aux[i]<aux[i+1]){
            count++;
            i++;
        }
        if(count<length){
            creciente = true;
        }
        unsigned int j = count;
        while (j<length-1 && creciente){
            if(aux[j]<aux[j+1]){
                creciente = false;
            }
            dec++;
            j++;
        }
        if (dec == length-(count+1)){
            decreciente = true;
        }
        bool_ret = creciente && decreciente;
    }

    return bool_ret;
}
