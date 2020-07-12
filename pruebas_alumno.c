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
    printf("------inicio prueba heap crear\n");
    heap_t *heap = heap_crear(cmp_enteros);
    
    print_test("se creó un heap", heap != NULL);
    print_test("el heap esta inicialmente vacio", heap_esta_vacio(heap));
    print_test("la cantidad en el heap es cero", heap_cantidad(heap) == 0);
    print_test("ver maximo en heap vacio devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("desencolar en heap vacio devuelve NULL", heap_desencolar(heap) == NULL);
    heap_destruir(heap, NULL);
    print_test("se destruyó el heap", true);
}

void heap_prueba_crear_arr(){
    printf("------inicio prueba heap crear arr\n");
    int a[] = {6,4,7,9,1,2,8,3,5,0};
    void* arr[10];

    for(size_t i = 0; i<10; i++)
        arr[i] = &a[i];

    heap_t* heap = heap_crear_arr(arr, 10, cmp_enteros);

    print_test("se creó un heap", heap != NULL);
    print_test("la cantidad en el heap es diez", heap_cantidad(heap) == 10);
    print_test("ver maximo en heap devuelve nueve", *(int*)heap_ver_max(heap) == 9);
    print_test("desencolar en heap devuelve nueve", *(int*)heap_desencolar(heap) == 9);
    print_test("la cantidad en heap es nueve", heap_cantidad(heap) == 9);
    heap_destruir(heap, NULL);
    print_test("se destruyó el heap", true);
}

/*void heap_prueba_destruir_NULL(){
    printf("------inicio prueba heap destruir NULL\n");

    int a[] = {6,4,7,9,1,2,8,3,5,0};
    void* arr[10];

    for(size_t i = 0; i<10; i++)
        arr[i] = &a[i];
    
    heap_t *heap = heap_crear(cmp_enteros);

    print_test("se creó un heap", heap != NULL);
    print_test("el heap esta inicialmente vacio", heap_esta_vacio(heap));
    print_test("la cantidad en el heap es cero", heap_cantidad(heap) == 0);

}*/

/*
void heap_prueba_destruir_free(){
    printf("------inicio prueba heap destruir FREE\n");
}*/


void pruebas_heap_alumno(void){
    heap_prueba_crear();
    heap_prueba_crear_arr();
    //heap_prueba_destruir_NULL();
    //heap_prueba_destruir_free();
}