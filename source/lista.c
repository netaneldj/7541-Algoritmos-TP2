#include "lista.h"
#include <stdlib.h>
#define VACIO 0

/* Definicion de la estructura de la lista,de los nodos de la misma y de su iterador.  */

typedef struct nodo{
	void* dato;
	struct nodo* siguiente;
}nodo_lista_t;

struct lista{
	nodo_lista_t* primero;
	nodo_lista_t* ultimo;
	size_t largo;
};

struct lista_iter{
	nodo_lista_t* actual;
	nodo_lista_t* anterior;
	lista_t* lista;
};

/* Definicion de funciones auxiliares. */
	
nodo_lista_t* nodo_crear(void* valor);

bool insertar_lista_vacia(lista_t* lista, nodo_lista_t* nodo);

/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

lista_t* lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if(lista == NULL) return NULL;
	lista->largo = VACIO;
	lista->primero = NULL;
	lista->ultimo = NULL;
	return lista;
	}

bool lista_esta_vacia(const lista_t *lista){
	return lista->largo == VACIO;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_lista_t * nodo = nodo_crear(dato);
	if (nodo==NULL) return false;
	if (lista_esta_vacia(lista)) return insertar_lista_vacia(lista,nodo);
	nodo->siguiente = lista->primero;
	lista->primero = nodo;
	lista->largo ++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_lista_t * nodo = nodo_crear(dato);
	if (nodo==NULL) return false;
	if (lista_esta_vacia(lista)) return insertar_lista_vacia(lista,nodo);
	lista->ultimo->siguiente = nodo;
	lista->ultimo = nodo;
	lista->largo ++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if (lista_esta_vacia(lista)) return NULL;
	nodo_lista_t* nodo_eliminar = lista->primero;
	void* dato = nodo_eliminar->dato;
	lista->primero = lista->primero->siguiente;
	lista->largo --;
	free(nodo_eliminar);
	return dato;
}

void *lista_ver_primero(const lista_t *lista){
	if (lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->primero->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
	if (lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ultimo->dato;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while(!lista_esta_vacia(lista)){
			void* aux = lista_borrar_primero(lista);
			if(destruir_dato != NULL){
				destruir_dato(aux);
			}
	}
		free(lista);
}
	
/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/
 
lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iter = malloc(sizeof(lista_iter_t));
	if (iter == NULL) return NULL;
	iter->actual = lista->primero;
	iter->anterior = NULL;
	iter->lista = lista;
	return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if (iter->actual == NULL) return false;
	iter->anterior = iter->actual;
	iter->actual = iter->actual->siguiente;
	return true;
} 

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if (iter->actual == NULL) return NULL;
	return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	return iter->actual == NULL ;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if (lista_esta_vacia(iter->lista) || iter->actual == iter->lista->primero){  // si la lista esta vacia
		if(lista_insertar_primero(iter->lista,dato)){                            // o el actual es el primero
			iter->actual = iter->lista->primero;
			return true;
			}
		return false;
	}
	if (iter->actual == NULL && iter->anterior != NULL){  // si el iterador esta al final y
		if(lista_insertar_ultimo(iter->lista,dato)){      // y la lista no esta vacia
			iter->actual = iter->lista->ultimo;
			return true;
		}
		return false;
	}
	nodo_lista_t * nodo = nodo_crear(dato); 
	if (nodo==NULL) return false;
	iter->anterior->siguiente = nodo;
	nodo->siguiente = iter->actual;
	iter->actual = nodo;
	iter->lista->largo++;
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if (iter->actual == NULL) return NULL;
	if (iter->anterior == NULL){        
		void* dato = lista_borrar_primero(iter->lista);
		iter->actual = iter->lista->primero;
		return dato;
	}
	nodo_lista_t* nodo_eliminar = iter->actual;	
	void* dato = nodo_eliminar->dato;
	if(iter->actual == iter->lista->ultimo){
		iter->actual = iter->actual->siguiente;
		iter->anterior->siguiente = iter->actual; 
		iter->lista->ultimo = iter->anterior;
		iter->lista->largo--;
		free(nodo_eliminar);
		return dato;
	}
	iter->anterior->siguiente = iter->actual->siguiente;
	iter->actual = iter->actual->siguiente;
	iter->lista->largo--;
	free(nodo_eliminar);
	return dato;
}

/* *****************************************************************
 *                    ITERADOR INTERNO
 * *****************************************************************/

void lista_iterar(lista_t *lista, bool (*visitar)(void *dato, void *extra), void *extra){
	nodo_lista_t* nodo_actual = lista->primero;
	for (int i=0 ; i<lista->largo ; i++){
			 bool dato = visitar(nodo_actual->dato,extra);
			 if (!dato) break;
			 nodo_actual = nodo_actual->siguiente;
		 }
	 }
		

/* ********* FUNCIONES AUXILIARES  *********** */
		
nodo_lista_t* nodo_crear(void*valor){
	nodo_lista_t* nodo_nuevo = malloc(sizeof(nodo_lista_t));
	if (nodo_nuevo == NULL){
		return NULL;
	}
	nodo_nuevo->dato = valor;
	nodo_nuevo->siguiente = NULL;
	return nodo_nuevo;
}	

bool insertar_lista_vacia(lista_t* lista, nodo_lista_t* nodo){
	lista->primero = nodo;
	lista->ultimo = nodo;
	lista->largo ++;
	return true;
}
		
	

