#include "heap.h"
#include "testing.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>



// funcion de comparacion auxiliar
int cmp_enteros(const void *a, const void *b) {
    int *x = (int*) a;
    int *y = (int*) b;
    
    if(*x == *y) 
        return 0;
    return (*x > *y) ? 1 : -1;
}
//cmp_func_t cmp = cmp_enteros;


void heap_prueba_crear() {
    printf("------inicio_prueba_heap_crear");
    heap_t *heap = heap_crear(cmp_enteros);
    
    print_test("se creó un heap", heap != NULL);
    print_test("el heap esta inicialmente vacio", heap_esta_vacio(heap));
    print_test("la cantidad en el heap es cero", heap_cantidad(heap) == 0);
    print_test("ver maximo en heap vacio devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("desencolar en heap vacio devuelve NULL", heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
    print_test("se destruyó el heap", true);
}



void pruebas_heap_alumno(void){
    heap_prueba_crear();
}