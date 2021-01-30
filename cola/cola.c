#include "cola.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct nodo{
    void* dato;
    struct nodo* sig;
};

typedef struct nodo nodo_t;

struct cola{
    nodo_t* prim;
    nodo_t* ult;
};

static nodo_t *nodo_crear(void *d){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if(!nodo)
        return NULL;

    nodo->sig = NULL;
    nodo->dato = d;

    return nodo;
}

cola_t* cola_crear(void){
    cola_t *cola = malloc(sizeof(cola_t));
    if(!cola) 
        return NULL;

    cola->prim = NULL;
    cola->ult = NULL;

    return cola;
}

bool cola_encolar(cola_t *cola, void* valor){
    nodo_t *nodo = nodo_crear(valor);
    if(!nodo)
        return false;

    if(cola_esta_vacia(cola)){
        cola->prim = nodo;
        cola->ult = nodo;
        return true;
    }

    cola->ult->sig = nodo;
    cola->ult = nodo;

    return true;
}

void* cola_desencolar(cola_t *cola){
    void *dato = NULL;
    if(cola->prim){
        nodo_t *aux = cola->prim;
        cola->prim = cola->prim->sig;
        dato = aux->dato;
        free(aux);

        if(!cola->prim)
            cola->ult = NULL;
    }
    return dato;
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->prim == NULL && cola->ult == NULL;
}

void* cola_ver_primero(const cola_t *cola){
    return cola_esta_vacia(cola) ? NULL : cola->prim->dato;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void*)){
    while(!cola_esta_vacia(cola)){
        if(destruir_dato != NULL)
            destruir_dato(cola->prim->dato);
        
        cola_desencolar(cola);
    }
    free(cola);
}


void imprimir_cola(cola_t *cola){
    nodo_t *aux = cola->prim;
    while(aux){
        printf(" | %d | ->", *(int*)(aux->dato));
        aux = aux->sig;
    }
    printf("\n");
}


