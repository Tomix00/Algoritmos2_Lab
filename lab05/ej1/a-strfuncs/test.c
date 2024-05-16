#include <stdio.h>
#include <stdlib.h>

#include "strfuncs.h"


int main(void) {
    char *some_str="h.o.l.a m.u.n.d.o.!";
    char *some_symmetric="abcba";
    char *some_asymmetric="ab";
    char *filtered=NULL;

    filtered = string_filter(some_str, '.');
    printf("original: '%s' (%ld)\n"
           "filtrada: '%s' (%ld)\n\n",
           some_str, string_length(some_str),
           filtered, string_length(filtered),);

    free(filtered);
    filtered=NULL;

    return EXIT_SUCCESS;
}

