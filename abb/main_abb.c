#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void pruebas_abb_alumno(void);

/* ******************************************************************
 *                        PROGRAMA PRINCIPAL
 * *****************************************************************/

int main(int argc, char *argv[])
{
    time_t t;

    srand((unsigned) time(&t));
    printf("~~~ PRUEBAS ALUMNO ~~~\n");
    pruebas_abb_alumno();

    return failure_count() > 0;
}
