#include <limits.h>
#include "array_helpers.h"

int menor_temperatura_minima(WeatherTable array);
/*devuelve la menor de las menores temperaturas de weathertable*/

void mayor_temperatura_maxima(WeatherTable array,int maximos[YEARS]);
/*toma y llena un arreglo con el maximo de cada año*/

void precipitaciones(WeatherTable array, int meses_p[YEARS]);
/*devuelve una lista con los meses donde hubo mas precipitaciones por año*/
