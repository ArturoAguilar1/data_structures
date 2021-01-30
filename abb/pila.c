#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

#define PILA_CAPACIDAD_INICIAL 1


struct pila {
    void **datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));
    if(!pila)
        return NULL;

    pila->datos = malloc(sizeof(void *));
    if(!pila->datos){
        free(pila);
        return NULL;
    }

    pila->capacidad = PILA_CAPACIDAD_INICIAL;
    pila->cantidad = 0;

    return pila;
}

bool pila_redimensionar(pila_t *pila, size_t tam){
    void *aux_datos = realloc(pila->datos,sizeof(void *) * tam);
    if(tam > 0 && aux_datos == NULL)
        return false;
    
    pila->capacidad = tam;
    pila->datos = aux_datos;
    return true;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == 0;
}

bool pila_apilar(pila_t *pila, void *valor){
    if(pila == NULL)
        return false;
        
    if(pila->cantidad == pila->capacidad){
        if(pila_redimensionar(pila,pila->capacidad*2) != true)
            return false;
    }

    pila->datos[pila->cantidad++] = valor;

    return true;
}

void *pila_ver_tope(const pila_t *pila){
    return (pila_esta_vacia(pila)) == true ? NULL : pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila){
    if(pila_esta_vacia(pila))
        return NULL;

    void *aux = pila_ver_tope(pila);

    pila->cantidad--;

    if(pila->cantidad*4 == pila->capacidad){
        if(!pila_redimensionar(pila,pila->capacidad / 2)){
            return aux;
        }
    }

    return aux;
}


void pila_imprimir(pila_t *p){
    printf("  _______\n");
    for(size_t i = 0; i< p->cantidad ; i++){
        printf("  |  %d  |\n  -------\n",*(int *)p->datos[i]);
    }
    printf("\n \n");
}
