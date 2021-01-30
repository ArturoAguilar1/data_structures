#include "testing.h"
#include <stdlib.h>
#include <stdio.h>

#include <stdint.h>
#include <string.h>

#define _PADr_KAZE(x, n) ( ((x) << (n))>>(n) )

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

void pruebas_hash_catedra(void);
void pruebas_volumen_catedra(size_t);


//uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed);
// uint32_t FNV1A_Pippip(const char *str, size_t wrdlen);

int main(int argc, char *argv[])
{
    if (argc > 1) {
        // Asumimos que nos están pidiendo pruebas de volumen.
        long largo = strtol(argv[1], NULL, 10);
        pruebas_volumen_catedra((size_t) largo);

        return failure_count() > 0;
    }

    printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
    pruebas_hash_catedra();

    return failure_count() > 0;
}
    // if (argc > 1) {
    //     // Asumimos que nos están pidiendo pruebas de volumen.
    //     long largo = strtol(argv[1], NULL, 10);
    //     pruebas_volumen_catedra((size_t) largo);

    //     return failure_count() > 0;
    // }

    // printf("\n~~~ PRUEBAS CÁTEDRA ~~~\n");
    // pruebas_hash_catedra();
    // printf("Prueba con funcion hash:\n");
    // const char *key = "hola";
    // printf("hola\n");
    // uint32_t seed = 0;
    // const char *key1 = "Salchichon Primavera";
    // const char *key2 = "Algoritmos 2";
    // const char *key3 = "Probando Diccionario"; 

    // uint32_t hash = murmurhash(key,(uint32_t)strlen(key),13);
    // printf("Hasheado1: %u  \n",hash);

    // uint32_t hash1 = murmurhash("Hola",(uint32_t)strlen(key),seed);
    // printf("Hasheado2: %u y aplicado el modulo es: %u \n",hash1, hash1 % 13);

    // uint32_t hash2 = murmurhash("Arturo Javier Aguilar Lopez",(uint32_t)strlen(key),seed);
    // printf("Hasheado2: %u y aplicado el modulo es: %u \n",hash2, hash2 % 13);

    // uint32_t hpip = FNV1A_Pippip("Arturo Javier Aguilar Lopez",strlen("Arturo Javier Aguilar Lopez"));
    // printf("Hasheado2: %u y aplicado el modulo es: %u \n",hpip, hpip % 13);

    // uint32_t hpip1 = FNV1A_Pippip(key1,strlen(key1));
    // printf("String: %s   Hasheado: %u    Con mod: %u   \n",key1,hpip1, hpip1 % 13);

    //   uint32_t hpip2 = FNV1A_Pippip(key2,strlen(key2));
    // printf("String: %s   Hasheado: %u    Con mod: %u   \n",key2,hpip2, hpip2 % 13);

    // uint32_t hpip3 = FNV1A_Pippip(key1,strlen(key3));
    // printf("String: %s   Hasheado: %u    Con mod: %u   \n",key3,hpip3, hpip3 % 13);


    //return failure_count() > 0;



// uint32_t murmurhash (const char *key, uint32_t len, uint32_t seed) {
//   uint32_t c1 = 0xcc9e2d51;
//   uint32_t c2 = 0x1b873593;
//   uint32_t r1 = 15;
//   uint32_t r2 = 13;
//   uint32_t m = 5;
//   uint32_t n = 0xe6546b64;
//   uint32_t h = 0;
//   uint32_t k = 0;
//   uint8_t *d = (uint8_t *) key; // 32 bit extract from `key'
//   const uint32_t *chunks = NULL;
//   const uint8_t *tail = NULL; // tail - last 8 bytes
//   int i = 0;
//   int l = len / 4; // chunk length

//   h = seed;

//   chunks = (const uint32_t *) (d + l * 4); // body
//   tail = (const uint8_t *) (d + l * 4); // last 8 byte chunk of `key'

//   // for each 4 byte chunk of `key'
//   for (i = -l; i != 0; ++i) {
//     // next 4 byte chunk of `key'
//     k = chunks[i];

//     // encode next 4 byte chunk of `key'
//     k *= c1;
//     k = (k << r1) | (k >> (32 - r1));
//     k *= c2;

//     // append to hash
//     h ^= k;
//     h = (h << r2) | (h >> (32 - r2));
//     h = h * m + n;
//   }

//   k = 0;

//   // remainder
//   switch (len & 3) { // `len % 4'
//     case 3: k ^= (tail[2] << 16);
//     case 2: k ^= (tail[1] << 8);

//     case 1:
//       k ^= tail[0];
//       k *= c1;
//       k = (k << r1) | (k >> (32 - r1));
//       k *= c2;
//       h ^= k;
//   }

//   h ^= len;

//   h ^= (h >> 16);
//   h *= 0x85ebca6b;
//   h ^= (h >> 13);
//   h *= 0xc2b2ae35;
//   h ^= (h >> 16);

//   return h;
// }


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

