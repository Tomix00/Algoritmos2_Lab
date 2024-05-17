#include <stdbool.h>
#include <stdlib.h>

size_t string_length(const char *str);
//{devuelve el tamaño del string}

char * string_filter(const char *str, char c);
//{devuelve otro string sin el caracter c}

bool string_is_symmetric(const char *str);
//{verifica si el string es palindromo}
