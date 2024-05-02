#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"

void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);

    printf("name-size  : %lu bytes\n"
           "age-size   : %lu bytes\n"
           "height-size: %lu bytes\n"
           "data_t-size: %lu bytes\n",sizeof(messi.name),
                                      sizeof(messi.age),
                                      sizeof(messi.height),
                                      sizeof(data_t));
    
    data_t *p=NULL;
    printf("data name size    : %p bytes\n"
           "data age size     : %p bytes\n"
           "data height size  : %p bytes\n", (void *)(&p->name),
                                             (void *)(&p->age),
                                             (void *)(&p->height));


    return EXIT_SUCCESS;
}


