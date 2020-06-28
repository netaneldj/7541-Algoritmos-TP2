#ifndef STRUTIL_H
#define STRUTIL_H

#include <stddef.h>

/*
 * Devuelve en un arreglo dinamico terminado en NULL con todos los subsegmentos
 * del 'str' separados por el caracter 'sep'. Tanto el arreglo devuelto como las
 * cadenas que contiene son allocadas dinamicamente.
 *
 * Quien llama a la funcion toma responsabilidad de la memoria dinamica del
 * arreglo devuelto. La funcion devuelve NULL si falla alguna llamada a
 * malloc(), o si 'sep' es '\0'.
 */
char** split(const char* str, char sep);

/*
 * Devuelve una cadena, allocada dinamicamente, resultado de unir todas las
 * cadenas del arreglo terminado en NULL 'strv'.
 *
 * Quien llama a la funcion toma responsabilidad de la memoria dinamica de la
 * cadena devuelta. La funcion devuelve NULL si no se pudo allocar memoria.
 */
char* join(char** strv, char sep);

/*
 * Libera un arreglo dinamico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char* strv[]);

#endif  // STRUTIL_H
