#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>

#include "fixstring.h"

bool goes_before(fixstring x, fixstring y);

bool array_is_sorted(fixstring a[], unsigned int length);

void swap(fixstring a[], unsigned int i, unsigned int j);

#endif
