#include "vector.h"

/**************************************
 *   Alumno: Arturo Aguilar López     *
 *   Padrón: 99804                    *
 *   Mail: -aguilarlopez18@gmail.com/ *
 *         -aaguilarl@fi.uba.ar       *
**************************************/


bool vector_vacio(vector_t * vector){
    return vector_largo(vector) == 0;
}

void vector_destruir(vector_t* vector){
    free(vector->datos);
    free(vector);
}

bool vector_obtener(vector_t* vector, size_t pos, int* valor){
    if(vector_vacio(vector))
        return false;
    
    if(pos > vector->tam-1)
        return false;

    *valor = vector->datos[pos];

    return true;
}

bool vector_guardar(vector_t* vector, size_t pos, int valor){
    if(vector_vacio(vector))
        return false;

    if(pos > vector->tam-1)
        return false;

    vector->datos[pos] = valor;
    
    return true;
}

size_t vector_largo(vector_t* vector){
    return vector->tam;
}

vector_t* vector_crear(size_t tam) {
    vector_t* vector = malloc(sizeof(vector_t));

    if (vector == NULL) {
        return NULL;
    }
    vector->datos = malloc(tam * sizeof(int));

    if (tam > 0 && vector->datos == NULL) {
        free(vector);
        return NULL;
    }
    vector->tam = tam;
    return vector;
}

bool vector_redimensionar(vector_t* vector, size_t tam_nuevo) {
    int* datos_nuevo = realloc(vector->datos, tam_nuevo * sizeof(int));

    // Cuando tam_nuevo es 0, es correcto si se devuelve NULL.
    // En toda otra situación significa que falló el realloc.
    if (tam_nuevo > 0 && datos_nuevo == NULL) {
        return false;
    }

    vector->datos = datos_nuevo;
    vector->tam = tam_nuevo;
    return true;
}
