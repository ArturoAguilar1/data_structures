#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stdlib.h>


typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


//Primitivas de la lista

//Crea una lista
//Post: Devuelve una lista vacía
lista_t *lista_crear(void);

//Chequea si hay elementos en la lista
//Pre: La lista fue creada
//Post: Devuelve true si la lista está vacía, false de lo contrario
bool lista_esta_vacia(const lista_t *lista);

//Inserta un elemento la primer posicion de la lista, en la cabeza.
//Pre: La lista fue creada
//Post: Retorna true si se pudo agregar el elemento, false de lo contrario.
bool lista_insertar_primero(lista_t *lista, void *dato);


//Inserta un elemento en la ultima posicion de la lista
//Pre: La lista fue creada
//Post: Retorna true si se pudo agregar el elemento, la lista queda con un elemento más y este está en la ultima posicion.
bool lista_insertar_ultimo(lista_t *lista, void *dato);


//Borra el primer elemento de la lista, NULL si la lista está vacia
//Pre: La lista ya fue creada
//Post: Se borró el primer elemento de la lista, el primer elemento de ahora es el 2do de antes.
void *lista_borrar_primero(lista_t *lista);


//Devuelve el primer elemento de la lista, NULL si la lista está vacia.
//Pre: La lista fue creada.
//Post: Devolvió el puntero al dato pedido.
void *lista_ver_primero(const lista_t *lista);

//Devuelve el ultimo elemento de la lista, NULL si la lista está vacia.
//Pre: La lista fue creada.
//Post: Devolvió el puntero al dato pedido.
void *lista_ver_ultimo(const lista_t* lista);


//Devuelve el largo de la lista
//Pre: la lista ya fue creada.
//Post: Devolvió el valor de la lista.
size_t lista_largo(const lista_t *lista);

//Destruye la lista completamente, recibe un puntero a funcion en caso de que se necesite borrar adentro de la lista.
//Pre: la lista ya fue creada:
//Post: Se destruyó por completo la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


//----------------------------------------------//
//Primitivas del iterador interno

//Recorre todos los elementos de la lista, recibe un puntero a funcion en caso de querer hacer algo con los elementos de la lista.
//Pre: La lista ya fue creada
//Post: Se recorrió completamente la lista y en caso de necesitar hacer algo se hizo.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);




//----------------------------------------------//
//Primitivas del iterador externo

//Crea un iterador sobre la lista que recibe
//Pre: La lista existe y fue creada
//Post: Se devuelve un puntero que apunta a la lista recibida
lista_iter_t *lista_iter_crear(lista_t *lista);

//Avanza sobre la lista.
//Pre: el iterador ya fue creado.
//Post: La posicion actual se avanzo y la posicion anterior tambien.
bool lista_iter_avanzar(lista_iter_t *iter);

//Devuelve el dato actual del iterador
//Pre: El iterador ya fue creado.
//Post: Devolvio el dato u NULL si el iterador ya termino.
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Consulta si el iterador llego al final
//Pre: El iterador ya fue creado.
//Post: Se retorna true si el iterador actual terminó false de lo contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador.
//Pre: el iterador ya esta creado.
//Post: El iterador se eliminó.
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un nodo entre la posicion anterior y actual
//Pre: El iterador ya fue creado
//Post: Se insertó un nuevo nodo en la lista en la que se está iterando
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Elimina el nodo actual(apuntado por el iterador)de la lista.
//Devuelve el puntero al dato que contenia ese nodo
//Pre: el iterador ya fue creado
//Post: Se elimina un nodo de la lista en la cual se está iterando
void *lista_iter_borrar(lista_iter_t *iter);
//----------------------------------------------//



#endif

