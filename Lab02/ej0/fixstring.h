#ifndef _FIXSTRING_H_
#define _FIXSTRING_H_

#include <stdbool.h>

#define FIXSTRING_MAX 100

typedef char fixstring [FIXSTRING_MAX];

unsigned int fstring_length(fixstring s);

bool fstring_eq(fixstring s1, fixstring s2);

bool fstring_less_eq(fixstring s1, fixstring s2);

#endif

