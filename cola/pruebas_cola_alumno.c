#include "cola.h"
#include "pila.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>

#define PRUEBA_ELEMENTOS 100

//Funciones auxiliares
void _destruir_dato(void *dato){
    free(dato);
}

void _destruir_pila(void *dato){
    pila_destruir(dato);
}
void apilar_strings(pila_t *pila){
    char *ej[] = {"Hola", "Buenas", "Algoritmos2","Probando","RAM"};
    for(size_t i = 0; i <  5  ; i++){
        pila_apilar(pila,ej[i]);
    }
}

void apilar_ints(pila_t *pila){
    int vect[10] = {0,1,2,3,4,5,6,7,8,9};
    for(int i = 0 ; i < 10; i++){
        pila_apilar(pila,&vect[i]);
    }
}
void apilar_doubles(pila_t *pila){
    double vect[10] = {0.12,1.23,2.45,3.56,4.66,5.77,6.77,7.99,8.88,9.12};
    for(int i = 0 ; i < 10; i++){
        pila_apilar(pila,&vect[i]);
    }
}
//*******************************

// Pruebas

void pruebas_cola_vacia(){
    printf( "\n \033[104m -*-*-*-*-*-*-*-* Pruebas Cola Vacia y Null-*-*-*-*-*-*-*-* \033[m \n");
    cola_t *cola = cola_crear();
    print_test("Se pudo crear la cola",cola);
    print_test("Cola creada, pruebo que la cola está vacía", cola_esta_vacia(cola));
    print_test("Pruebo que desencolar una cola vacía retorna NULL", cola_desencolar(cola) == NULL);
    print_test("Pruebo que ver primero en una cola vacía es NULL", cola_ver_primero(cola) == NULL);
    cola_encolar(cola,NULL);
    print_test("Pruebo que encolar el NULL es válido", cola_ver_primero(cola) == NULL);
    print_test("Prueba que puedo sacar el NULL de la cola", cola_desencolar(cola) == NULL);
    print_test("Cola queda vacía", cola_esta_vacia(cola));
    cola_destruir(cola,free);
    print_test("Cola quedó destruida", true);
    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");
}

void pruebas_elementos(){

    printf( "\n \033[104m -*-*-*-*-*-*-*-* Pruebas Cola Elementos-*-*-*-*-*-*-*-* \033[m \n");
    cola_t *cola1 = cola_crear();
    int vect[PRUEBA_ELEMENTOS];
    for(int i = 0; i<PRUEBA_ELEMENTOS; i++){
        vect[i] = i;
    }
    print_test("Cola1 creada correctamente",cola1);
    print_test("Cola1 esta vacia: ",cola_esta_vacia(cola1));
    for(int i = 0; i < PRUEBA_ELEMENTOS; i++){
        cola_encolar(cola1,&vect[i]);
    }
    print_test("Se encolaron elementos 100 la cola dejó de estar vacia:",!cola_esta_vacia(cola1));
    int j = 0;
    bool result = true;
    for(int i = 0; i< PRUEBA_ELEMENTOS/2; i++){
        if(*(int*)cola_desencolar(cola1) != vect[j++])
            result = false;
    }
    print_test("Desencolo los elementos, verifico que el elemento desencolado es igual al encolado",result);

    print_test("Desencolo la mitad de los elementos, entonces el primer elemento es 50",*(int*)cola_ver_primero(cola1)==50);
    cola_destruir(cola1,NULL);
    print_test("Destruyo la cola, al almanecar datos de memoria estática, se pasa NULL en cola_destruir...",true);

    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");
}


void pruebas_con_pilas(){
    printf( "\n \033[104m -*-*-*-*-*-* Pruebas Cola Con Pilas-*-*-*-*-*-*-* \033[m \n");
    cola_t *cola2 = cola_crear();
    pila_t *pila_strings = pila_crear();
    pila_t *pila_ints = pila_crear();
    pila_t *pila_doubles = pila_crear();

    print_test("Se crearon 3 pilas distintas para encolar; ints, doubles y strings", pila_strings && pila_ints && pila_doubles);
    //{0,1,2,3,4,5,6,7,8,9}
    apilar_ints(pila_ints);

    //{0.12,1.23,2.45,3.56,4.66,5.77,6.77,7.99,8.88,9.12}
    apilar_doubles(pila_doubles);

    //{"Hola", "Buenas", "Algoritmos2","Probando","RAM"}
    apilar_strings(pila_strings);

    cola_encolar(cola2,pila_ints);
    cola_encolar(cola2,pila_strings);
    cola_encolar(cola2,pila_doubles);

    print_test("Se encolaron las 3 pilas, primera pila de ints, primer dato el 0",*(int*)cola_ver_primero(cola2));

    cola_destruir(cola2,_destruir_pila);
    print_test("Se destruyó la cola mediante pila_destruir",true);
    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");
}

void pruebas_con_free(){
    printf( "\n \033[104m -*-*-*-*-*-* Pruebas Cola Con Free-*-*-*-*-*-*-* \033[m \n");
    cola_t *cola3 = cola_crear();
    print_test("cola 3 ccreada correctamente", cola3);
    print_test("Cola3 esta vacía", cola_esta_vacia(cola3));

    int *cero = malloc(sizeof(int));
    cero[0] = 0;
    cola_encolar(cola3,cero);
    print_test("Encolo el cero",*(int*)cola_ver_primero(cola3) == 0);

    int *pares = malloc(sizeof(int)* 7);
    for(int i = 2; i < 5; i+=2){
        pares[i] = i;
    }
    cola_encolar(cola3,pares);

    int *impares = malloc(sizeof(int) *7);
    for(int i = 1; i<5; i+=2){
        impares[i] = i;
    }
    cola_encolar(cola3,impares);
    printf("Se encolaron en cola3 el 0, un vector de pares y un vector de impares\n");

    cola_destruir(cola3,_destruir_dato);
    print_test("Se destruyó la Cola3 mediante free",true);

    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");
}


void pruebas_cola_alumno(void){
    pruebas_cola_vacia();
    pruebas_con_pilas();
    pruebas_elementos();
    pruebas_con_free();


}







