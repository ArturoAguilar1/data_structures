#include "heap.h"
#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comparar_enteros(const void *a,const void *b){
    if(*(int*)a > *(int*)b)
        return 1;
    else if( *(int*)a < *(int*)b)
        return -1;
    else
        return 0;     
}
int comparar_doubles(const void *a,const void *b){
    if(*(double*)a > *(double*)b)
        return 1;
    else if( *(double*)a < *(double*)b)
        return -1;
    else
        return 0;     
}

void pruebas_heap_vacio(void){
    heap_t *heap = heap_crear(comparar_enteros);

    print_test("Prueba heap crear heap vacio",heap);
    print_test("Prueba heap la cantidad es cero",heap_cantidad(heap) == 0);
    print_test("Prueba heap desencolar de algo que esta vacio es NULL",heap_desencolar(heap) == NULL);
    print_test("Prueba heap ver max de un heap vacio no existe",heap_ver_max(heap) == NULL);
    print_test("Prueba heap esta vacio",heap_esta_vacio(heap));

    heap_destruir(heap,free);
    print_test("El heap fue destruido correctamente",true);
}

void pruebas_heap_con_double(void){
    heap_t *heap = heap_crear(comparar_doubles);
    double valor1 = 1.23; double valor2 = 2.34; double valor3 = 5.67; double valor4 = 0.12; double valor5 = 9.01;
    print_test("No hay elementos en un heap recien creado",!heap_cantidad(heap));
    print_test("El heap entonces está vacio",heap_esta_vacio(heap));
    print_test("Prueba heap encolar el valor1 = 1",heap_encolar(heap,&valor1));
    print_test("Prueba heap encolar el valor2 = 2",heap_encolar(heap,&valor2));
    print_test("Prueba heap encolar el valor3 = 5",heap_encolar(heap,&valor3));
    print_test("Prueba heap encolar el valor4 = 0",heap_encolar(heap,&valor4));
    print_test("Prueba heap encolar el valor5 = 9",heap_encolar(heap,&valor5));
    //heap_imprimir(heap);
    print_test("Prueba heap no esta vacio",!heap_esta_vacio(heap));
    print_test("Prueba heap cantidad es 5", heap_cantidad(heap) == 5);
    print_test("Prueba heap ver el maximo es el valor5 = 9", *(double*)heap_ver_max(heap) == valor5);
    print_test("Prueba heap desencolar me devuelve el valor5",*(double*)heap_desencolar(heap) == valor5);
    //heap_imprimir(heap);
    print_test("Prueba heap la cantidad disminuye, la cantidad es 4", heap_cantidad(heap)==4);
    print_test("Prueba heap, ahora el maximo es el valor3 = 5",*(double*)heap_ver_max(heap) == valor3);
    print_test("Prueba heap desencolar el valor3",*(double*)heap_desencolar(heap) == valor3);
    print_test("El maximo cambia nuevamente, es el valor2 = 2",*(double*)heap_ver_max(heap) == valor2);
    print_test("Prueba heap la cantidad queda en 3", heap_cantidad(heap) == 3);
    //heap_imprimir(heap);
    heap_destruir(heap,NULL);
    print_test("El heap fue destruido correctamente",true);
}

void pruebas_heap_crear_desde_arreglo(void){
    int arr[9] = {0,3,6,1,7,11,2,4,8};
    void **v = malloc(sizeof(void*) * 9);
    for(size_t i = 0; i < 9; i++){
        v[i] = &arr[i];
        printf("V: %d \t",*(int*)v[i]);
    }
    printf("\n");
    // int valor1 = 1; int valor2 = 2; int valor3 = 5; int valor4 = 0; int valor5 = 9;
    // int valor1 = 7; int valor7 = 11; int valor8 = 8; int valor9 = 3; int valor10 = 10;
    heap_t *heap = heap_crear_arr(v,9,comparar_enteros);
    print_test("Prueba heap ver max desde un arreglo es 11", *(int*)heap_ver_max(heap));
    size_t cant_arr = sizeof(arr)/sizeof(arr[0]);
    print_test("Prueba heap la cantidad de eleemntos del heap es la misma que elementos del arreglo",heap_cantidad(heap) == cant_arr);
    free(v);
    //heap_imprimir(heap);
    heap_destruir(heap,NULL);
}

int aleatorio_en_rango(int minimo, int maximo) {
    return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
}

void desordenar_arreglo(int *v,int largo){
    for (int i = 0; i < largo; i++) {
        int indice_aleatorio = aleatorio_en_rango(0, largo - 1);
        int temporal = v[i];
        v[i] = v[indice_aleatorio];
        v[indice_aleatorio] = temporal;
    }
}


void pruebas_heapsort(void){
    int arr[9] = {0,3,6,1,7,11,2,4,8};
    void **v = malloc(sizeof(void*) * 9);

    for(size_t i = 0; i < 9; i++)
        v[i] = &arr[i];
    

    printf("Antes de ordenar \n");    
 
    for(size_t i = 0; i < 9; i++)
        printf("%d ",*(int*)v[i]);

    heap_sort(v,9,comparar_enteros);
    
    printf("Despues de ordenar con heapsort \n");

    for(size_t i = 0; i < 9; i++)
        printf("%d ",*(int*)v[i]);

    free(v);
    printf("Heapsort en volumen:\n");

    int *arr2 = malloc(sizeof(int) * 5000);
    for(int i = 0; i < 5000; i++){
        arr2[i] = i;
    }
    desordenar_arreglo(arr2,5000);
    void **v2 = malloc(sizeof(void*)*5000);
    for(size_t i = 0; i < 5000; i++){
        v2[i] = &arr2[i];
    }
    // printf("Antes de heapsort \n");
    // for(size_t i = 0 ; i < 5000; i++){
    //     printf(" %d \t",*(int*)v2[i]);
    // }
    // printf("\n");
    heap_sort(v2,5000,comparar_enteros);
    // printf("Despues de heapsort \n");
    // for(size_t i = 0 ; i < 5000; i++){
    //     printf(" %d \t",*(int*)v2[i]);
    // }
    free(arr2);
    free(v2);
}

void pruebas_volumen(void){
    int arr[5000];
    heap_t * heap = heap_crear(comparar_enteros);
    for(int i = 0;i<5000;i++){
        arr[i] = i+1;
        heap_encolar(heap,&arr[i]);
    }
    print_test("La lista no está vacia",!heap_esta_vacio(heap));
    print_test("La cantidad del heap es de 5000 elementos",heap_cantidad(heap) == 5000);
    print_test("El máximo del heap coincide",*(int*)heap_ver_max(heap) == 5000);
    print_test("Desencolo el primero del heap y coincide",*(int*)heap_desencolar(heap) == 5000);
    print_test("Vuelvo a desencolar y veo que coincide el",*(int*)heap_desencolar(heap) == 4999);
    print_test("El máximo coincide",*(int*)heap_ver_max(heap) == 4998);
    print_test("El heap no está vacio",!heap_esta_vacio(heap));
    print_test("La cantidad coincide",heap_cantidad(heap) == 4998);

    for(int i = 0;heap_cantidad(heap) > 1;i++)
        heap_desencolar(heap);
    
    print_test("Probé desencolar hasta que el heap tenga un elemento",heap_cantidad(heap) == 1);
    print_test("El máximo coincide",*(int*)heap_ver_max(heap) == 1);
    print_test("Desencolé el ultimo",*(int*)heap_desencolar(heap) == 1);
    print_test("Por lo tanto el heap está vacio",heap_esta_vacio(heap));
    heap_destruir(heap,free);
    print_test("El heap fue destruido correctamente",true);
}

void pruebas_volumen_heapify(void){
    int arr[5000];
    for(int i = 0;i<5000;i++){
        if(i % 2 == 0)
            arr[i] = i-5; // Es para darle un arreglo desordenado y que aplique heapify
        else arr[i] = i+1;
    }
    
    void **v = malloc(sizeof(void*) * 5000);
    for(size_t i = 0; i < 5000; i++)
        v[i] = &arr[i];

    heap_t *heap = heap_crear_arr(v,5000,comparar_enteros);
    print_test("El maximo coincide",*(int*)heap_desencolar(heap) == 5000);
    print_test("Luego de desencolar el maximo, el nuevo maximo coincide",*(int*)heap_ver_max(heap) == 4998);
    free(v);
    //heap_imprimir(heap);
    heap_destruir(heap,NULL);   
    print_test("El heap fue destruido correctamente",true);    
}


void pruebas_heap_alumno(void){
    //Llamar aca a todas:
    pruebas_heap_vacio(); //OK && VALGRIND
    pruebas_heap_con_double(); //OK && VALGRIND
    pruebas_heap_crear_desde_arreglo(); //OK && VALGRIND
    pruebas_heapsort(); //OK && VALGRIND
    pruebas_volumen(); //OK && VALGIND
    pruebas_volumen_heapify(); //OK && VALGRIND

}




