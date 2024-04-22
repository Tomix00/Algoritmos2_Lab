#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>

bool goes_before(int x, int y);

bool array_is_sorted(int a[], unsigned int length);

void swap(int a[], unsigned int i, unsigned int j);

#endif
