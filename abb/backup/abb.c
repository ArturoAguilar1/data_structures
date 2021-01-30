#define  _POSIX_C_SOURCE 200809L
#include <string.h>
#include <stdio.h>
#include "abb.h"

#include "pila.h"

#define MENOR -1
#define MAYOR 1

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

// nodo_abb_t** abb_nodo_buscar(nodo_abb_t **raiz,const char *clave,abb_comparar_clave_t cmp){
// 	//nodo_abb_t *aux = *raiz;
// 	if(!aux)
// 		return NULL;

// 	if(!cmp(aux->clave,clave))
// 		return raiz;

// 	// else if(cmp(clave,raiz->clave) < 0 && raiz->izq)
// 	// 	return abb_nodo_buscar(raiz->izq,clave,cmp);
	
// 	// else if(raiz->der)
// 	// 	return abb_nodo_buscar(raiz->der,clave,cmp);		
	
// 	else if(cmp(clave,aux->clave) < 0){
// 		if(!aux->izq)
// 			return &aux->izq;
// 		return abb_nodo_buscar(&aux->izq,clave,cmp);
// 	}
// 	else{
// 		if(!aux->der)
// 			return &aux->der;
// 		return abb_nodo_buscar(&aux->der,clave,cmp);		
// 	}
// }
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

void imprimir_strings(void * str){
    printf(" %s \n",(char*)str);
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	if(!arbol)	return false;
	if(!arbol->raiz){
		nodo_abb_t* nodo = abb_nodo_crear(clave,dato);
		if(!nodo)	return false;
		arbol->raiz = nodo;
		arbol->cantidad++;
		return true;
	}
	/*
	// nodo_abb_t *nodo_buscado = abb_nodo_buscar(arbol->raiz,clave,arbol->comparar);
	// if(arbol->raiz && !arbol->comparar(nodo_buscado->clave,clave)){
	//  	if(arbol->destruir)
	// 		arbol->destruir(nodo_buscado->dato); 	
	//  	nodo_buscado->dato = dato;
	// 	return true;
	// }	// HAY UN NODO YA EXISTENTE QUE YA TIENE LA MISMA CLAVE.

	// nodo_abb_t *nodo_insertar = abb_nodo_crear(clave,dato);
	// 	if(!nodo_insertar)	return false;
		
	// if(!nodo_buscado)
	// 	arbol->raiz = nodo_insertar;

	// else if(arbol->comparar(nodo_insertar->clave,nodo_buscado->clave) < 0)
	// 	nodo_buscado->izq = nodo_insertar;
	

	// else if(arbol->comparar(nodo_insertar->clave,nodo_buscado->clave) > 0)
	// 	nodo_buscado->der = nodo_insertar;
	*/
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
	
    
    imprimir_arbol(arbol,imprimir_strings);
	
	arbol->cantidad++;
    return true;
}


void *abb_borrar(abb_t *arbol, const char *clave){
	// if(!arbol)
	//     return NULL;

	// nodo_abb_t *borrado = abb_nodo_buscar(arbol->raiz,clave,arbol->comparar);
	// if(!borrado)
	// 	return NULL; //No encontré la clave
	// void * dato = NULL;
	// if(!borrado->izq && !borrado->der){ //EL NODO NO TIENE HIJOS, OJALA FUESE EL UNICO CASO
	// 	dato = borrado->dato;
	// 	free(borrado->clave);
	// 	free(borrado);
	// }

	// else if((!borrado->izq && borrado->der) || (borrado->izq && !borrado->der))
	// 	return; // EL NODO TIENE UN HIJO.
	return NULL;

}


// void *abb_obtener(const abb_t *arbol, const char *clave){
// 	if(!arbol)
// 	    return NULL;

// 	nodo_abb_t *obtenido = abb_nodo_buscar(arbol->raiz,clave,arbol->comparar);
//     return obtenido ? obtenido->dato : NULL;
// }

// bool abb_pertenece(const abb_t *arbol, const char *clave){
// 	if(!arbol)
// 	    return false;

// 	nodo_abb_t *obtenido = abb_nodo_buscar(arbol->raiz,clave,arbol->comparar);
// 	return obtenido; //si existe devuelve true si no existe devuelve false;

// }

size_t abb_cantidad(abb_t *arbol){
    return arbol->cantidad;
}

void abb_destruir_wrapper(abb_t *arbol, nodo_abb_t * raiz){
	
	if(raiz && raiz->izq)
		abb_destruir_wrapper(arbol,raiz->izq);
	// me tengo que ir al izquierdo
	
	if(raiz && raiz->der)
		abb_destruir_wrapper(arbol,raiz->der);
	 // me tengo que ir al derecho
	
	if(raiz){ // estoy en una hoja , tengo que liberar de abajo para arriba, CREO QUE NO ES NECESARIO PREGUNTAR SI RAIZ EXISTE, PERO COMO DIJIMOS A PRINCIPIO HAGAMOSLO TODO RUSTICO
		if(arbol->destruir)
			arbol->destruir(raiz->dato);
		free(raiz->clave);
		free(raiz);
	}
	return; 
}

void abb_destruir(abb_t *arbol){
	if (!arbol)
	    return;
	abb_destruir_wrapper(arbol,arbol->raiz);
	free(arbol);
}

// Iterador Interno
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){
    return;
}

//Iterador Externo

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t *abb_iter = malloc(sizeof(abb_iter_t));
    if(!abb_iter)   return NULL;

	abb_iter->pila = pila_crear();
	if(!abb_iter->pila){
		free(abb_iter);
		return NULL;
	}
	//pila_apilar();


    abb_iter->abb = arbol;


    return abb_iter;
}


// bool abb_iter_in_avanzar(abb_iter_t *iter){
//     if (abb_iter_in_al_final(iter))
//     	return false;

//     	if(iter->actual->izq)
//     		iter->actual = iter->actual -> izq;
//     	else if(iter->actual->der)
// 	    	iter->actual = iter->actual -> der; // 
    	
//     	return true;
// }

// bool abb_iter_in_al_final(const abb_iter_t *iter){
// 	return (!iter->actual || (!iter->actual->izq && !iter->actual->der))
// }
// // Hay dos casos que considerar, este es el caso 1 que te lo explico por wp 

// bool abb_iter_in_al_final(const abb_iter_t *iter){
// 	return !iter->actual;
// } // caso 2

//Si la pila esta vacia, quiere decir que el iter llegó al final.
bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	return (char*)pila_ver_tope(iter->pila);
}


// const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
// 	return !abb_iter_in_al_final(iter) ? iter->actual->clave : NULL;
// }

// bool abb_iter_in_avanzar(abb_iter_t *iter){
//     if (abb_iter_in_al_final(iter))
//     	return false;

//     	if(iter->actual->izq)
//     		iter->actual = iter->actual -> izq;
//     	else
// 	    	iter->actual = iter->actual -> der; // 
    	
//     	return true;
// }

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
    free(iter);
}


