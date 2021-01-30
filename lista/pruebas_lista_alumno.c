#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <string.h>


#define PRUEBA_ELEMENTOS 1000

void imprimir_iter_externo(lista_t *lista);
bool imprimir_un_entero(void *elemento, void *extra){
    printf("| %d | ->",*(int*)elemento);
    return true; 
}

bool sumar_pares(void *elemento, void *extra){
    if((*(int*) elemento) % 2 == 0 ){
        *(int*)extra += *(int*)elemento;
    }
    return true;
}

bool sumar_adicional(void *elemento, void *extra){
    *(int*)elemento += *(int *)extra;
    return true;
}

//Se quiere probar que se recorre la lista hasta un corte, cuando encuentra algo dentro de la lista
// se corta la iteracion. En este casi, si encuentra un numero de dos cifras se corta la iteracion
bool sumar_hasta(void *elemento, void *extra){
    *(int*)elemento += *(int *)extra;
    if(*(int*)elemento >= 10)
        return false;

    return true;
}

void imprimir_iter_interno(lista_t *lista){
    printf("\033[31m Lista: \033[m \n");
    lista_iterar(lista, imprimir_un_entero,NULL);
    putchar('\n');
}

void pruebas_lista_vacia(void){
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~ Pruebas Lista Vacia ~~~~~~~~~~~~~~~~~~* \033[m \n");
    lista_t *lista0 = lista_crear();
    print_test("La lista se creó correctamente y está vacia",lista0 && lista_esta_vacia(lista0));
    lista_insertar_primero(lista0,NULL);
    lista_insertar_ultimo(lista0,NULL);
    print_test("Agrego NULL tanto con insertar primero y con insertar ultimo, por lo tanto el largo de la lista es 2", lista_largo(lista0) == 2);
    print_test("Los elementos de la lista son el NULL",lista_ver_primero(lista0) == NULL && lista_ver_ultimo(lista0) == NULL);
    print_test("Remuevo los elementos de la lista con borrar primero",lista_borrar_primero(lista0) == NULL && lista_borrar_primero(lista0) == NULL);
    print_test("La lista queda vacia", lista_esta_vacia(lista0));
    print_test("Largo de la lista es 0", lista_largo(lista0) == 0);
    print_test("Pruebo que borrar el primero de una lista vacia es NULL", lista_borrar_primero(lista0) == NULL);
    print_test("Pruebo que ver primero y ver ultimo de una lista vacia da NULL", lista_ver_primero(lista0) == NULL && lista_ver_ultimo(lista0) == NULL);
    int vect[10] = {0,1,2,3,4,5,6,7,8,9};
    for(int i = 5; i < 10; i++){
        lista_insertar_ultimo(lista0,&vect[i]);
    }
    for(int i = 4; i>=0; i--){
        lista_insertar_primero(lista0,&vect[i]);
    }
    printf("Se insertan 10 enteros en la lista \n");
    imprimir_iter_externo(lista0);
    print_test("El primero es el 0 y el ultimo es el 0",*(int*)lista_ver_primero(lista0) == 0 && *(int*)lista_ver_ultimo(lista0) == 9);
    print_test("El largo de la lista es 10", lista_largo(lista0));

    lista_destruir(lista0,NULL);
    print_test("Lista destruida con el uso de NULL como parametro", true);
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* \033[m \n");
}


void pruebas_lista_general(void){
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~ Pruebas Lista General ~~~~~~~~~~~~~~~~~~* \033[m \n");
    lista_t *lista1 = lista_crear();
    int vect[PRUEBA_ELEMENTOS];
    int i;
    for(i = 0; i<PRUEBA_ELEMENTOS; i++){
        vect[i] = i;
    }
    print_test("La lista se creó correctamente y está vacia",lista1 && lista_esta_vacia(lista1));
    for(i = 0; i < PRUEBA_ELEMENTOS; i++){
        lista_insertar_ultimo(lista1,&vect[i]);
    }
    print_test("Se insertaron 1000 elementos, el primero es el 0 y el ultimo es el 999", *(int*)lista_ver_primero(lista1) == 0 && *(int*)lista_ver_ultimo(lista1) == 999);
    print_test("Lista largo es de 1000", lista_largo(lista1) == PRUEBA_ELEMENTOS);
    bool result = true;
    for(i = 0; i< PRUEBA_ELEMENTOS/2 ; i++){
        if(*(int*)lista_borrar_primero(lista1) != vect[i])
             result = false;
    }
    //imprimir_iter_externo(lista1);
    printf("Lista largo %zu \n",lista_largo(lista1));

    print_test(" Se borraron la mitad de los elementos de la lista 1, se cumple que cada borrado sea igual al que estaba en la lista", result);
    print_test("El primero de la lista debe ser 500 y el ultimo 999",  *(int*)lista_ver_primero(lista1) == 500 && *(int*)lista_ver_ultimo(lista1) == 999);


    lista_destruir(lista1,NULL);
    print_test("Lista 1 fue destruida",true);
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* \033[m \n");    
}

void pruebas_iterador_interno(void){
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~ Pruebas Iterador Interno ~~~~~~~~~~~~~~~~~~~~* \033[m \n");
    lista_t *lista2 = lista_crear();
    print_test("La lista se creó correctamente y está vacia",lista2 && lista_esta_vacia(lista2));
    int int_array[] = {0,1,2,3,5,6,7,8,9,9,10,11,12};
    size_t tam_int = sizeof(int_array) / sizeof(int_array[0]);
    for(int i = 0; i< tam_int; i++){
        lista_insertar_ultimo(lista2,&int_array[i]);
    }
    printf("Se puede imprimir la lista mediante el iterador interno:\n");
    imprimir_iter_interno(lista2);
    printf("Se prueba que mediante funciones el iterador interno sume todos los numeros pares\n");
    int suma_total = 0;
    lista_iterar(lista2,sumar_pares,&suma_total);
    printf("La suma total de los pares de la lista 2 es: %d \n",suma_total);

    int adicional = 3;
    lista_iterar(lista2,sumar_adicional,&adicional);
    printf("Con la suma adicional, la lista queda: \n");
    imprimir_iter_interno(lista2);

    suma_total = 0;
    lista_iterar(lista2,sumar_pares,&suma_total);
    printf("Con la suma adicional en los elementos de la lista, la suma total de los pares queda: %d \n", suma_total);

    int sumar = 1;
    //Sumo "sumar" hasta que encuentro una condicion de corte que esta en la funcion, si encunetro un numero de dos cifras
    //corto la iteracion
    lista_iterar(lista2,sumar_hasta,&sumar);
    //Con el "sumar hasta" la lista queda:
    imprimir_iter_interno(lista2);


    lista_destruir(lista2,NULL);
    print_test("Se destruyo la lista", true);
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* \033[m \n");  
}

void pruebas_iterador_borde(void){
    printf( "\n \033[36m  *~~~~~~~~~~~~~~~~~~ Pruebas Iterador Casos Borde ~~~~~~~~~~~~~~~~~~* \033[m \n");
    int vect[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    size_t tam_vect = sizeof(vect) / sizeof(vect[0]);
    lista_t *lista3 = lista_crear();
    print_test("La lista se creó correctamente y está vacia",lista3 && lista_esta_vacia(lista3));
    for(int i = 0; i< tam_vect; i++){
        lista_insertar_ultimo(lista3,&vect[i]);
    }
    print_test(" El largo de la lista es 12",lista_largo(lista3) == tam_vect);
    lista_iter_t *iter  = lista_iter_crear(lista3);
    print_test("Se creó el iterador sobre la lista 3",iter);
    print_test("Se agregaron elementos del 1 al 12 a la lista el iterador actual devuelve el primer elemento, el 0",*(int*)lista_iter_ver_actual(iter) == vect[0]);
    int b = 99;
    lista_iter_insertar(iter,&b);
    print_test("Se inserta un elemento(99) en la primera posicion de la lista", *(int*)lista_ver_primero(lista3) == 99);
    print_test("Se aumenta el largo de la lista a 13",lista_largo(lista3) == tam_vect +1);
    printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    //imprimir_iter_externo(lista3);
    for(int i = 0; i< tam_vect/2; i++){
        lista_iter_avanzar(iter);
    }
    // printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    print_test("Se avanzo el iteraror hasta la mitad de los elementos, actual ahora es 6",*(int*)lista_iter_ver_actual(iter) == vect[tam_vect/2 - 1]);
    lista_iter_insertar(iter,&b);
    print_test("Se inserto un valor 99 en el medio de la lista, el actual ahora es 99",*(int*)lista_iter_ver_actual(iter) == 99);
    print_test("El largo de la lista aumenta  a 14 ", lista_largo(lista3) == 14);

    for(size_t i = tam_vect/2; i< tam_vect + 1; i++){
        lista_iter_avanzar(iter);
    }
    printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    print_test("El iterador esta al final de la lista, el elemento es el 12",*(int*)lista_iter_ver_actual(iter) == 12);
    // // lista_iter_borrar(iter);
    // // print_test("Si borro el utlimo de la lista con el iterador, el ultimo de la lista cambia, de 12 pasa a 11",*(int*)lista_ver_ultimo(lista3) == 11);
     lista_iter_avanzar(iter);
    print_test("Si avanzo una posicion mas, el iterador esta al final, terminó", lista_iter_al_final(iter));
     lista_iter_insertar(iter,&b);
    print_test("El iterador esta al final, si agrego el elemento 99, se comporta como insertar al final",*(int*)lista_ver_ultimo(lista3) == 99);
    printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    lista_iter_avanzar(iter);
    
    print_test("Si avanzo una posicion mas, el iterador esta al final, terminó", lista_iter_al_final(iter));
    int a = 66;
    lista_iter_insertar(iter,&a);
    print_test("El iterador esta al final, si agrego el elemento 66, se comporta como insertar al final",*(int*)lista_ver_ultimo(lista3) == 66);
 
    
    imprimir_iter_interno(lista3);
lista_iter_destruir(iter);
    lista_destruir(lista3,NULL);
    print_test("Se elimino la lista3",true);
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* \033[m \n");
}

void prueba_iter_externo_elementos(void){
    lista_t * lista4 = lista_crear();
    int vect[4] = {1,2,3,4};
    lista_iter_t *iter = lista_iter_crear(lista4);
    print_test("La lista se creó correctamente y está vacia",lista4 && lista_esta_vacia(lista4));
    print_test("Se creó el iterador sobre la lista 4",iter);
    print_test("Se inserta v[0] = 1",lista_iter_insertar(iter,&vect[0]));
    print_test("insero vect[0] primero y se compporta como insertar al principio",*(int*)lista_ver_primero(lista4) == vect[0]);
    print_test("Se inserta v[1] = 2",lista_iter_insertar(iter,&vect[1]));
    print_test("insero vect[1] y ahora el primero es el recien insertado",*(int*)lista_ver_primero(lista4) == vect[1]);
    //printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    print_test("Se inserta v[2] = 3",lista_iter_insertar(iter,&vect[2]));
    //printf("Pri: %d \t Ult: %d \n",*(int*)lista_ver_primero(lista4),*(int*)lista_ver_ultimo(lista4));

    print_test("Inserto vect[2] y ahora el primero es el recien insertado",*(int*)lista_ver_primero(lista4) == vect[2]);
    print_test("elimino el  primero, debe coindicir con el vect[2]",*(int*)lista_iter_borrar(iter) == vect[2]);
    print_test("El actual ahora es vect[1]",*(int*)lista_iter_ver_actual(iter) == vect[1]);
    print_test("elimino el  segundo, debe coindicir con el vect[1]",*(int*)lista_iter_borrar(iter) == vect[1]);
    print_test("El actual ahora es vect[0]",*(int*)lista_iter_ver_actual(iter) == vect[0]);
    print_test(" quedaria un solo elemento, tanto el primero de la lista como el utlimo deben coincidir",*(int*)lista_ver_primero(lista4) ==  *(int*)lista_ver_ultimo(lista4));
    print_test("Prueba que lista largo vale 1",lista_largo(lista4) == 1);
    //print_test("Avanzar es falso",!lista_iter_avanzar(iter));
    print_test("elimino el  ultimo elemento, debe coindicir con el vect[0]",*(int*)lista_iter_borrar(iter) == vect[0]);
    print_test("Prueba que iter borrar da NULL",lista_iter_borrar(iter) == NULL );
    print_test("Prueba que no se puede avanzar en lista vacia", !lista_iter_avanzar(iter));

    print_test("No quedan elementos, ver primero es NULL",lista_ver_primero(lista4) == NULL);
     print_test("No quedan elementos, ver ULTIMO es NULL",lista_ver_ultimo(lista4) == NULL);

    print_test("lista queda vacia", lista_esta_vacia(lista4));
    print_test("Prueba que lista largo es 0", lista_largo(lista4) == 0);
    lista_iter_destruir(iter);
    lista_destruir(lista4,NULL);
    print_test("Se elimino la lista4 y el iterador",true);
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* \033[m \n");
}

void pruebas(void){
    lista_t *lista5 = lista_crear();
    int vect[3] = {1,2,3};
    print_test("Se inserta ultimo el primer valor,1",lista_insertar_ultimo(lista5,&vect[0]));
    print_test("Se inserta ultimo el primer valor,2",lista_insertar_ultimo(lista5,&vect[1]));
    print_test("Se inserta ultimo el primer valor,3",lista_insertar_ultimo(lista5,&vect[2]));
    lista_iter_t *iter = lista_iter_crear(lista5);
    print_test("Iter no esta al final", !lista_iter_al_final(iter));
    print_test("Ver actual es el valor 1", *(int*)lista_iter_ver_actual(iter) == vect[0]);
    print_test("Avanzar es true",lista_iter_avanzar(iter));
    print_test("Ver actual es el valor 2", *(int*)lista_iter_ver_actual(iter) == vect[1]);
    print_test("Borrar el actual, borro el 2", *(int*)lista_iter_borrar(iter) == vect[1]);
    print_test("Lista largo ahora pasa a 2", lista_largo(lista5) == 2);
    print_test("El actual ahora es el 3",*(int*)lista_iter_ver_actual(iter) == vect[2]);
    print_test("Borrar el actual, borro el 3", *(int*)lista_iter_borrar(iter) == vect[2]);
    print_test("Lista largo ahora pasa a 1", lista_largo(lista5) == 1);
    print_test("Si avanzo ahora, es false", !lista_iter_avanzar(iter));
    print_test("Prueba que iter borrar es NULL, ya que actual ahora es NULL, porque habia avanzo del primer elemento", lista_iter_borrar(iter) == NULL);
    print_test("Prueba que iter actual es NULL", lista_iter_ver_actual(iter) == NULL);
    lista_iter_destruir(iter);

    lista_iter_t *iter2 = lista_iter_crear(lista5);
    print_test("Creo un nuevo iter sobre lista5", iter2);
    print_test("Ver actual es el valor 1", *(int*)lista_iter_ver_actual(iter2) == vect[0]);
    print_test("Puedo avanzar con el nuevo iterador", lista_iter_avanzar(iter2));
    print_test("El actual es nULO",lista_iter_ver_actual(iter2) == NULL);
    print_test("Prueba que iter2 avanza falla", !lista_iter_avanzar(iter2));
    lista_iter_destruir(iter2);

    lista_destruir(lista5,NULL);
}

//void pruebas_lista_

void pruebas_lista_alumno(void){
    pruebas_lista_vacia(); //OK
    pruebas_lista_general(); //OK
    pruebas_iterador_interno(); //OK
    pruebas_iterador_borde(); //OK   
    prueba_iter_externo_elementos(); //OK
    pruebas();
}



void imprimir_iter_externo(lista_t *lista){
    lista_iter_t *iter = lista_iter_crear(lista);
    printf("\033[31m Lista: \033[m \n");
    while (!lista_iter_al_final(iter))
    {
        int *elemento = lista_iter_ver_actual(iter);
        printf("| %d | -> ", *elemento);
        lista_iter_avanzar(iter);
    }
    printf("\n\n");
    lista_iter_destruir(iter);
}


