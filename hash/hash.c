#define  _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"

#define _PADr_KAZE(x, n) ( ((x) << (n))>>(n) )


#define TAM_HASH_INICIAL 37
#define FACTOR_REDIMENSION_UP 3
#define FACTOR_REDIMENSION_DOWN 2
#define FACTOR_DE_CARGA_MAX 0.7
#define FACTOR_DE_CARGA_MIN 0.25

uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed);
//uint32_t FNV1A_Pippip(const char *str, size_t wrdlen);

static uint32_t seed_parametro = 0;

typedef enum{
    LIBRE = 0,
    OCUPADO = 1,
    BORRADO = 2,
}estado_t;

typedef struct{
    char *clave;
    void *dato;
    estado_t estado;
}hash_campo_t;

struct hash{
    size_t cant;
    size_t tam;
	size_t borrados;
    hash_campo_t *tabla;
    hash_destruir_dato_t destruir_hash_dato;
};
struct hash_iter{
	const hash_t *hash;
	hash_campo_t actual;
	size_t posicion;
};

void inicializar_tabla(hash_campo_t *ptr,size_t tam){
	for(size_t i=0 ; i<tam ; i++){
    	ptr[i].estado = LIBRE;
		ptr[i].clave = "";
		ptr[i].dato = NULL;
	}
}


hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    hash_t *hash = malloc(sizeof(hash_t));
    if(!hash) {
       	return NULL;
    }

	hash->tabla = malloc(sizeof(hash_campo_t)*TAM_HASH_INICIAL);
    if(!hash->tabla){
    	free(hash);
    	return NULL;
    }

    hash->tam = TAM_HASH_INICIAL;
    hash->cant = 0;
	hash->borrados = 0;
    hash->destruir_hash_dato = destruir_dato;

	inicializar_tabla(hash->tabla,hash->tam);

    return hash;
}

bool guardar_elementos_redimension(hash_campo_t *tabla,char *clave, void *dato, size_t nuevo_tam){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % nuevo_tam;
	while(tabla[indice].estado == OCUPADO){
		indice++;
		if(indice == nuevo_tam)
			indice = 0;
	}
	tabla[indice].clave = clave; 
	tabla[indice].dato = dato;
	tabla[indice].estado = OCUPADO;
	
	return true;
}

bool hash_redimensionar(hash_t *hash,size_t nuevo_tam){
	hash_campo_t *nueva_tabla = malloc(sizeof(hash_campo_t)*nuevo_tam);
	if(nuevo_tam > 0 && !nueva_tabla)	return false;

	inicializar_tabla(nueva_tabla,nuevo_tam);

	for(size_t i=0;i<hash->tam;i++){
		if(hash->tabla[i].estado == OCUPADO){
			if(!guardar_elementos_redimension(nueva_tabla,hash->tabla[i].clave,hash->tabla[i].dato,nuevo_tam)){
				return false;
			}
		}
	}

	hash->tam = nuevo_tam;
	free(hash->tabla);
	hash->tabla = nueva_tabla;
	hash->borrados = 0;

	return true;
}

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if(clave == NULL)	return false;
	
	if((float)(hash->cant + hash->borrados)/ (float)hash->tam >= FACTOR_DE_CARGA_MAX){
		if(!hash_redimensionar(hash,hash->tam * FACTOR_REDIMENSION_UP)){
			return false;
		}
	}

	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash->tam;

	if(hash->cant > 0 && !strcmp(hash->tabla[indice].clave,clave)){ 
		if(hash->destruir_hash_dato != NULL){
			hash->destruir_hash_dato(hash->tabla[indice].dato); 
		}
		hash->tabla[indice].dato = dato;
		return true;
	}
	else{
		while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
			indice++;
			if(indice == hash->tam) 
				indice = 0;
		}
		hash->tabla[indice].clave = strdup(clave); 
		hash->tabla[indice].dato = dato;
		hash->tabla[indice].estado = OCUPADO;
		hash->cant++;
	}

	return true;
}

bool buscar_posicion(hash_campo_t *tabla,size_t *indice, size_t tam, const char *clave){
	while(tabla[*indice].estado != LIBRE){
		if(tabla[*indice].estado == BORRADO){
			(*indice)++;
			if(*indice == tam)
				*indice = 0;	
			continue;
		}

		if(!strcmp(tabla[*indice].clave,clave))
			return true;

		(*indice)++;
		if(*indice == tam)
			*indice = 0;
	}
	return false;
}


void *hash_borrar(hash_t *hash, const char *clave){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash->tam;
	void *dato;
	if(buscar_posicion(hash->tabla,&indice,hash->tam,clave)){
		dato = hash->tabla[indice].dato;
		free(hash->tabla[indice].clave);
		hash->tabla[indice].estado = BORRADO;
		hash->cant--;
		hash->borrados++;
	}
	else
		return NULL;
		
	if((float)hash->cant / (float)hash->tam <= FACTOR_DE_CARGA_MIN){
		if(!hash_redimensionar(hash,hash->tam / FACTOR_REDIMENSION_DOWN))
			return NULL;
	}

	return dato;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash -> tam;
	void *dato;
	if(buscar_posicion(hash->tabla,&indice,hash->tam,clave)){
		dato = hash->tabla[indice].dato;
		return dato;
	}else
		return NULL;
}

bool hash_pertenece(const hash_t *hash, const char *clave){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash -> tam;
	return buscar_posicion(hash->tabla,&indice,hash->tam,clave);
}

void hash_destruir(hash_t *hash){
	for(size_t i = 0; i < hash->tam; i++){
		if(hash->tabla[i].estado == OCUPADO){
			if(hash->destruir_hash_dato != NULL){
				hash->destruir_hash_dato(hash->tabla[i].dato);
			}
			free(hash->tabla[i].clave);
		}
	}
	free(hash->tabla);
	free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t *iter = malloc(sizeof(hash_iter_t));
	if(!iter)	return NULL;

	iter->hash = hash;
	iter->posicion = 0;
	if(iter->hash->cant > 0){
		while(iter->hash->tabla[iter->posicion].estado != OCUPADO){
			if(iter->posicion == iter->hash->tam){
				break;
			}
		iter->posicion++;
		}
	}

	iter->actual = iter->hash->tabla[iter->posicion];
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
 
    if(hash_iter_al_final(iter))
        return false;
   
    while(iter->posicion < iter->hash->tam){
        iter->posicion++;
        if(hash_iter_al_final(iter))
            return false;
 
        if(iter->hash->tabla[iter->posicion].estado == OCUPADO)
            break;
    }
 
    iter->actual = iter->hash->tabla[iter->posicion];
    return true;
}

const char *hash_iter_ver_actual(const hash_iter_t* iter){
	return !hash_iter_al_final(iter) ? iter->hash->tabla[iter->posicion].clave : NULL;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	if(iter->hash->cant == 0)	
		return true;
	return iter->posicion == iter->hash->tam;
}

void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}


void hash_imprimir(hash_t *hash){
	printf("HASH:\n");
	for(size_t i = 0; i < hash->tam; i++){
		if(hash->tabla[i].estado == OCUPADO){
			printf("[Indice: %zu] Clave: \x1b[1m\x1b[32m %s \x1b[0m Estado: %s \n",i,hash->tabla[i].clave,"Ocupado");	
		}else if(hash->tabla[i].estado == LIBRE){
			printf("[Indice: %zu] Clave: %s Estado: %s \n",i,"Vacio","Libre");
		}else{
			printf("[Indice: %zu] Clave: %s Estado: %s \n",i,"Clave Borrada","Borrado");
		}		
	}
}


//Funcion de hash: Murmurhash3 de:
// https://github.com/jwerle/murmurhash.c/blob/master/murmurhash.c
uint32_t murmurhash(const char *key, uint32_t len, uint32_t seed) {
  uint32_t c1 = 0xcc9e2d51;
  uint32_t c2 = 0x1b873593;
  uint32_t r1 = 15;
  uint32_t r2 = 13;
  uint32_t m = 5;
  uint32_t n = 0xe6546b64;
  uint32_t h = 0;
  uint32_t k = 0;
  uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
  const uint32_t *chunks = NULL;
  const uint8_t *tail = NULL; // tail - last 8 bytes
  int i = 0;
  int l = len / 4; // chunk length

  h = seed;

  chunks = (const uint32_t *) (d + l * 4); // body
  tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

  // for each 4 byte chunk of `key'
  for (i = -l; i != 0; ++i) {
    // next 4 byte chunk of `key'
    k = chunks[i];

    // encode next 4 byte chunk of `key'
    k *= c1;
    k = (k << r1) | (k >> (32 - r1));
    k *= c2;

    // append to hash
    h ^= k;
    h = (h << r2) | (h >> (32 - r2));
    h = h * m + n;
  }

  k = 0;

  // remainder
  switch (len & 3) { // `len % 4'
    case 3: k ^= (tail[2] << 16);
    case 2: k ^= (tail[1] << 8);

    case 1:
      k ^= tail[0];
      k *= c1;
      k = (k << r1) | (k >> (32 - r1));
      k *= c2;
      h ^= k;
  }

  h ^= len;

  h ^= (h >> 16);
  h *= 0x85ebca6b;
  h ^= (h >> 13);
  h *= 0xc2b2ae35;
  h ^= (h >> 16);

  return h;
}

/*La encontre en: https://www.codeproject.com/Articles/716530/Fastest-Hash-Function-for-Table-Lookups-in-C
Ahi explica que tiene muy buen rendimiento comparado a otras.
Necesita la macro de funcion _PaDr_KAZE
*/
/*uint32_t FNV1A_Pippip(const char *str, size_t wrdlen) {
	const uint32_t PRIME = 591798841; 
  uint32_t hash32; 
  uint64_t hash64 = 14695981039346656037U;
	size_t Cycles, NDhead;
  if (wrdlen > 8) {
	Cycles = ((wrdlen - 1)>>4) + 1; NDhead = wrdlen - (Cycles<<3);
  #pragma nounroll
        for(; Cycles--; str += 8) {
		hash64 = ( hash64 ^ (*(uint64_t *)(str)) ) * PRIME;        
		hash64 = ( hash64 ^ (*(uint64_t *)(str+NDhead)) ) * PRIME;        
	}
} else
	hash64 = ( hash64 ^ _PADr_KAZE(*(uint64_t *)(str+0), (8-wrdlen)<<3) ) * PRIME;        
  hash32 = (uint32_t)(hash64 ^ (hash64>>32)); 
return hash32 ^ (hash32 >> 16);
} */

