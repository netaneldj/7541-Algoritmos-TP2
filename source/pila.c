#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t tam;
    size_t largo;
};

/*Declaro la funcion auxiliar redimensionar_pila y la variable entera tamanio inicial*/

bool redimensionar_pila(pila_t* pila , size_t nuevo_tam);
const int tam_inicial = 8;

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if (pila == NULL) {
        return NULL;
	}
	pila->datos = malloc(tam_inicial * sizeof(void*));
	if (pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila->tam = tam_inicial;
	pila->largo = 0;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	if(pila->largo == 0){
		return true;
	}
	return false;
}

bool pila_apilar(pila_t *pila, void* valor){
	if(pila->largo == pila->tam){
		if(!redimensionar_pila(pila , pila->largo * 2)){
			return false;
		}
	}
	pila->datos[pila->largo] = valor;
	pila->largo++;
	return true;
}

void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	return pila->datos[(pila->largo)-1];
}

void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	if(pila->largo == pila->tam / 4 && pila->largo * 2 >= tam_inicial){
		if(!redimensionar_pila(pila , pila->largo * 2)){
			return NULL;
		}
	}
	pila->largo--;
	return pila->datos[(pila->largo)];
}

/*Funcion auxiliar para redimensionar las pilas*/

bool redimensionar_pila(pila_t* pila , size_t nuevo_tam){
	if(nuevo_tam < tam_inicial ){
		return false;
	}
	void* pila_nueva = realloc(pila->datos,nuevo_tam * sizeof(void*));
	if(pila_nueva == NULL){
		return false;
	}
	pila->datos = pila_nueva;
	pila->tam = nuevo_tam;
	return true;
}
	
		 
	
	






		


