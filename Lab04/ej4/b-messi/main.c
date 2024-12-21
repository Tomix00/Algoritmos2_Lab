#include <stdio.h>
#include <stdlib.h>

#include "data.h"


#include <string.h>
void
print_data(data_t d) {
    printf("NOMBRE: %s\n"
           "EDAD  : %d años\n"
           "ALTURA: %d cm\n\n",
           d.name, d.age, d.height);
}


void set_name(name_t new_name, data_t *d) {
    char *p = new_name;
    for(unsigned int i=0u;i<strlen(new_name);i++){
        d->name[i]=p[i];
    }

}

int main(void) {

    data_t messi = {"Leo Messi", 36, 169};
    print_data(messi);
    name_t messi_full_name = "Lionel Messi";

    data_t *p=NULL;
    p = &messi;
    set_name(messi_full_name,p);
    

    print_data(messi);

    return EXIT_SUCCESS;
}

