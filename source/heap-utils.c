#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector_dinamico.h"
#include "heap.h"

int comparar (const void* a, const void* b){
	char* dir_a = (char*)a;
	char* dir_b = (char*)b;
	if(*dir_a < *dir_b)return (int)-1;
	if(*dir_a == *dir_b)return (int)0;
	return (int)1;
}

/*Dado un arreglo de elementos y una función de comparación,
 *nos devuelve un nuevo arreglo con los k elementos más chicos, 
 *en orden de menor a mayor.
 *El arreglo devuelto tendrá exactamente tamaño k.
 *Si k > n, las últimas k - n posiciones son NULL.
 *La complejidad de la función debe ser O(nlogk).*/
 
void** top_k(size_t k, void** datos, size_t tam_datos, cmp_func_t cmp){
	heap_t* heap = heap_crear(cmp);
	if(!heap)return NULL;
	for(size_t i=0;i<k && i<tam_datos;i++)heap_encolar(heap,datos[i]);
	if(tam_datos<k){
		vector_t* vector = vector_crear(0,NULL);
		if(!vector)return NULL;
		while(!heap_esta_vacio(heap))vector_insertar_al_final(vector,heap_desencolar(heap));
		heap_sort(vector->datos,tam_datos,comparar);	
		for(size_t i=tam_datos;i<k;i++)vector_insertar_al_final(vector,NULL);
		void** ordenado = malloc(k*sizeof(void*));
		if(!ordenado)return NULL;
		for(size_t i=0;i<vector->tam;i++)ordenado[i]=vector->datos[i];
		vector_destruir(vector);
		heap_destruir(heap,NULL);
		return ordenado;	
	} else { 
		for(size_t i=k;i<tam_datos;i++){
			if(comparar(heap_ver_max(heap),datos[i])>0){
				heap_desencolar(heap);
				heap_encolar(heap,datos[i]);
			}
		}
	}
	void** ordenado = malloc(k*sizeof(void*));
	if(!ordenado)return NULL;
	for(size_t i=0;i<k;i++)ordenado[i]=heap_desencolar(heap);
	heap_sort(ordenado,k,comparar);
	heap_destruir(heap,NULL);
	return ordenado;
}
