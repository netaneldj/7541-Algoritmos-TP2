#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "hash.h"
#include "pila.h"
#include "lista.h"
#include "strutil.h"


/* *****************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/
 
 void imprimir_resultado(char* clave,int* apariciones){
	printf("%d ",*apariciones);
	size_t i = 0;
	while(clave[i]!='\n' && clave[i]!='\0'){ 
		putchar(clave[i]);
		i++;
	}
	putchar('\n');
}
 
/* *****************************************************************
 *                      FUNCION PRICIPAL
 * *****************************************************************/

int main(int argc, char* argv[]){
	if (argc != 2){
		fprintf(stderr, "Error, cantidad de parametros incorrecta\n");
		return -1;
	}
	FILE* file = fopen(argv[1],"r");
	if(!file){
		fprintf(stderr, "Error, no se puede abrir el archivo\n");
		return -1;
	}
	char* linea = NULL;
	char** arreglo_palabras = NULL;
	size_t capacidad = 0;
	size_t pos_pal = 0;
	ssize_t len = 0;
	hash_t* hash_palabras = hash_crear(free); 
	lista_t* lista_palabras = lista_crear(); 
	lista_t* lista_lineas = lista_crear(); 
	len = getline(&linea, &capacidad, file);
	while(len != -1){
		arreglo_palabras = split(linea,' '); 
		while(arreglo_palabras[pos_pal]!=NULL){
			int* cant = malloc(sizeof(int));
			*cant = 1;
			if(!hash_pertenece(hash_palabras,arreglo_palabras[pos_pal])){
				hash_guardar(hash_palabras,arreglo_palabras[pos_pal],(void*)cant);
				lista_insertar_ultimo(lista_palabras,arreglo_palabras[pos_pal]);
				pos_pal++;
				continue;
			}
			int* cant_ant = (int*) hash_obtener(hash_palabras,arreglo_palabras[pos_pal]);
			*cant+=*cant_ant;
			hash_guardar(hash_palabras,arreglo_palabras[pos_pal],(void*)cant);
			pos_pal++;
		}
		pos_pal = 0;
		lista_insertar_ultimo(lista_lineas,(void*)arreglo_palabras);
		len = getline(&linea, &capacidad, file);
	}
	lista_iter_t * iter_palabras = lista_iter_crear(lista_palabras);
	int* apariciones = NULL;
	while(!lista_iter_al_final(iter_palabras)){
		char* clave = lista_iter_borrar(iter_palabras);
		apariciones = (int*)hash_obtener(hash_palabras,clave);
		imprimir_resultado(clave,apariciones);
	}
	lista_iter_t * iter_lineas = lista_iter_crear(lista_lineas);
	while(!lista_iter_al_final(iter_lineas)){
		char** aux = lista_iter_borrar(iter_lineas);
		free_strv(aux);
	}
	lista_destruir(lista_lineas,NULL);
	lista_destruir(lista_palabras,NULL);
	lista_iter_destruir(iter_lineas);
	lista_iter_destruir(iter_palabras); 
	hash_destruir(hash_palabras); 
	free(linea); 
	fclose(file);
	return 0;
}
			
			
			
				
		
	
