#include "abb.h"

#include "testing.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>  

#define MAX 5000

void pruebas_debug();

void imprimir_strings(void * str){
    printf(" %s \n",(char*)str);
}

void imprimir_enteros(void *dato){
    printf(" %d \n",*(int*)dato);
}

bool visitar(const char *clave, void *dato, void *extra){
    if( !(*(int*)dato % 2 == 0)){
        *(int*)dato *= *(int*)extra;
    }
    return true;
}

int comparar_enteros(const char *a,const char *b){
    int aux_a = atoi(a);
    int aux_b = atoi(b);
    if(aux_a > aux_b)
        return 1;
    else if( aux_a < aux_b)
        return -1;
    else
        return 0; 
    
}

void imprimir_iter_externo(abb_t *arbol){
    abb_iter_t *abb_iter = abb_iter_in_crear(arbol);
    while(!abb_iter_in_al_final(abb_iter)){
        const char *aux = abb_iter_in_ver_actual(abb_iter);
        printf("%s -> ",aux);
        
        abb_iter_in_avanzar(abb_iter);
    }
    printf("\n");
    abb_iter_in_destruir(abb_iter);
}



void prueba_crear_abb_vacio()
{
    abb_t* abb = abb_crear(comparar_enteros,NULL);
 
    print_test("Prueba abb crear abb vacio", abb);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Prueba abb obtener clave A, es NULL, no existe", !abb_obtener(abb, "A"));
    print_test("Prueba abb pertenece clave A, es false, no existe", !abb_pertenece(abb, "A"));
    print_test("Prueba abb borrar clave A, es NULL, no existe", !abb_borrar(abb, "A"));
 
    abb_destruir(abb);
}
 
void prueba_iterar_abb_vacio()
{
    abb_t* abb = abb_crear(comparar_enteros,NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iter crear iterador abb vacio", iter);
    print_test("Prueba abb iter esta al final", abb_iter_in_al_final(iter));
    print_test("Prueba abb iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iter ver actual es NULL", !abb_iter_in_ver_actual(iter));
 
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}
 
 void prueba_abb_insertar()
{
    abb_t* abb = abb_crear(strcmp,NULL);
 
    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
 
    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
 
    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));
 
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
 
    abb_destruir(abb);
}
 
 void prueba_abb_reemplazar()
{
    abb_t* abb = abb_crear(strcmp,NULL);
 
    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";
 
    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
 
    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
 
    abb_destruir(abb);
}
 
 void prueba_abb_reemplazar_con_destruir()
{
    abb_t* abb = abb_crear(strcmp,free);
 
    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;
 
    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));
 
    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));

    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));

    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);

    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
 
    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
 
    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}
 
 void prueba_abb_borrar()
{
    abb_t* abb = abb_crear(strcmp,NULL);
 
    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";
 
    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
 
    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
 
    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave1));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
 
    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave2));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
 
    abb_destruir(abb);
}
 
 void prueba_abb_clave_vacia()
{
    abb_t* abb = abb_crear(strcmp,NULL);
 
    char *clave = "", *valor = "";
 
    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
 
    abb_destruir(abb);
}
 
 void prueba_abb_valor_null()
{
    abb_t* abb = abb_crear(strcmp,NULL);
 
    char *clave = "", *valor = NULL;
 
    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
 
    abb_destruir(abb);
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

 void prueba_abb_volumen(int largo, bool debug)
{
    abb_t* abb = abb_crear(comparar_enteros,free);
 
    const int largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    char clave[largo_clave];
    int *v = malloc(sizeof(int) * MAX);

    //Guardo MAX valores en v
    for(int i = 0; i < largo; i++){
        v[i] = i;
    }
    desordenar_arreglo(v,largo);
    bool ok = true;
    for (size_t i = 0; i < largo; i++) {
        sprintf(claves[i],"%d",v[i]);
        sprintf(clave,"%d",v[i]); 
        ok = abb_guardar(abb,clave,&v[i]);
        if (!ok) break;

    }
     //imprimir_iter_externo(abb);

     printf("Cantidad: %zu \n",abb_cantidad(abb));
     if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
     if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = *(int*)abb_obtener(abb, claves[i]) == v[i];
        if (!ok) break;
    }
    
     if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
     if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    // /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        //void *aux = abb_borrar(abb, claves[i]);
        ok = *(int*)abb_borrar(abb, claves[i]) == v[i];
        if (!ok) break;
    }
 
    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);
 
    // /* Destruye el abb y crea uno nuevo que sí libera */
    // abb_destruir(abb);
    // abb = abb_crear(comparar_enteros,free);
 
    // // // // /* Inserta 'largo' parejas en el abb */
    // ok = true;
    // for (size_t i = 0; i < largo; i++) {
    //     sprintf(clave,"%d",v[i]); 
    //     ok = abb_guardar(abb, clave, &v[i]);
    //     if (!ok) break;
    // }
 

    free(claves);
    free(v);
    // /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);
 
}
 
 ssize_t buscar(const char* clave, char* claves[], size_t largo)
{
    for (size_t i = 0; i < largo; i++) {
        if (strcmp(clave, claves[i]) == 0) return (ssize_t) i;
    }
    return -1;
}
 
 void prueba_abb_iterar()
{
    abb_t* abb = abb_crear(strcmp,NULL);
 
    char *claves[] = {"perro", "gato", "vaca"};
    char *valores[] = {"guau", "miau", "mu"};
 
    /* Inserta 3 valores */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, claves[2], valores[2]));
 
    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    const char *clave;
    ssize_t indice;
 
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
 
    /* Primer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
 
    /* Segundo valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    print_test("Prueba abb iterador avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
 
    /* Tercer valor */
    clave = abb_iter_in_ver_actual(iter);
    indice = buscar(clave, claves, sizeof(claves) / sizeof(char *));
    print_test("Prueba abb iterador ver actual, es una clave valida", indice != -1);
    print_test("Prueba abb iterador ver actual, no es el mismo puntero", clave != claves[indice]);
    abb_iter_in_avanzar(iter);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));
 
    /* Vuelve a tratar de avanzar, por las dudas */
    print_test("Prueba abb iterador ver actual, es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Prueba abb iterador avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));
 
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}
 
 void prueba_abb_iterar_volumen(int largo)
{
    abb_t* abb = abb_crear(comparar_enteros,NULL);
 
    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);
    char clave[largo_clave];
    int *v = malloc(sizeof(int) * largo);
    //size_t valores[largo];
 
    for(int i = 0; i < largo; i++){
        v[i] = i;
    }
     
    desordenar_arreglo(v,largo);
    bool ok = true;
    
    for (int i = 0; i < largo; i++) {
        sprintf(claves[i],"%d",v[i]);
        sprintf(clave,"%d",v[i]); 
        ok = abb_guardar(abb,clave,&v[i]);
        if (!ok) break;
    }
    //imprimir_iter_externo(abb);
    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));
 
    ok = true;
    size_t i;
    const char *clave_bis;
    int *valor;
 
    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave_bis = abb_iter_in_ver_actual(iter);
        if ( clave_bis == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave_bis);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));
 
    ok = true;
    for (i = 0; i < largo; i++) {
        if ( v[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);
 
    free(claves);
    free(v);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void pruebas_abb_catedra()
{
    /* Ejecuta todas las pruebas unitarias. */
    prueba_crear_abb_vacio(); //OK && VALGRIND
    prueba_iterar_abb_vacio(); //OK && VALGRIND
    prueba_abb_insertar(); //OK && VALGRIND
    prueba_abb_reemplazar(); //OK && VALGRIND
    prueba_abb_reemplazar_con_destruir(); //OK && VALGRIND
    prueba_abb_borrar(); //OK && VALGRIND 
    prueba_abb_clave_vacia(); //OK && VALGRIND
    prueba_abb_valor_null(); //OK && VALGRIND 
    prueba_abb_volumen(MAX, true); //OK //ERROR EN VALGRIND
    prueba_abb_iterar(); //OK && VALGRIND
    prueba_abb_iterar_volumen(MAX); //OK  && VALGRIND
}


void pruebas_abb_alumno(void){
    //Aca llamar a todas las funciones de pruebas
   // pruebas_debug();
    pruebas_abb_catedra();
}


void pruebas_debug(){
    abb_t* abb = abb_crear(comparar_enteros,NULL);

    // char *clave1 = "10";//, *valor1 = "guau";
    // char *clave2 = "7";//, *valor2 = "miau";
    // char *clave3 = "15";//, *valor3 = "mu";
    int v[10] = {1,2,3,4,5,5,15,13,12,2};
    //int v[MAX];

    // printf("Desordenado:\n");
    // for(size_t i = 0; i < MAX; i++){
    //     v[i] = rand() % 20;
    //     printf(" %d ",v[i]);
    // }
    // printf("\n");
    // const int largo_clave = 10;
    // char (*claves)[largo_clave] = malloc(MAX * largo_clave);

    // for(int i = 0; i < MAX; i++){
    //     sprintf(claves[i], "%d", v[i]);
    //     abb_guardar(abb,claves[i],&v[i]);
    // }
    // printf("Recorrido del arbol en inorder, ordenado:\n");
    // imprimir_iter_externo(abb);
    // free(claves);
    print_test("Prueba abb insertar clave1", abb_guardar(abb, "1", &v[0]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, "2",&v[1]));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, "4",&v[3]));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, "3", &v[2]));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, "5", &v[4]));
    print_test("Cantidad queda en 5 ", abb_cantidad(abb) == 5);
    // print_test("Prueba abb insertar clave3", abb_guardar(abb, "6",&v[5]));
    // print_test("Prueba abb insertar clave1", abb_guardar(abb, "7", &v[6]));
    imprimir_iter_externo(abb);
    print_test("Pruebo borrar el 1",*(int*)abb_borrar(abb,"1") == 1);
    print_test("Cantidad queda en 4 ", abb_cantidad(abb) == 4);
    imprimir_iter_externo(abb);
    print_test("Pruebo borrar el 2",*(int*)abb_borrar(abb,"2") == 2);
    print_test("Cantidad queda en 3 ", abb_cantidad(abb) == 3);
    imprimir_iter_externo(abb);
    print_test("Pruebo borrar el 4",*(int*)abb_borrar(abb,"4") == 4);
    print_test("Cantidad queda en 2 ", abb_cantidad(abb) == 2);
    printf("En cuanto queda cantidad: %zu \n",abb_cantidad(abb));
    imprimir_iter_externo(abb);

    // printf("\nIter Externo\n");
    // imprimir_iter_externo(abb);

    // abb_in_order(abb,visitar,&v[9]);
    // imprimir_arbol(abb,imprimir_enteros);

    // abb_borrar(abb,"1");
    // abb_borrar(abb,"5");
    //abb_borrar(abb,"10");
    //abb_borrar(abb,"7");
    // printf("\n\n");
    // imprimir_arbol(abb,imprimir_strings);
    // printf("Cantidad: %zu \n",abb_cantidad(abb));
    abb_destruir(abb);
    //    imprimir_arbol(abb,imprimir_strings);
}
