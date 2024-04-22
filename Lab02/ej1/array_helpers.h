#ifndef _ARRAY_HELPERS_H
#define _ARRAY_HELPERS_H

#include <stdbool.h>

bool array_is_permutation_of(int a[], int other[], unsigned int length);

void array_dump(int a[], unsigned int length);

void array_copy(int dst[], int src[], unsigned int length);

unsigned int array_from_file(int a[], unsigned int max_size, const char *filepath);

#endif
