#ifndef _SORTEDDECK_H_
#define _SORTEDDECK_H_

#include "card.h"

#include <stdbool.h>

typedef struct s_sdeck * sdeck;

sdeck sorteddeck_create(void);
sdeck sorteddeck_destroy(sdeck deck);

sdeck sorteddeck_add(sdeck deck, card c);
sdeck sorteddeck_remove(sdeck deck, card c);
card sorteddeck_first(sdeck deck);

unsigned int sorteddeck_size(sdeck deck);
unsigned int sorteddeck_redcount(sdeck deck);
unsigned int sorteddeck_blackcount(sdeck deck);

bool sorteddeck_is_empty(sdeck deck);

card* sorteddeck_to_array(sdeck deck);

void sorteddeck_dump(sdeck deck);


#endif

