#include <stdbool.h>

typedef int list_elem;

typedef struct node * list;

struct node {
    list_elem elem;
    list next;
};

/* Constructors */
    
list empty(void);
/*Crea una lista vacía.*/

list addl(list_elem e, list l);
/*Agrega el elemento e al comiendo de la lista l.*/


/* Operations */

void destroy(list l);
/*Libera memoria en caso que sea necesario*/

list copy_list(list l);
/*Devuelve una copia de la lista l*/

bool is_empty(list l);
/*Devuelve True si l es vacia*/

list_elem head(list l);
/*Devuelve el primer elemento de la lista l.
  PRECONDITION: !is_empty(l).*/

list tail(list l);
/*Devuelve la lista l sin su primer elemento.
        PRECONDITION: !is_empty(l).
        Funciona como un procedimiento por lo que el modo de uso seria algo tal que, dada x1 lista: "x1 = tail(x1);"*/

list addr(list_elem e, list l);
/*Agrega el elemento e al final de la lista l.*/

unsigned int length(list l);
/*Devuelve la cantidad de elemento de la lista l.*/

list concat(list a, list b);
/*Devuelve la lista resultante de agregar al final de a todos los elementos de b en el mismo orden.
    Funciona como un procedimiento por lo que el modo de uso seria algo tal que, dada x1 y x2 listas: "x1 = concat(x1,x2);"*/


list_elem index(unsigned int n, list l);
/*Devuelve el n-esimo elemento de la lista l.
    PRECONDITION: length(l)>n*/

list take(unsigned int n, list l);
/*Devuelve la lista resultante de dejar los primeros n elementos de la lista l, sin tener en cuenta el resto
    Funciona como un procedimiento por lo que el modo de uso seria algo tal que, dada x1 lista y n un natural: "x1 = take(n,x1);"*/

list drop(unsigned int n, list l);
/*Devuelve la lista resultante de eliminar los primeros n elementos de l
    Funciona como un procedimiento por lo que el modo de uso seria algo tal que, dada x1 lista y n un natural: "x1 = drop(n,x1);"*/

