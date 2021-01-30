

    // else if(iter->actual->sig == NULL){
    //     printf("Entre aca\n");
    //     iter->anterior->sig = iter->actual;
    //     aux_nodo = iter->actual;
    //     iter->actual = iter->actual->sig;
    // }
    
            // aux_nodo = iter->actual;    
        // iter->actual = iter->actual->sig;
        // iter->anterior->sig = iter->actual;
        // aux_nodo = iter->actual;
        // iter->actual = iter->actual->sig;
    
    // else{
    //     iter->anterior->sig = iter->actual;
        // aux_nodo = iter->actual;    
        // iter->actual = iter->actual->sig;      
    

    // if(lista_iter_al_final(iter)){
    //     iter->l_iter->ult = iter->anterior;

    // if(lista_iter_al_final(iter))
    //     iter->l_iter->ult = iter->anterior;


//Prueba el iterador externo en su forma general,recorrer, borrar, insertar.
void pruebas_iterador_general(void){
     printf( "\n \033[36m *~~~~~~~~~~~~~~~~~ Pruebas Iterador General~~~~~~~~~~~~~~~~~* \033[m \n");
    int int_array[] = {18,1,3,5,6,7,8,9,9,10,11};
    size_t tam_int = sizeof(int_array) / sizeof(int_array[0]);
    lista_t *lista_enteros = lista_crear();
    
    for(int i = 0; i< tam_int; i++){
        lista_insertar_ultimo(lista_enteros,int_array + i);
    }
    imprimir_iter_externo(lista_enteros);

    lista_iter_t *iter_lista = lista_iter_crear(lista_enteros);
    printf("Si en la lista hay algun entero par, agrego su duplicado:\n");

    while(!lista_iter_al_final(iter_lista)){
        int *elemento = lista_iter_ver_actual(iter_lista);
        if((*elemento % 2) == 0){
            lista_iter_insertar(iter_lista,(int*)elemento);
        }
            lista_iter_avanzar(iter_lista);
        
    }

    imprimir_iter_externo(lista_enteros);


    printf("Luego de duplicar los pares, si hay impares, los elimino \n");
    lista_iter_destruir(iter_lista);
    lista_iter_t *iter2 = lista_iter_crear(lista_enteros);
    while(!lista_iter_al_final(iter2)){
        int *elemento = lista_iter_ver_actual(iter2);
        if(!((*elemento % 2) == 0)){
            int *aux = lista_iter_borrar(iter2);
            // printf("Borrado: %d  \n ", *aux);
        }else{
            lista_iter_avanzar(iter2);
        }
    }
    imprimir_iter_externo(lista_enteros);
    print_test("el iterador actual quedó en NULL",lista_iter_ver_actual(iter2) == NULL);


    printf("ult: %d  \n",*(int*)lista_ver_ultimo(lista_enteros));
    lista_destruir(lista_enteros,NULL);
    printf( "\n \033[36m *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~* \033[m \n");
}

void eliminar_mediante_iter(lista_t *lista){
    lista_iter_t *iter = lista_iter_crear(lista);
    while (!lista_iter_al_final(iter)) {
        lista_iter_borrar(iter);
    }

    lista_iter_destruir(iter);
}


    // lista_iter_insertar(iter,&vect[0]);
    // print_test("Puedo insertar con el iterador recien creado en una lista vacia, inserto el 0",*(int*)lista_iter_ver_actual(iter) == vect[0]);
    // lista_iter_borrar(iter);
    // print_test("Puedo borrarlo con el iterador del borrar y la lista queda nuevamente vacia",lista_esta_vacia(lista3));
    //lista_iter_insertar(iter,&vect[1]);

    // lista_iter_insertar(iter,&vect[2]);
    // lista_iter_insertar(iter,&vect[3]);
 
    // printf("Pri: %d   \n",*(int*)lista_iter_ver_actual(iter));
    // printf("ult: %d  \n",*(int*)lista_ver_ultimo(lista3));
    // printf("Pri: %d \n",*(int*)lista_ver_primero(lista3));
        //printf("Pri: %d \t Ulti: %d  \n",*(int*)lista_ver_primero(lista3), *(int*)lista_ver_ultimo(lista3));
    //print_test("Puedo usar iterador insertar para agregar elementos en la lista vacia\n Agrego primero el 0 luego el 1, primero debe ser 1 y segundo el 0",
                                                                  //  *(int*)lista_ver_primero(lista3) == 1 && *(int*)lista_ver_ultimo(lista3) == 0);
    // lista_iter_borrar(iter);
    // printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    // lista_iter_borrar(iter);
    //  printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    //     lista_iter_borrar(iter);
    //  printf("Actual: %d   \n",*(int*)lista_iter_ver_actual(iter));
    //  lista_iter_borrar(iter);



    // for(int i = 0; i< tam_int; i++){
    //     lista_insertar_ultimo(lista3,int_array + i);
    // }
    // imprimir_iter_externo(lista3);

    // printf("Caso borde, el iterador inserta un elemento al principio de la lista\n");
    // lista_iter_t *iter_lista = lista_iter_crear(lista3);
    // int *elemento = lista_iter_ver_actual(iter_lista);
    // printf("%d \n", *elemento);
    // if((*elemento % 2) == 0){
    //     lista_iter_insertar(iter_lista,(int*)elemento);
    //     printf("Sali post\n");
    // }
    //  lista_iter_destruir(iter_lista);
    // imprimir_iter_externo(lista3);




