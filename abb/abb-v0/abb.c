#define  _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdio.h>
#include "abb.h"

#include "pila.h"


typedef struct nodo_abb{
    struct nodo_abb *izq;
    struct nodo_abb *der;
    char* clave;
    void* dato;
}nodo_abb_t;

struct abb{
    nodo_abb_t *raiz;
    size_t cantidad;
    abb_destruir_dato_t destruir;
    abb_comparar_clave_t comparar;
};

struct abb_iter{
    const abb_t *abb;
    pila_t *pila;
};

void inorder(nodo_abb_t *raiz,void print(void*)){
    if(raiz!=NULL) 
    {
        inorder(raiz->izq,print);
        print(raiz->clave); 
        inorder(raiz->der,print);
    }
}

void imprimir_arbol(abb_t *arbol,void print(void*)){
	inorder(arbol->raiz,print);
}


nodo_abb_t *abb_nodo_crear(const char *clave, void *dato){
	nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
	nodo->clave = strdup(clave);
	if(!nodo || !nodo->clave)	return false;
	
	nodo->dato = dato;
	nodo->der = NULL;
	nodo->izq = NULL;

	return nodo;
}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));
    if(!abb)    return NULL;

    abb->raiz = NULL;
    abb->cantidad = 0;
    abb->comparar = cmp;
    abb->destruir = destruir_dato;

    return abb;
}

nodo_abb_t** abb_nodo_buscar(nodo_abb_t **raiz,const char *clave,abb_comparar_clave_t cmp){
	if(!raiz)
		return NULL;

	if(!cmp((*raiz)->clave,clave))
		return raiz;	
	
	else if(cmp(clave,(*raiz)->clave) < 0){
		if(!(*raiz)->izq)
			return &(*raiz)->izq;
		return abb_nodo_buscar(&(*raiz)->izq,clave,cmp);
	}
	else{
		if(!(*raiz)->der)
			return &(*raiz)->der;
		return abb_nodo_buscar(&(*raiz)->der,clave,cmp);		
	}
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(!arbol->raiz){
		nodo_abb_t* nodo = abb_nodo_crear(clave,dato);
		if(!nodo)	return false;
		arbol->raiz = nodo;
		arbol->cantidad++;
		return true;
	}
	nodo_abb_t **nodo_buscado = abb_nodo_buscar(&arbol->raiz,clave,arbol->comparar);
	if(*nodo_buscado != NULL){
	 	if(arbol->destruir)
			arbol->destruir((*nodo_buscado)->dato); 	
	 	(*nodo_buscado)->dato = dato;
		return true;
	}
	nodo_abb_t *nodo_insertar = abb_nodo_crear(clave,dato);
	if(!nodo_insertar)	return false;
	*nodo_buscado = nodo_insertar;
	
	arbol->cantidad++;
    return true;
}

nodo_abb_t *buscar_reemplazante(nodo_abb_t *nodo){
	nodo_abb_t *aux_min = nodo;
	while(aux_min->izq != NULL){
		aux_min = aux_min->izq;
	}
	return aux_min;
}

void *borrar_nodo(abb_t *arbol,nodo_abb_t **nodo_borrar,const char *clave){
	void *aux_dato = NULL;
	nodo_abb_t *aux_borrar = *nodo_borrar;
	if(!aux_borrar->izq && !aux_borrar->der){
		aux_dato = aux_borrar->dato;
		free(aux_borrar->clave);
		free(aux_borrar);
		*nodo_borrar = NULL;
	}
	else if(!aux_borrar->izq){
		aux_dato = aux_borrar->dato;
		*nodo_borrar = aux_borrar->der;
		free(aux_borrar->clave);
		free(aux_borrar);
	}else if(!aux_borrar->der){
		aux_dato = aux_borrar->dato;
		*nodo_borrar = aux_borrar->izq;
		free(aux_borrar->clave);
		free(aux_borrar);
	}else{
		aux_dato = aux_borrar->dato;
		nodo_abb_t *reemplazo = buscar_reemplazante((*nodo_borrar)->der);
		char *clave_pisar = strdup(reemplazo->clave);
		void *dato_reemplazo = abb_borrar(arbol,reemplazo->clave);
		arbol->cantidad++;
		free((*nodo_borrar)->clave);
		(*nodo_borrar)->clave = clave_pisar;
		(*nodo_borrar)->dato = dato_reemplazo;
	}
	return aux_dato;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	if(arbol->cantidad == 0)	return NULL;
	nodo_abb_t **nodo_borrar = abb_nodo_buscar(&arbol->raiz,clave,arbol->comparar);
	if(!(*nodo_borrar))
	 	return NULL; //No encontré la clave
	void *dato = borrar_nodo(arbol,nodo_borrar,clave);
	arbol->cantidad--;
	return dato;
}

void *abb_obtener(const abb_t *arbol, const char *clave){
	if(arbol->cantidad == 0)	return NULL;
	nodo_abb_t *aux_raiz = arbol->raiz;
	nodo_abb_t **obtenido = abb_nodo_buscar(&aux_raiz,clave,arbol->comparar);
    return *obtenido ? (*obtenido)->dato : NULL;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	if(arbol->cantidad == 0)	return false;
	nodo_abb_t *aux_raiz = arbol->raiz;
	nodo_abb_t **obtenido = abb_nodo_buscar(&aux_raiz,clave,arbol->comparar);
	return *obtenido != NULL;
}

size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}

void abb_destruir_wrapper(abb_t *arbol, nodo_abb_t * raiz){
	if(raiz && raiz->izq)
		abb_destruir_wrapper(arbol,raiz->izq);
	
	if(raiz && raiz->der)
		abb_destruir_wrapper(arbol,raiz->der);
	
	if(raiz){ 
		if(arbol->destruir != NULL){
			arbol->destruir(raiz->dato);
		}
		free(raiz->clave);
		free(raiz);
	}
	return; 
}

void abb_destruir(abb_t *arbol){
	if(arbol->cantidad != 0){
		abb_destruir_wrapper(arbol,arbol->raiz);
	}
	free(arbol);
}

// Iterador Interno

void abb_in_order_wrapper(nodo_abb_t *raiz, bool visitar(const char *, void *, void*),void *extra){
	if(raiz != NULL){
		abb_in_order_wrapper(raiz->izq,visitar,extra);	
		if(!visitar(raiz->clave,raiz->dato,extra))
			return;
		abb_in_order_wrapper(raiz->der,visitar,extra);
	}
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
	abb_in_order_wrapper(arbol->raiz,visitar,extra);
}


//Iterador Externo
bool abb_apilar_izq(nodo_abb_t *raiz,abb_iter_t *iter){
    if(!raiz)
        return true;
    if(!pila_apilar(iter->pila,raiz))
        return false;
    return abb_apilar_izq(raiz->izq,iter);
}
 
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t *abb_iter = malloc(sizeof(abb_iter_t));
    if(!abb_iter)   return NULL;
 
    abb_iter->pila = pila_crear();
    if(!abb_iter->pila){
        free(abb_iter);
        return NULL;
    }
    abb_iter->abb = arbol;
    if(!abb_apilar_izq(arbol->raiz,abb_iter)){
        pila_destruir(abb_iter->pila);
        free(abb_iter);
        return NULL;
    } 
    return abb_iter;
}
 
bool abb_iter_in_avanzar_nodo(abb_iter_t *iter,nodo_abb_t *raiz){
    if(!raiz)
        return true;
    if(!abb_apilar_izq(raiz,iter))
        return false;
	return true;
}
 
bool abb_iter_in_avanzar(abb_iter_t *iter){
    if(abb_iter_in_al_final(iter))
        return false;
    nodo_abb_t *aux = pila_desapilar(iter->pila);
    if(!abb_iter_in_avanzar_nodo(iter,aux->der))
        return false; 
    return true;
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
    return pila_esta_vacia(iter->pila);
}
 
const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    nodo_abb_t *actual = pila_ver_tope(iter->pila);
    return !abb_iter_in_al_final(iter) ? actual->clave : NULL;
}
  
void abb_iter_in_destruir(abb_iter_t* iter){
    pila_destruir(iter->pila);
    free(iter);
}
