#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "heap.h"
#include "vector_dinamico.h"
#define VACIO 0

struct heap{
	vector_t* vd;
	size_t tam;
	cmp_func_t func_cmp;
};

heap_t* heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap)return NULL;
	heap->vd = vector_crear(VACIO,NULL);
	heap->func_cmp = cmp;
	heap->tam = VACIO;
	return heap;
}

size_t heap_cantidad(const heap_t* heap){
	return heap->tam;
}

bool heap_esta_vacio(const heap_t* heap){
	if(heap->tam==VACIO)return true;
	return false;
}

void *heap_ver_max(const heap_t *heap){
	if(heap->tam==VACIO)return NULL;
	return vector_obtener(heap->vd,0);
}

void upheap(heap_t* heap,size_t pos_hijo){
	if(pos_hijo<1 || pos_hijo>=heap->tam)return;
	size_t pos_padre = (pos_hijo-1)/2;
	void *val_hijo,*val_padre;
	
	val_hijo = vector_obtener(heap->vd,pos_hijo);
	val_padre = vector_obtener(heap->vd,pos_padre);
	
	if(!val_hijo || !val_padre)return;
	
	if(heap->func_cmp (val_hijo,val_padre)>0){
		vector_guardar(heap->vd,pos_padre,val_hijo);
		vector_guardar(heap->vd,pos_hijo,val_padre);
		upheap(heap,pos_padre);		
	}
}

bool heap_encolar(heap_t *heap, void *elem){
	if(!vector_insertar_al_final(heap->vd,elem))return false;
	heap->tam = heap->vd->tam;
	upheap(heap,heap->tam-1);
	return true;
}

void downheap(heap_t* heap,size_t pos_act){
	
	if(pos_act>=heap->tam)return;
	
	size_t pos_h_izq = 2*pos_act + 1;
	size_t pos_h_der = 2*pos_act + 2;
	size_t pos_mayor = pos_act;
	
	void *val_act,*val_izq,* val_der;
	
	val_act = vector_obtener(heap->vd,pos_act);
	val_izq = vector_obtener(heap->vd,pos_h_izq);
	val_der = vector_obtener(heap->vd,pos_h_der);
	
	if(pos_h_izq<heap->tam && heap->func_cmp(val_izq,val_act)>0)pos_mayor = pos_h_izq;
	if(pos_h_der<heap->tam && heap->func_cmp(val_der,vector_obtener(heap->vd,pos_mayor))>0)pos_mayor = pos_h_der;
	
	if(pos_mayor!=pos_act){
		vector_guardar(heap->vd,pos_act,vector_obtener(heap->vd,pos_mayor));
		vector_guardar(heap->vd,pos_mayor,val_act);
		downheap(heap,pos_mayor);		
	}	
}

void* heap_desencolar(heap_t *heap){
	if(heap_esta_vacio(heap))return NULL;
	void* val_borrar = vector_obtener(heap->vd,0);
	vector_guardar(heap->vd,0,vector_obtener(heap->vd,heap->tam-1));
	vector_guardar(heap->vd,heap->tam-1,val_borrar);
	vector_borrar_ultimo(heap->vd);
	heap->tam = heap->vd->tam;
	downheap(heap,0);
	return val_borrar;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	while(!heap_esta_vacio(heap)){
		if(destruir_elemento!=NULL)destruir_elemento(heap_desencolar(heap));
		else heap_desencolar(heap);
	}
	vector_destruir(heap->vd);
	free(heap);
}

heap_t* heap_crear_arr(void* arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap)return NULL;
	void** copia_arreglo = malloc(n*sizeof(void*));
	for(int i=0;i<n;i++)copia_arreglo[i]=arreglo[i];
	heap->vd = vector_crear(n,copia_arreglo);
	heap->func_cmp = cmp;
	heap->tam = n;
	for(size_t i=(n-1)/2;i>0;i--){
		downheap(heap,i);
	}
	downheap(heap,0);
	return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
	heap_t* heap = heap_crear_arr(elementos,cant,cmp);
	for(size_t i=heap->tam-1;i>0;i--){
		void* val_0 = vector_obtener(heap->vd,0);
		void* val_i = vector_obtener(heap->vd,i);
		vector_guardar(heap->vd,0,val_i);
		vector_guardar(heap->vd,i,val_0);
		heap->tam--;
		downheap(heap,0);
	}
	for(int i=0;i<cant;i++){
		elementos[i] = vector_obtener(heap->vd,i);
	}
	heap_destruir(heap,NULL);
}

void heap_actualizar_prioridad(heap_t* heap, void* dato){
	if(!dato)return;
	size_t pos=-1;
	void** arreglo = heap->vd->datos;
	for(size_t i=0;i<heap->tam;i++){
		if(arreglo[i]==dato){
			pos=i;
			break;
		}
	}
	if(pos==-1)return;
	upheap(heap,pos);
	downheap(heap,pos);
}
