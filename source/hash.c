#include "hash.h"
#include "lista.h"
#include "pila.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM_INI 157
#define VACIO 0

/* Definicion de la estructura hash, del nodo de hash y de su iterador.  */

typedef struct nodo_hash{
	char* clave;
	void* valor;
}nodo_hash_t;

struct hash{
	hash_destruir_dato_t destruir_dato;
	lista_t** lista;
	size_t tam;
	size_t cant;
};

struct hash_iter{
	const hash_t* hash;
	lista_iter_t* lista;
	size_t pos;
};

/* Definicion de funciones auxiliares. */
	
nodo_hash_t* nodo_hash_crear(char* clave, void* valor);

size_t hashing(const char* clave , size_t tam);

bool hash_redimensionar(hash_t* hash, size_t new_tam);

char* copy_key(const char* clave);

void destruir_listas_hash(hash_t* hash);

lista_t** crear_array_listas(size_t tam);


/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/
	
hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* hash = malloc(sizeof(hash_t));
	if(hash == NULL) return NULL;
	hash->tam = TAM_INI;
	hash->cant = VACIO;
	hash->destruir_dato = destruir_dato;
	hash->lista = crear_array_listas(hash->tam);
	if (hash->lista == NULL){
		free(hash);
		return NULL;
	}
	return hash;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	size_t pos = hashing (clave,hash->tam);
	if(hash->lista[pos] == NULL) return false;
	lista_t* lista = hash->lista[pos];
	lista_iter_t* iter = lista_iter_crear(lista);
	while(!lista_iter_al_final(iter)){
		nodo_hash_t* dupla = lista_iter_ver_actual(iter);
		if(strcmp(dupla->clave, clave) == 0){
			lista_iter_destruir(iter);
			return true;
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return false;
}

bool hash_guardar(hash_t *hash, const char *key, void *dato){
	if(hash->cant >= hash->tam * 2){
		if(!hash_redimensionar(hash,hash->tam * 2)) return false;
	}
	char* clave = copy_key (key);
	if (clave == NULL) return false;
	size_t pos = hashing (clave, hash->tam);
	if(hash->lista[pos] == NULL){
		hash->lista[pos] = lista_crear();
		if (hash->lista[pos] == NULL){
			free(clave);
			return false;
		}
	}
	lista_t* lista = hash->lista[pos];
	lista_iter_t* iter = lista_iter_crear(lista);
	while(!lista_iter_al_final(iter)){
		nodo_hash_t* dupla = lista_iter_ver_actual(iter);
		if(strcmp(dupla->clave, clave) == 0){
			if(hash->destruir_dato !=NULL){
				hash->destruir_dato(dupla->valor);
			}
			dupla->valor = dato;
			lista_iter_destruir(iter);
			free(clave);
			return true;
		}
		lista_iter_avanzar(iter);	
	}
	nodo_hash_t* nodo_hash = nodo_hash_crear(clave, dato);
	if(nodo_hash == NULL){
		free(clave);
		lista_destruir(lista,NULL);
		lista_iter_destruir(iter);
		return false;
	}
	lista_insertar_ultimo(lista,nodo_hash);
	hash->cant++;
	lista_iter_destruir(iter);
	return true;
}

void* hash_borrar(hash_t *hash, const char *clave){
	if(hash->cant * 2 <= hash->tam && hash->tam / 2 >= TAM_INI){
		if(!hash_redimensionar(hash,hash->tam / 2)) return NULL;
	}
	if(!hash_pertenece(hash,clave))return NULL;
	size_t pos = hashing (clave, hash->tam);
	lista_t* lista = hash->lista[pos];
	lista_iter_t* iter = lista_iter_crear(lista);
	while(!lista_iter_al_final(iter)){
		nodo_hash_t* dupla = lista_iter_ver_actual(iter);
		if(strcmp(dupla->clave, clave) == 0){
			void* valor = dupla->valor;
			free(dupla->clave);
			free(dupla);
			lista_iter_borrar(iter);
			lista_iter_destruir(iter);
			if(lista_esta_vacia(lista)){
				lista_destruir(lista,NULL);
				hash->lista[pos] = NULL;
			}
			hash->cant--;
			return valor;
		}
		lista_iter_avanzar(iter);	
	}
	lista_iter_destruir(iter);
	return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	size_t pos = hashing (clave, hash->tam);
	if(hash->lista[pos] == NULL) return NULL;
	lista_t* lista = hash->lista[pos];
	lista_iter_t* iter = lista_iter_crear(lista);
	while(!lista_iter_al_final(iter)){
		nodo_hash_t* dupla = lista_iter_ver_actual(iter);
		if(strcmp(dupla->clave, clave) == 0){
			lista_iter_destruir(iter);
			return dupla->valor;
		}
		lista_iter_avanzar(iter);
	}
	lista_iter_destruir(iter);
	return NULL;
}

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

void hash_destruir(hash_t *hash){
	destruir_listas_hash(hash);
	free(hash->lista);
	free(hash);
}

/* *****************************************************************
 *                  PRIMITIVAS DEL ITERADOR DEL HASH
 * *****************************************************************/
 			
hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if(iter == NULL) return NULL;
	iter->hash = hash;
	if(hash_cantidad(hash) != 0){
		for(int i = 0 ;i<hash->tam ; i++){
			if(hash->lista[i] != NULL){
				iter->lista = lista_iter_crear(hash->lista[i]);
				if(iter->lista == NULL){
					free(iter);
					return NULL;
				}
				iter->pos = i;
				return iter;
			}
		}
	}
	iter->lista = NULL;
	iter->pos = 0;
	return iter;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	if(iter->lista == NULL) return true;
	if(lista_iter_al_final(iter->lista)){
		for(size_t i = iter->pos+1 ; i<iter->hash->tam; i++){
			if(iter->hash->lista[i] != NULL)return false;
		}
		return true;
	}
	return false;	
}
	
bool hash_iter_avanzar(hash_iter_t *iter){
	if(hash_iter_al_final(iter)) return false;
	if(!lista_iter_al_final(iter->lista)){
		lista_iter_avanzar(iter->lista);
		}
	if(lista_iter_al_final(iter->lista)){
		for(size_t i = iter->pos+1 ; i<iter->hash->tam; i++){
			if(iter->hash->lista[i] != NULL){
				lista_iter_destruir(iter->lista);
				iter->pos = i;
				iter->lista = lista_iter_crear(iter->hash->lista[i]);
				if(iter->lista == NULL) return false;
				return true;
			}
		}
	}
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
	if(hash_iter_al_final(iter)) return NULL;
	nodo_hash_t * dupla = lista_iter_ver_actual(iter->lista);
	return dupla->clave;
}

void hash_iter_destruir(hash_iter_t* iter){
	lista_iter_destruir(iter->lista);
	free(iter);
}

size_t hashing (const char* clave,size_t tam){
	unsigned int num1 = 378551;
	unsigned int num2 = 63689;
	unsigned int clave_numerica = 0;
	for(int i = 0; *clave; clave++, i++){
		 clave_numerica = clave_numerica * num2 + (*clave);
		 num2 = num2 * num1;
		 }
	return (clave_numerica%tam);
}

char* copy_key(const char* key){
	char* clave = malloc((strlen(key)+1) * sizeof(char));
	if (clave==NULL) return NULL;
	strcpy(clave,key);
	return clave;
}
	
bool hash_redimensionar(hash_t* hash, size_t tam){
	lista_t** array_listas = crear_array_listas(tam);
	if (array_listas==NULL)return false;
	pila_t* pila = pila_crear();
	if(pila==NULL){
		free(array_listas);
		return false;
	}
	hash_iter_t* iter = hash_iter_crear(hash);
	if(iter==NULL) {
		free(array_listas);
		pila_destruir(pila);
		return false;
	}
	while(!hash_iter_al_final(iter)){
		nodo_hash_t * dupla = lista_iter_ver_actual(iter->lista);
		pila_apilar(pila,dupla);
		hash_iter_avanzar(iter);
	}
	while(!pila_esta_vacia(pila)){
		nodo_hash_t* par = pila_desapilar(pila);
		char* clave = par->clave;
		size_t pos = hashing (clave,tam);
		if(array_listas[pos] == NULL){
			array_listas[pos] = lista_crear();
			lista_insertar_ultimo(array_listas[pos],par);
		}
		else{
			lista_insertar_ultimo(array_listas[pos],par);
		}
	}
	for (int j = 0 ; j < hash->tam ; j++){
		if(hash->lista[j] == NULL) continue;
		lista_destruir(hash->lista[j],NULL);
	}
	hash_iter_destruir(iter);
	pila_destruir(pila);
	free(hash->lista);
	hash->lista = array_listas;
	hash->tam = tam;
	return true;
}
	
nodo_hash_t* nodo_hash_crear(char* clave, void* valor){
	nodo_hash_t* dupla = malloc(sizeof(nodo_hash_t));
	if (dupla == NULL) return NULL;
	dupla->clave = clave;
	dupla->valor = valor;
	return dupla;
}		

lista_t** crear_array_listas(size_t tam){
	lista_t** array_listas = malloc(tam * sizeof(lista_t*));
	if (array_listas == NULL)return NULL;
	for (int i = 0 ; i < tam ; i++){
		array_listas[i] = NULL;
	}
	return array_listas;
}

void destruir_listas_hash (hash_t* hash){	
	for (int i = 0 ; i < hash->tam ; i++){
		if(hash->lista[i] == NULL) continue;
		lista_t* lista = hash->lista[i];
		lista_iter_t* iter = lista_iter_crear(lista);
		while(!lista_iter_al_final(iter)){
			nodo_hash_t* dupla = lista_iter_ver_actual(iter);
			if(hash->destruir_dato !=NULL){
				hash->destruir_dato(dupla->valor);
			}
			free(dupla->clave);
			free(dupla);
			lista_iter_avanzar(iter);
		}
		lista_iter_destruir(iter);
		lista_destruir(lista,NULL);
	}
}

