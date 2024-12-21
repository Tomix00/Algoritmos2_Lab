#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"

list empty(void){
    return NULL;
}


list addl(list_elem e, list l){
    list p = malloc(sizeof(struct node));

    (*p).elem = e;
    (*p).next = l;

    return p;
}


void destroy(list l){
    list p = l;
    
    if (p!=NULL){
        if(((*p).next)!=NULL){
            p = (*p).next;
            destroy(p);
        }
        free(p);
    }
}



list copy_list(list l){
    list res;

    if (l==NULL){
        res = NULL;
    }
    else{
        list p;
        list q;
        res = malloc(sizeof(struct node));
        p = l;
        q = res;

        while(((*p).next)!=NULL){
            (*q).elem = (*q).elem;
            (*q).next = malloc(sizeof(struct node));
            q = (*q).next;
            p = (*p).next;
        }
        (*q).elem = (*p).elem;
        (*q).next = NULL;
    }

    return res;
}


bool is_empty(list l){
    bool res;
    res = (l==NULL);

    return res;
}


list_elem head(list l){
    assert(!(is_empty(l)));
    
    list_elem res;
    res = (*l).elem;

    return res;
}


list tail(list l){
    assert(!(is_empty(l)));

    list res;
    res = (*l).next;

    free(l);
    return res; 
}


list addr(list_elem e, list l){
    list p;
    list q;
    p = l;

    if (p!=NULL){
        q = p;

        while (((*p).next)!=NULL){
            p = (*p).next;
        }

        (*p).next = malloc(sizeof(struct node));
        p = (*p).next;
        (*p).next = NULL;
        (*p).elem = e;
    }
    else {
        p = malloc(sizeof(struct node));
        (*p).next = NULL;
        (*p).elem = e;
        q = p;
    }
    
    

    return q;
}
   

unsigned int length(list l){
    unsigned int res;
    
    if(l==NULL){
        res = 0;
    }
    else{
        res = 1;
        list p;
        p = l;
    
        while (((*p).next)!=NULL) {
            p = (*p).next;
            res++;
        }
    }

    return res;
}


list concat(list a, list b){
    list res;
    if (a==NULL){
        res = b;
    }
    else{
        list p;
        res = a;
        p = a;
    
        while (((*p).next)!=NULL){
                p = (*p).next;
        }

        (*p).next = b;
    }

    return res;
}


list_elem index(unsigned int n, list l){
    assert(n<length(l));

    list_elem res;
    unsigned int i;
    list p;
    i = 0;
    p = l;

    while (i<n){
        p = (*p).next;
        i++;
    }
    res = (*p).elem;

    return res;
}


list take(unsigned int n, list l){
    list res;
    list p;
    unsigned int i;
    res = l;
    p = l;
    i = 0;

    while ((i<n)&&(p!= NULL)){
        p = (*p).next;
        i++;
    }
    p = NULL;

    return res;
}


list drop(unsigned int n, list l){
    list res;
    unsigned int i;
    list p;
    res = l;
    i = 0;

    while ((i<n)&&(res!= NULL)){
        p = res;
        res = (*res).next;
        free(p);
        i++;
    }
    
    return res;
}


