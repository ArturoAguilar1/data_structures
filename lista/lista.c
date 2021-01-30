#include "lista.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct nodo{
    struct nodo *sig;
    void *dato;
};
typedef struct nodo nodo_t;

struct lista{
    nodo_t *prim;
    nodo_t *ult;
    size_t largo;
};

struct lista_iter{
    nodo_t *anterior;
    nodo_t *actual;
    lista_t *l_iter;
};


lista_t *lista_crear(){
    lista_t *l = malloc(sizeof(lista_t));
    if(!l)
        return NULL;

    l->prim = NULL;
    l->ult = NULL;
    l->largo = 0;

    return l;
}

nodo_t *nodo_crear(void *dato){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if(!nodo)
        return NULL;

    nodo->dato = dato;
    nodo->sig = NULL;

    return nodo;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->prim == NULL && lista->ult == NULL;
}

bool lista_insertar_primero(lista_t *lista,void *dato){
	nodo_t *nodo = nodo_crear(dato);
	if(!nodo) return false;

    if(lista_esta_vacia(lista))
        lista->ult = nodo;
    
	nodo->sig = lista->prim;
	lista->prim = nodo;

    lista->largo++;
    
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t *nodo = nodo_crear(dato);
    if(!nodo)  return false;

    if(lista_esta_vacia(lista))
        lista->prim = nodo;
    else
        lista->ult->sig = nodo;
    
    lista->ult = nodo;

    lista->largo++;

    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista)) return NULL;

	nodo_t *nodo_aux = lista->prim;
	void *d = nodo_aux->dato;

	lista->prim = nodo_aux->sig;
	free(nodo_aux);

    if(lista->prim == NULL){
        lista->ult = NULL;
    }

    lista->largo--;

	return d;
}

void *lista_ver_primero(const lista_t *lista){
    return lista_esta_vacia(lista) ? NULL : lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    return lista_esta_vacia(lista) ? NULL : lista->ult->dato;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
    while(!lista_esta_vacia(lista)){
        if(destruir_dato != NULL)
            destruir_dato(lista->prim->dato);

        lista_borrar_primero(lista);
    }

    free(lista);
}


//Iterador Interno
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t *nodo_aux = lista->prim;
    while(nodo_aux){
        if(!visitar(nodo_aux->dato,extra))
            return;
        
        nodo_aux = nodo_aux->sig;
    }
}


//Iterador Externo
lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if(!iter) return NULL;

    iter->l_iter = lista; 
    iter->actual = lista->prim;
    iter->anterior = NULL;

    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(lista_iter_al_final(iter))
        return false;

    iter->anterior = iter->actual;
    iter->actual = iter->actual->sig;

    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    return lista_iter_al_final(iter) ? NULL : iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}


// bool lista_iter_insertar(lista_iter_t *iter, void *dato){
//     if(lista_iter_al_final(iter)){
//         if(!lista_insertar_ultimo(iter->l_iter,dato))
//             return false;
//     }
//     if(!iter->anterior){
//         if(!lista_insertar_primero(iter->l_iter,dato))
//             return false;
//     } 
//     else{
//         nodo_t *nodo_insertar = nodo_crear(dato);
//         if(!nodo_insertar)   return false;
//         iter->anterior->sig = nodo_insertar;
//         nodo_insertar->sig = iter->actual;
//         iter->actual = nodo_insertar;
//     } 
//     iter->l_iter->largo++;

//     return true;
// }


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t *nodo_insertar = nodo_crear(dato);
    if(!nodo_insertar)   return false;
    
    if(!iter->anterior){
        nodo_insertar->sig = iter->actual;
        iter->l_iter->prim = nodo_insertar;  
        iter->actual = nodo_insertar;    
    } 
    else if(lista_iter_al_final(iter)){
        iter->actual = nodo_insertar;
        iter->l_iter->ult = nodo_insertar;
        iter->anterior->sig = nodo_insertar;
    }
    else{
        iter->anterior->sig = nodo_insertar;
        nodo_insertar->sig = iter->actual;
        iter->actual = nodo_insertar;
    }
    if(!iter->actual->sig)
        iter->l_iter->ult = nodo_insertar;
    

    iter->l_iter->largo++;

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
    if(lista_iter_al_final(iter))
        return NULL;
    
    nodo_t *aux_nodo = iter->actual;
    void *dato = lista_iter_ver_actual(iter);

    iter->actual = iter->actual->sig;

    if(!iter->anterior){
        iter->l_iter->prim = iter->actual; 
    } else{
        iter->anterior->sig = iter->actual;
    }
    if(lista_iter_al_final(iter))
        iter->l_iter->ult = iter->anterior;

    free(aux_nodo);    
    iter->l_iter->largo--;
    return dato;
 }
