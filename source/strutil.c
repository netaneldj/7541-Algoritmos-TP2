#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void free_strv(char* strv[]){
	int pos = 0;
	while(strv[pos]){
		free(strv[pos]);
		pos++;
	}
	free(strv);
}

char** split(const char* str, char sep){
	if(sep == '\0') return NULL;
	size_t len = strlen(str);
	int cant_cad = 0;
	for (int i=0 ; i<len ; i++){
		if(str[i] == sep){
			cant_cad++;
			continue;
		}
	}
	char** array_din = malloc( (cant_cad + 2)* sizeof(char*));
	if (!array_din) return NULL;
	char cad_aux[len];
	char* cad_din;
	size_t pos_aux = 0, pos_array_aux = 0;
	for (int j=0 ; j<len ; j++){
		if(str[j] == sep){
			cad_aux[pos_aux] = '\0';
			cad_din = strdup(cad_aux);
			if (!cad_din){
				free_strv(array_din);
				return NULL;
			}
			pos_aux = 0;
			array_din[pos_array_aux] = cad_din;
			pos_array_aux++;
			continue;
		}
		cad_aux[pos_aux] = str[j];
		pos_aux++;
		continue;
	}
	cad_aux[pos_aux] = '\0';
	cad_din = strdup(cad_aux);
	if (!cad_din){
		free_strv(array_din);
		return NULL;
	}
	array_din[pos_array_aux] = cad_din;
	array_din[pos_array_aux+1] = NULL;
	return array_din;
}					
	
char* join(char** strv, char sep){
	size_t cant_cad = 0, cant_char = 0 ,pos_cad = 0,len = 0;
	char* cadena;
	while(strv[cant_cad]){
		len = strlen(strv[cant_cad]);
		for(int j = 0 ; j < len ;j++){
			cant_char++;
		}
		cant_cad++;
	}
	cadena = malloc((cant_char+cant_cad+1) * sizeof(char));
	if(!cadena)return NULL;
	for (int i = 0 ; i <cant_cad ; i++){
		len = strlen(strv[i]); 
		for(int j = 0 ; j < len ;j++){
			cadena[pos_cad] = strv[i][j];
			pos_cad++;
		}
		if(i != cant_cad-1){
		cadena[pos_cad]=sep;
		pos_cad++;
		}
	}
	cadena[pos_cad] = '\0';
	return cadena;
}
	
		
	

		
		
		
		
		
			
		
		
	
