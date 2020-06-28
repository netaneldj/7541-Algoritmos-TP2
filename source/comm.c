#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash.h"
#include "lista.h"
#include "strutil.h"

/* *****************************************************************
 *                      FUNCIONES AUXILIARES
 * *****************************************************************/
 
void guardar_lineas(FILE* file, hash_t* hash){
	char* linea = NULL;
	size_t tam = 0;
	ssize_t len = 0;
	len = getline(&linea, &tam, file);
	while(len!=-1){
		hash_guardar(hash,linea,&linea);
		len = getline(&linea, &tam, file);
	}
	free(linea);
}

void imprimir_palabras(hash_iter_t* iter,hash_t* hash){		
	while(!hash_iter_al_final(iter)){
			const char* palabra = hash_iter_ver_actual(iter);
			if(!hash_pertenece(hash,palabra)){
				size_t i = 0;
				while(palabra[i]!='\n' && palabra[i]!='\0'){ 
					putchar(palabra[i]);
					i++;
				}
				putchar('\n');
				hash_iter_avanzar(iter);
				continue;
			}
			hash_iter_avanzar(iter);
	}
	return;
}

/* *****************************************************************
 *                      FUNCION PRICIPAL
 * *****************************************************************/

int main(int argc, char* argv[]){
	if (argc != 4 && argc != 3){
		fprintf(stderr, "Error, cantidad de parametros incorrecta\n");
		return -1;
	}
	if (argc == 4){
		if(strcmp(argv[3],"-1") && strcmp(argv[3],"-2")){
		fprintf(stderr, "Error, tercer parametro incorrecto\n");
		return -1;
		}
	}
	FILE* file1 = fopen(argv[1],"rt");
	if(!file1){
		fprintf(stderr, "Error, no se puede abrir el primer archivo\n");
		return -1;
	}
	FILE* file2 = fopen(argv[2],"rt");
	if(!file2){
		fclose(file1);
		fprintf(stderr, "Error, no se puede abrir el segundo archivo\n");
		return -1;
	} 
	hash_t* pal_file1 = hash_crear(NULL);
	hash_t* pal_file2 = hash_crear(NULL);
	guardar_lineas(file1,pal_file1);
	guardar_lineas(file2,pal_file2);
	hash_iter_t * iter1 = hash_iter_crear(pal_file1);
	hash_iter_t * iter2 = hash_iter_crear(pal_file2);
	if (argc == 3){
		while(!hash_iter_al_final(iter1)){
			const char* palabra = hash_iter_ver_actual(iter1);
			if(hash_pertenece(pal_file2,palabra)){
				size_t i = 0;
				while(palabra[i]!='\n' && palabra[i]!='\0'){ 
					putchar(palabra[i]);
					i++;
				}
				putchar('\n');
				hash_iter_avanzar(iter1);
				continue;
			}
			hash_iter_avanzar(iter1);
		}
	}
	else if(!strcmp(argv[3],"-1")){
		imprimir_palabras(iter1,pal_file2);
	}
	else {
		imprimir_palabras(iter2,pal_file1);
	}
	hash_iter_destruir(iter1);
	hash_iter_destruir(iter2);
	hash_destruir(pal_file1);
	hash_destruir(pal_file2);
	fclose(file1);
	fclose(file2);
	return 0;
}

