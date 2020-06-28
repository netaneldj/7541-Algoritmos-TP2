#include "vector_dinamico.h"
#include <stdlib.h>
#include <stddef.h>


// Funciones del alumno.

void vector_destruir(vector_t* vector){
	free(vector->datos);
	free(vector);
}

void* vector_obtener(vector_t* vector, size_t pos){
	if(pos<0 || pos>=vector->tam){
		return NULL;
	}
	return vector->datos[pos];
}

bool vector_guardar(vector_t* vector, size_t pos, void* valor){
	if(pos<0 || pos>=vector->tam){
		return false;
	}
	vector->datos[pos]=valor;
	return true;
}

size_t vector_obtener_tamanio(vector_t* vector){
	return vector->tam;
}


void* vector_borrar_ultimo(vector_t* vector){
	void* valor = vector->datos[vector->tam-1];
	if(!vector_redimensionar(vector,vector->tam-1))return NULL;
	return valor;	
}

bool vector_insertar_al_final(vector_t* vector,void* valor){
	if(!vector_redimensionar(vector,vector->tam+1))return false;
	vector->datos[vector->tam-1]=valor;
	return true;
}

// Funciones implementadas por la catedra.

vector_t* vector_crear(size_t tam,void** vd) {
    vector_t* vector = malloc(sizeof(vector_t));
    if (vector == NULL) {
        return NULL;
    }
	if(vd!=NULL){
		vector->datos = vd;
		vector->tam = tam;
		return vector;
	}    
    vector->datos = malloc(tam * sizeof(void*));
    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    void** datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(void*));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }
    
    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
