#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "array_helpers.h"
#include "sort_helpers.h"
#include "sort.h"


static void insert(int a[], unsigned int i) {
    
    unsigned int j;
    for(j=i;j>1 && goes_before(a[j],a[j-1]);j--){
        swap(a,j-1,j);
    }
}

void insertion_sort(int a[], unsigned int length) {
    for (unsigned int i = 1u; i < length; ++i) {
        
        insert(a, i);
        assert(array_is_sorted(a,i));
    }
}

