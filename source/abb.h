#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct abb;
struct abb_iter;
typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;
typedef struct abb_iter_post abb_iter_post_t; 

typedef struct abb_item{
    const char* clave;
    void* valor;
} abb_item_t;

// tipo de función para destruir dato y tipo de funcion para comparar claves.

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);



/* ******************************************************************
 *                    PRIMITIVAS DE LA ABB
 * *****************************************************************/

/* Crea un ABB.
 *  cmp es la funcion de comparacion de claves y destruir dato es la funcion
 *que se encarga de destruir los datos. 
 * Post: devuelve un ABB vacio o NULL en caso de fallar.
 */
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);


/* Guarda un dato en el ABB. Si la clave ya existe reemplaza el dato anterior
 * por el nuevo, sino guarda la clave y el dato.
 * Pre: El ABB fue creado.
 * Post: Devuelve true si guardo el dato, o false en caso contrario.
 */
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

/* Borra un dato del ABB, si la clave ya se encuentra en la estructura, sino devuelve
 * NULL en caso de no estar la clave.
 * Pre: El ABB fue creado.
 * Post: Devuelve el dato asociado a la clave o devuelve NULL en caso contrario.
 */
void *abb_borrar(abb_t *arbol, const char *clave);

/* Obtiene el dato asociado a la clave, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura ABB fue inicializada.
 */
void *abb_obtener(const abb_t *arbol, const char *clave);

/* Determina si clave pertenece o no al ABB.
 * Pre: La estructura hash fue inicializada.
 */
bool abb_pertenece(const abb_t *arbol, const char *clave);

/* Devuelve la cantidad de elementos del ABB.
 * Pre: La estructura ABB fue inicializada
 */
size_t abb_cantidad(const abb_t *arbol);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada dato.
 * Pre: La estructura ABB fue inicializada
 * Post: La estructura ABB fue destruida
 */
void abb_destruir(abb_t *arbol);


/* Devuelve un arreglo con todos los datos del árbol ordenados por clave,
 * donde cada posicion es una estructura que posee (clave,valor)
 * Pre: La estructura ABB fue inicializada
 * Post: La estructura ABB fue destruida
 */
abb_item_t* abb_obtener_items(const abb_t*);

/* ******************************************************************
 *             PRIMITIVAS DEL ITERADOR EXTERNO INORDER DEL ABB
 * *****************************************************************/


/* Crea un iterador de tipo "inorder" para el ABB provisto como parámetro.
 * Pre: El ABB fue creado.
 * Post: Se devuelve el iterador o NULL en otro caso.
 */
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

/* Avanza el iterador devolviendo true si pudo sino false en caso contrario.
 * Pre: La estructura ABB fue creada.
 * Post: Se devolvio true si avanzo o false en caso contrario.
 */
bool abb_iter_in_avanzar(abb_iter_t *iter);

/* Devuelve clave actual, esa clave no se puede modificar ni liberar.
 * Pre: La estructura ABB fue creada.
 * Post: Se devolvio la clave donde esta posicionado el iterador.
 */
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

/*Comprueba si terminó la iteración.
 * Pre: La estructura ABB fue creada.
 * Post: Se devolvio true si esta al final o false en caso contrario.
 */
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye iterador.
void abb_iter_in_destruir(abb_iter_t* iter);

/* ******************************************************************
 *             PRIMITIVAS DEL ITERADOR EXTERNO POSTORDER DEL ABB
 * *****************************************************************/


/* Crea un iterador de tipo "postorder" para el ABB provisto como parámetro.
 * Pre: El ABB fue creado.
 * Post: Se devuelve el iterador o NULL en otro caso.
 */
abb_iter_post_t *abb_iter_post_crear(const abb_t *arbol);

/* Avanza el iterador devolviendo true si pudo sino false en caso contrario.
 * Pre: La estructura ABB fue creada.
 * Post: Se devolvio true si avanzo o false en caso contrario.
 */
bool abb_iter_post_avanzar(abb_iter_post_t *iter);

/* Devuelve clave actual, esa clave no se puede modificar ni liberar.
 * Pre: La estructura ABB fue creada.
 * Post: Se devolvio la clave donde esta posicionado el iterador.
 */
const char *abb_iter_post_ver_actual(const abb_iter_post_t *iter);

/*Comprueba si terminó la iteración.
 * Pre: La estructura ABB fue creada.
 * Post: Se devolvio true si esta al final o false en caso contrario.
 */
bool abb_iter_post_al_final(const abb_iter_post_t *iter);

// Destruye iterador.
void abb_iter_post_destruir(abb_iter_post_t *iter);

/* *****************************************************************
 *            PRIMITIVAS DEL ITERADOR INTERNO INORDER
 * ****************************************************************/

// Itera el ABB mientras la funcion de callback "visitar" devuelve TRUE 
// y no esté al final del ABB.
// Pre: El ABB fue creado.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* *****************************************************************
 *            PRIMITIVAS DEL ITERADOR INTERNO POSTORDER
 * ****************************************************************/

// Itera el ABB mientras la funcion de callback "visitar" devuelve TRUE 
// y no esté al final del ABB.
// Pre: El ABB fue creado.

void abb_post_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * ****************************************************************/

// Realiza pruebas sobre la implementación del alumno.

void pruebas_abb_alumno(void);

#endif // ABB_H
