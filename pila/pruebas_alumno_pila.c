#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRUEBA_VOLUMEN 10001
#define PRUEBA_ELEMENTOS 1001



/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


void pruebas_borde(){
     printf( "\n \033[104m -*-*-*-*-*-*-*-* Pruebas Borde Pila-*-*-*-*-*-*-*-* \033[m \n");
    pila_t *pila2 = pila_crear();
    //Condicion de borde:  la acción de esta_vacía en una pila recién creada es verdadero.
    print_test("Accion de pila esta vacia en una pila recien creada es true",pila_esta_vacia(pila2));
    void *aux = pila_desapilar(pila2);

    //Condiciones de borde:las acciones de desapilar y ver_tope en una pila recién creada son inválidas.
    print_test("Pruebo que desapilar de una pila vacia es NULL", aux == NULL);
    aux = pila_ver_tope(pila2);
    print_test("Pruebo que ver tope de una pila vacia es NULL", aux == NULL);
    
    pila_apilar(pila2,NULL);
    print_test("Pruebo que el apilamiento del NULL es válido",pila_ver_tope(pila2) == NULL);
    print_test("Pruebo que al apilar NULL, la pila no está vacía", pila_esta_vacia(pila2) == false);

    
    pila_destruir(pila2);
    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");
}

void pruebas_pila_vacia(){
    printf( "\n \033[104m -*-*-*-*-*-*-*-* Pruebas Pila Vacia-*-*-*-*-*-*-*-* \033[m \n");
    pila_t *pila = pila_crear();
    print_test("La pila se creó correctamente:",pila);
    print_test("Pila recien creada está vacia:", pila_esta_vacia(pila));
    print_test("El tope de una pila recien creada es NULL:",pila_ver_tope(pila) == NULL);
    print_test("Desapilar una pila vacia devuelve NULL:",pila_desapilar(pila) == NULL);
    pila_destruir(pila);    
    print_test("Pila fue destruida: ", true);

    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");
}

void pruebas_elementos(){
    printf( "\n \033[104m -*-*-*-*-*-*-*-* Pruebas Pila Con Algunos Elementos y Volumen-*-*-*-*-*-*-*-* \033[m \n");
    pila_t *pila = pila_crear();
    int a = 1;
    print_test("Apilar un elemento funciona correctamente: ",pila_apilar(pila,&a));
    print_test("Pila ya no está vacia",pila_esta_vacia(pila) == false);
    print_test("El tope de la pila es el elemento apilado, en este caso el entero 1:",*(int*)pila_ver_tope(pila) == a);
    print_test("Desapilo y devuelve ese elemento:",*(int*)pila_desapilar(pila) == a);
    print_test("Pila quedo vacia:",pila_esta_vacia(pila));
    print_test("Desapilo la pila vacia devuelve NULL:",pila_desapilar(pila) == NULL);
    print_test("El tope de la pila es NULL:",pila_ver_tope(pila) == NULL);   

    //Pruebo con algunos elementos, apilo 1000 elementos.
    int vect[PRUEBA_ELEMENTOS];
    for(int i = 0; i <  PRUEBA_ELEMENTOS; i++){
        vect[i] = i;
    }

    for(size_t i = 0; i < PRUEBA_ELEMENTOS; i++){
        pila_apilar(pila,vect + i);
    }
    //pila_imprimir(pila,PRUEBA_ELEMENTOS);
    print_test("Apilo elementos, del 0 al 1000 \n Veo que el tope de la pila sea el correcto: 1000",*(int *)pila_ver_tope(pila) == 1000);

    //Desapilo la mitad de la pila

    int j = PRUEBA_ELEMENTOS -1;
    bool result = false;

    for(int i = 0; i < PRUEBA_ELEMENTOS/2 ; i++){
        if(*(int*)pila_desapilar(pila) == vect[j--])
            result = true;
    }
    print_test("Pruebo desapilar la mitad de los elementos de la pila, resultado: ",result);
    print_test("Desapilo la mitad de la pila, el tope quedaría a la mitad: 500",*(int *)pila_ver_tope(pila) == 500);

    result = false;
    for(int i = 0; i < PRUEBA_ELEMENTOS/2 +1 ; i++){
        if(*(int*)pila_desapilar(pila) == vect[j--])
            result = true;
    }
    print_test("Desapilo el resto de la pila, resultado:",result);
    print_test("Pila queda vacía...",pila_esta_vacia(pila));

    //Condición de borde: las acciones de desapilar y ver_tope en una pila a la que se le apiló y desapiló hasta estar vacía son inválidas.
    print_test("Pruebo que ver el tope de una pila es inválido...", pila_ver_tope(pila) == NULL);
    print_test("Pruebo que desapilar de una pila que ya fue desapilada es inválido",pila_desapilar(pila) == NULL);


    //Condicion de borde:La pila se desapiló por completo y funciona como una pila recien creada.
    //Prueba Volumen

    int vect2[PRUEBA_VOLUMEN];
    for(int i = 0; i < PRUEBA_VOLUMEN ; i++){
        vect2[i] = i;
    }

    for(size_t i = 0; i < PRUEBA_VOLUMEN; i++){
        pila_apilar(pila,vect2 + i);
    }
    print_test("VOLUMEN : Apilo del 0 al 10000 (incluyendo el 0) Veo que el tope de la pila sea el correcto: 10000",*(int *)pila_ver_tope(pila) == 10000);

    //Desapilo la mitad de la pila
    result = false;
    j = PRUEBA_VOLUMEN - 1;
    for(int i = 0; i < PRUEBA_VOLUMEN/2 ; i++){
        if(*(int*)pila_desapilar(pila) == vect2[j--])
            result = true;
    }

    print_test("Desapilo la mitad de la pila, resultado:",result);
    print_test("Pila desapilada a la mitad, el tope quedaría a la mitad: 5000",*(int *)pila_ver_tope(pila) == 5000);

    //Pruebo apilar con un puntero distinto un arreglo de Strings
    char *string_array[] = {"Hola", "Buenas", "Algoritmos2","Probando","RAM"};
    for(size_t i = 0; i <  5  ; i++){
        pila_apilar(pila,string_array[i]);
    }

    result = strcmp((char*)pila_ver_tope(pila),string_array[4]) == 0 ;
    print_test("Apilo un arreglo de Strings, tope: RAM",result);
    
    int k = 4;
    result = false;
    for(int i = 0; i < 5 ; i++){
        if(strcmp((char*)pila_desapilar(pila),string_array[k--]) == 0){
            result = true;
        }
    }

    print_test("Desapilo el arreglo de Strings, resultado:",result);
    print_test("El tope quedaría nuevamente a la mitad: 5000",*(int *)pila_ver_tope(pila) == 5000);
  
    result = false;
    for(int i = 0; i < PRUEBA_VOLUMEN/2 +1 ; i++){
        if(*(int*)pila_desapilar(pila) == vect2[j--])
            result = true;
    }
    print_test("Desapilo el resto de la pila, la pila queda vacía", pila_esta_vacia(pila));

    pila_destruir(pila);    
    print_test("Pila fue destruida: ", true);
    printf( " \033[104m -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-* \033[m \n");    
}


void pruebas_pila_alumno() {
    pruebas_pila_vacia();
    pruebas_elementos();
    pruebas_borde();
}

