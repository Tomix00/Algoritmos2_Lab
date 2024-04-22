#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>

#include "fixstring.h"

bool array_is_permutation_of(fixstring a[], fixstring other[], unsigned int length);

void array_dump(fixstring a[], unsigned int length);

void array_copy(fixstring dst[], fixstring src[], unsigned int length);

unsigned int array_from_file(fixstring a[], unsigned int max_size, const char *filepath);

#endif
