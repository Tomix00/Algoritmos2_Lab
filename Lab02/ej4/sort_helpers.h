#ifndef _SORT_HELPERS_H
#define _SORT_HELPERS_H

#include <stdbool.h>

bool goes_before(int x, int y);

bool array_is_sorted(int a[], unsigned int length);

void swap(int a[], unsigned int i, unsigned int j);

void reset_comparisons_counter();

unsigned int comparisons_number();

void reset_swaps_counter();

unsigned int swaps_number();

void set_current_time();

double calculate_elapsed_time();

#endif
