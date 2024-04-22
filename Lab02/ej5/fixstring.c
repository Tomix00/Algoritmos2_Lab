#include <stdbool.h>
#include <assert.h>

#include "fixstring.h"


unsigned int fstring_length(fixstring s) {
    unsigned int count=0;
    unsigned int i=0;
    while (s[i] != '\0'){
        count++;
        i++;
    }
    return count;
}

bool fstring_eq(fixstring s1, fixstring s2) {
    bool iguales=true;

   if (fstring_length(s1) != fstring_length(s2)){
    iguales = false;
   }else{
    unsigned int tam = fstring_length(s1);
    for (unsigned int i=0;i<tam && iguales;i++){
        if (s1[i] != s2[i]){
            iguales = false;
        }
    }
   }
   return iguales;
}

bool fstring_less_eq(fixstring s1, fixstring s2) {

    bool res = fstring_length(s1)<=fstring_length(s2);
    unsigned int i = 0;

    while (i<fstring_length(s1) && i<fstring_length(s2)) {

        if (s1[i]==s2[i]) {
            i=i+1;
        } else {
            if (s1[i]<s2[i]) {
                res=true;
                i=101;
            } else {
                res=false;
                i=101;
            }
        }
       
    }


 return res;
}

void fstring_set(fixstring s1, const fixstring s2) {
    int i=0;
    while (i<FIXSTRING_MAX && s2[i]!='\0') {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = '\0';
}

void fstring_swap(fixstring s1,  fixstring s2) {
    fixstring aux;
    
    fstring_set(aux,s2);
    fstring_set(s2,s1);
    fstring_set(s1,aux);

}



