#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista enlazada de punteros genéricos. */

struct lista;
struct lista_iter;
typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

// Devuelve verdadero o falso, según si la lista tiene o no elementos en ella.
// Pre: la cola fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento en la primera posicion de la lista.
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al
// comienzo de la misma.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento en la ultima posicion de la lista.
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, dato se encuentra al
// final de la misma.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos
// quita el primero de la lista y devuelve su valor, 
// si esta vacia devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, la misma contiene un
// elemento menos si no estaba vacía. 
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no esté vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no esté vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene la cantidad de elementos de la lista. Si la lista tiene elementos,
// devuelve la cantidad, si esta vacia devuelve 0.
// Pre: La lista fue creada.
// Post: se devolvio la cantidad de elementos de la lista,si no esta vacia. 
size_t lista_largo(const lista_t *lista);


/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

// Crea un iterador.
// Post: devuelve un iterador para la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza la posicion del iterador en la lista.
// Devuelve false en caso de error.
// Pre: El iterador y la lista a iterar fueron creadas.
// Post: se avanzo una posicion en la lista, en caso de que
// no este vacia o en el final de la misma.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento de la lista donde esta posicionado 
// el iterador y lo devuelve, si esta al final devuelve NULL.
// Pre: El iterador y la lista a iterar fueron creadas.
// Post: Se devolvio el elemento de la lista donde estaba el iterador.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero o falso, según si el iterador esta o no al final de la lista.
// Pre: El iterador y la lista a iterar fueron creadas.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: El iterador fue creado.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento en la posicion de la lista donde se 
// encuentra el iterador. Devuelve falso en caso de error.
// Pre: El iterador y la lista a iterar fueron creadas.
// Post: Se agrego un nuevo elemento en la lista. dato se encuentra
// en la posicion de la lista donde esta el iterador.
// La lista tiene un elemento mas.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Saca el elemento de la posicion de la lista donde se encuentra el 
// iterador y lo devuelve, si esta vacia o al final devuelve NULL.
// Pre: El iterador y la lista a iterar fueron creadas.
// Post: Se devolvio el elemento de la lista donde se encontraba
// el iterador. La lista tiene un elemento menos si no estaba vacia.
void *lista_iter_borrar(lista_iter_t *iter);


/* *****************************************************************
 *                      PRIMITIVAS DEL ITERADOR INTERNO
 * ****************************************************************/

// Itera la lista mientras la funcion de callback "visitar" devuelve TRUE 
// y no esté al final de la lista.
// Pre: La lista fue creada.
void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * ****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en cola.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H
