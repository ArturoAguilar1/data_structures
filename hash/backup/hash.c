#define  _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "hash.h"

#define _PADr_KAZE(x, n) ( ((x) << (n))>>(n) )

//Tiene que ser si o si numero primo el inicial
#define TAM_HASH_INICIAL 13
#define FACTOR_REDIMENSION 3
#define FACTOR_DE_CARGA 0.7
#define TABLA_INICIO 0

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
    hash_campo_t *tabla;
    hash_destruir_dato_t destruir_hash_dato;
};
struct hash_iter{
	//Const porque la funcion por la catedra recibe const entonces el compilador jode con eso
	const hash_t *hash;
	hash_campo_t actual;
	size_t posicion;
};

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
    hash->destruir_hash_dato = destruir_dato;

    for(size_t i=0;i<hash->tam;i++)
    	hash->tabla[i].estado = LIBRE;

    return hash;
}
bool guardar_elementos_redimension(hash_campo_t *tabla,char *clave, void *dato, size_t tam_tabla){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % tam_tabla;
	while(tabla[indice].estado == OCUPADO || tabla[indice].estado == BORRADO){
		indice++;
		if(indice == tam_tabla) //Esto lo saqué del hash cerrado
		indice = 0;
	}
	//Al pasar los eleemntos de una tabla a otra, la clave ya tiene memoria.
	tabla[indice].clave = clave; 
	tabla[indice].dato = dato;
	tabla[indice].estado = OCUPADO;
	
	return true;
}

bool hash_redimensionar(hash_t *hash,size_t nuevo_tam){
	hash_campo_t *nueva_tabla = malloc(sizeof(hash_campo_t)*nuevo_tam);
	if(nuevo_tam > 0 && !nueva_tabla)	return false;

	for(size_t i=0;i <nuevo_tam;i++)
		nueva_tabla[i].estado = LIBRE;

	for(size_t i=0;i<hash->tam;i++){
		if(hash->tabla[i].estado == OCUPADO){
			if(!guardar_elementos_redimension(nueva_tabla,hash->tabla[i].clave,hash->tabla[i].dato,nuevo_tam)){
				//fallo el pasaje de datos de la tabla vieja a la nueva
				return false;
			//guardar elementos de la vieja en la nueva tabla
			}
		}
	}
	hash->tam = nuevo_tam;
	//free(hash->tabla)?? Liberar la memoria de la tabla vieja
	hash->tabla = nueva_tabla;

	return true;
}

bool hash_guardar(hash_t *hash, const char *clave, void *dato){
	if(clave == NULL)	return false;
	//Redimension
	if((double)(hash->cant / hash->tam) >= FACTOR_DE_CARGA){
		if(!hash_redimensionar(hash,hash->tam * FACTOR_REDIMENSION)){
			//Falla la redimension
			return false;
		}
	}
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash -> tam;
	printf("Entré\n");
	if(!strcmp(hash->tabla[indice].clave,clave)){ 
		//Si la funcion de destuccion no es null, destruyo el anterior dato y guardo el nuevo
		if(hash->destruir_hash_dato != NULL){
			hash->destruir_hash_dato(hash->tabla[indice].dato); 
		}
		hash->tabla[indice].dato = dato;
		return true;
	}
	/*//Si esta libre el balde del indice, lo meto ahi
	else if(hash->tabla[indice].estado == LIBRE){
		hash->tabla[indice].clave = strdup(clave);
		hash->tabla[indice].dato = dato;
		hash->tabla[indice].estado = OCUPADO;
		hash->cant++;
	}*/
	//Si no esta libre, y tampoco es la comparacion primera, entocnes busco disponibilidad para meter
	else{
		while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
		indice++;
		if(indice == hash->tam) //Esto lo saqué del hash cerrado
			indice = 0;
		}
		hash->tabla[indice].clave = strdup(clave); 
		hash->tabla[indice].dato = dato;
		hash->tabla[indice].estado = OCUPADO;
		hash->cant++;
	}
	
	return true;

}

size_t hash_cantidad(const hash_t *hash){
	return hash->cant;
}

//Creo que al borrar no se deberia actualizar la cantidad, porque cuando redimensionamos contamos el borrado como si esruviera ocupado
// ya que al borrado no se le pueden guardar claves
void *hash_borrar(hash_t *hash, const char *clave){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash->tam;
	void *dato;
	while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
		if(hash->tabla[indice].estado == BORRADO){
			indice++;
			if(indice == hash->tam)
				indice = 0;	
			continue;
		}
		if(!strcmp(hash->tabla[indice].clave,clave)){
			dato = hash->tabla[indice].dato;
			//Una vez encontrado el dato, hay que liberar la memoria asociada a la clave, ya que la pedimos en strdup
			free(hash->tabla[indice].clave);
			hash->tabla[indice].estado = BORRADO;
			return dato;
		}
		indice++;
		if(indice == hash->tam)
			indice = 0;	
	}

	return NULL;
}

void *hash_obtener(const hash_t *hash, const char *clave){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash -> tam;
	void *dato;
		
	// if(hash->tabla[indice].estado == LIBRE)
	// 	return NULL;
	while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
		if(hash->tabla[indice].estado == BORRADO){
			indice++;
			if(indice == hash->tam)
				indice = 0;	
			continue;
		}
		if(!strcmp(hash->tabla[indice].clave,clave)){
			dato = hash->tabla[indice].dato;
			return dato;
		}
		indice++;
	
		if(indice == hash->tam)
			indice = 0;
			
	}

	return NULL;
}


//Si te parecen los cambios que hice a obtener, tambien los implementamos aca en pertence
//Tenemos que despues hacerlo en una funcion "buscar"
bool hash_pertenece(const hash_t *hash, const char *clave){
	size_t indice = murmurhash(clave,(uint32_t)strlen(clave),seed_parametro) % hash -> tam;
	// if(hash->tabla[indice].estado == LIBRE)
	// 	return false;
	while(hash->tabla[indice].estado == OCUPADO || hash->tabla[indice].estado == BORRADO){
		if(hash->tabla[indice].estado == BORRADO){
			indice++;
			if(indice == hash->tam)
				indice = 0;	
			continue;
		}
		if(!strcmp(hash->tabla[indice].clave,clave)){
			return true;
		}
		indice++;
	
		if(indice == hash->tam)
			indice = 0;
			
	}	

	return false;
}

void hash_destruir(hash_t *hash){
	if(hash->destruir_hash_dato){
		for(size_t i=0 ; i<hash->tam; i++){
			if(hash->tabla[i].estado == OCUPADO){ //el .h dice que debemos eliminar cada par, el tema es que no se si la funcion destruir hash dato recibe 2 parametros o 1, por eso lo puse dos veces (19/06)
				hash->destruir_hash_dato(hash->tabla[i].dato);
				hash->destruir_hash_dato(hash->tabla[i].clave);
			}
		}
	}
	free(hash->tabla);
	free(hash);
}

hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t *iter = malloc(sizeof(hash_iter_t));
	
	if(!iter) 
		return NULL;
	iter->hash = hash;
	iter->posicion = 0;

	while(iter->hash->tabla[iter->posicion].estado != OCUPADO){
		if(iter->posicion == hash->tam){
			break;
		}
		iter->posicion++;
	}

	iter->actual = iter->hash->tabla[iter->posicion];
	return iter;
}

bool hash_iter_avanzar(hash_iter_t *iter){
	// if(hash_iter_al_final(iter))
	// 		return false;
	//Hay que buscar la proxima posicion donde realmente haya un par de clave y dato
	while(iter->hash->tabla[iter->posicion].estado != OCUPADO){
		if(hash_iter_al_final(iter))
			return false;
		iter->posicion++;
	}
	iter->actual = iter->hash->tabla[iter->posicion];
	return true;
}

const char *hash_iter_ver_actual(const hash_iter_t* iter){
	return !hash_iter_al_final(iter) ? iter->hash->tabla[iter->posicion].clave : NULL;
}

bool hash_iter_al_final(const hash_iter_t *iter){
	//Si justo en el ultimo balde hay algo, con esto no entraria
	//return iter->posicion < iter->hash->tam;
	return iter->posicion == iter->hash->tam;
}

void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
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
// uint32_t FNV1A_Pippip(const char *str, size_t wrdlen) {
// 	const uint32_t PRIME = 591798841; 
//   uint32_t hash32; 
//   uint64_t hash64 = 14695981039346656037U;
// 	size_t Cycles, NDhead;
//   if (wrdlen > 8) {
// 	Cycles = ((wrdlen - 1)>>4) + 1; NDhead = wrdlen - (Cycles<<3);
//   #pragma nounroll
//         for(; Cycles--; str += 8) {
// 		hash64 = ( hash64 ^ (*(uint64_t *)(str)) ) * PRIME;        
// 		hash64 = ( hash64 ^ (*(uint64_t *)(str+NDhead)) ) * PRIME;        
// 	}
// } else
// 	hash64 = ( hash64 ^ _PADr_KAZE(*(uint64_t *)(str+0), (8-wrdlen)<<3) ) * PRIME;        
//   hash32 = (uint32_t)(hash64 ^ (hash64>>32)); 

// return hash32 ^ (hash32 >> 16);
// } 

