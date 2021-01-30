//Aca pongo todo lo que sobra del abb para no perderlo 

// bool abb_obtener_wrapper(const abb_t *arbol,nodo_abb_t *raiz,const char *clave){
// 	if(!raiz)
// 		return NULL;


// 	if(raiz->comparar(clave,raiz->clave) <= MENOR){
// 		return abb_pertenece(arbol,raiz->izq,clave);
// 	} // me tengo que ir al izquierdo
	
// 	if(!arbol->comparar(raiz->clave,clave))
// 		return raiz->dato; //Encontré el dato

// 	if(arbol->comparar(clave,raiz->clave) >= MAYOR){
// 		return abb_pertenece(arbol,raiz->der,clave);
// 	} // me tengo que ir al derecho

//     return NULL;
// }


//	return abb_obtener_wrapper(arbol,arbol->raiz,clave);

// bool abb_pertenece_wrapper(const abb_t *arbol,nodo_abb_t *raiz,const char *clave){ //RESPETA EL RECORRIDO IN ORDER (IZQ-RAIZ-DER)
// 	if(!raiz)
// 		return false; 

// 	if(raiz->comparar(clave,raiz->clave) <= MENOR){
// 		return abb_pertenece_wrapper(arbol,raiz->izq,clave);
// 	} // me tengo que ir al izquierdo

// 	if(!arbol->comparar(raiz->clave,clave))
// 		return true; //Encontré la clave


// 	if(arbol->comparar(clave,raiz->clave) >= MAYOR){
// 		return abb_pertenece_wrapper(arbol,raiz->der,clave);
// 	} // me tengo que ir al derecho
	
//     return false;
// }

// bool abb_guadar_wrapper(abb_t *arbol, nodo_abb_t *raiz, nodo_abb_t *nodo){
// 	if(!comparar(raiz->clave,nodo->clave)) // UN NODO YA EXISTENTE TIENE LA MISMA CLAVE
// 		return false;
	
// 	if(comparar(nodo->clave,raiz->clave) <= MENOR){ //El nodo está en un valor mas chico que la raiz, tengo que doblar a la izq
// 		if(!raiz->izq){ // EL IZQUIERDO DE LA RAIZ NO ESTÁ POR LO TANTO AHORA EL IZQUIERDO APUNTA A ESTE NODO
// 			raiz->izq = nodo;
// 			return true;
// 		}
// 		else 
// 			abb_guadar_wrapper(arbol,raiz->izq,nodo); // LA RAIZ IZQUIERDA EXISTE POR LO TANTO TENGO QUE SEGUIR BUSCANDO PERO PONGO COMO RAIZ A RAIZ->IZQ
// 	} 
	
// 	if(comparar(nodo->clave,raiz->clave) >= MAYOR){ // ES IGUAL QUE EN RAIZ IZQUIERDA PERO AHORA ES PARA LA DERECHA
// 		if(!raiz->der){
// 			raiz->der = nodo;
// 			return true;
// 		}
// 		else 
// 			abb_guardar_wrapper(arbol,raiz->der,nodo);
// 	}

// }

/*Tengo la duda si la hacemos que devuelva un nodo_abb_t, o si tiene que devolver un entero o un bool.
Osea, esta la tenemos que usar en las 4 primitivas, busca y devuelve si lo encontró u no.
En guardar-> si encuentra el lugar donde meterlo devolveria ese nodo e inserto el nuevo nodo a izq o der del nodo que devuevle.
En pertence-> true o false
En obtener-> devuelve el dato que tiene ese nodo
En borrar -> devuelve la posicion en que esta para luego proceder como se deba en borrar.
*/
// nodo_abb_t* buscar(nodo_abb_t *raiz,const char *clave,abb_comparar_clave_t cmp){
	
// 	if(!raiz) return NULL;
// 	else if(!raiz->izq && !raiz->der)
// 		return raiz;
// 	else if(cmp(raiz->clave,clave) == 0)
// 		return raiz;
// 	else if(cmp(raiz->clave,clave) < 0)
// 		return buscar(raiz->izq,clave,cmp);
// 	else if(cmp(raiz->clave,clave) > 0)
// 		return buscar(raiz->der,clave,cmp);	
// }

/*	    else if(arbol->comparar(clave,ultimo->clave) < 0) //está en izquierda
    		ultimo->izq = nodo;
    	else ultimo->der = nodo;
*/


