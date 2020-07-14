#include "heap.h"
#include "testing.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define LARGO 1000


int cmp_enteros(const void *a, const void *b) {
    int *x = (int*) a;
    int *y = (int*) b;
    
    if(*x == *y) 
        return 0;
    return (*x > *y) ? 1 : -1;
}

// funcion de destruccion auxiliar
void destruir_enteros(void *dato) {
    int *a = (int*)dato;
    free(a);
    return;
}

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

void heap_pruebas_con_un_elemento() {
    printf("\n------inicio prueba heap crear\n");
    heap_t *heap = heap_crear(cmp_enteros);
    int a = 5;

    print_test("ingresando un elemento al heap", heap_encolar(heap, &a));
    print_test("el heap deja de estar vacio", !heap_esta_vacio(heap));
    print_test("la cantidad en el heap es 1", heap_cantidad(heap) == 1);
    print_test("el maximo es el esperado", heap_ver_max(heap) == &a);
    print_test("desencolar devuelve el elemento esperado", heap_desencolar(heap) == &a);
    print_test("el heap vuelve a estar vacio", heap_esta_vacio(heap));
    print_test("la cantidad vuelve a ser cero", heap_cantidad(heap) == 0);
    print_test("desencolar devuelve NULL", !heap_desencolar(heap));
    print_test("el maximo es nulo", heap_ver_max(heap) == NULL);
    heap_destruir(heap, NULL);
}

void pruebas_heap_destruccion_con_funcion() {
    printf("\n------inicio prueba destruir heap con free\n");
    heap_t *heap = heap_crear(cmp_enteros);
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    int *c = malloc(sizeof(int));
    int *d = malloc(sizeof(int));
    *a = 1;
    *b = 2;
    *c = 3;
    *d = 4;
    heap_encolar(heap, a);
    heap_encolar(heap, b);
    heap_encolar(heap, c);
    heap_encolar(heap, d);
    heap_destruir(heap, destruir_enteros);
    print_test("se destruyó el heap con funcion de destruccion", true);
}

void heap_prueba_crear_arr(){
    printf("\n------inicio prueba heap crear arr\n");
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

void heap_prueba_destruir_NULL(){
    printf("\n------inicio prueba heap destruir NULL\n");

    int a = 1;
    heap_t *heap = heap_crear(cmp_enteros);

    print_test("se creó un heap", heap != NULL);
    print_test("el heap esta inicialmente vacio", heap_esta_vacio(heap));
    print_test("la cantidad en el heap es cero", heap_cantidad(heap) == 0);
    print_test("Se inserta un elemento al heap", heap_encolar(heap, &a));
    print_test("la cantidad en el heap es uno", heap_cantidad(heap) == 1);
    heap_destruir(heap, NULL);
    print_test("Se destruyo el heap con NULL", true);
}


void heap_prueba_destruir_free(){
    printf("\n------inicio prueba heap destruir FREE\n");

    int *h = malloc(sizeof(int));
    *h=1;
    heap_t *heap = heap_crear(cmp_enteros);

    print_test("se creó un heap", heap != NULL);
    print_test("el heap esta inicialmente vacio", heap_esta_vacio(heap));
    print_test("la cantidad en el heap es cero", heap_cantidad(heap) == 0);
    print_test("Se inserta un elemento al heap", heap_encolar(heap, h));
    print_test("la cantidad en el heap es uno", heap_cantidad(heap) == 1);
    heap_destruir(heap, free);
    print_test("Se destruyo el heap con NULL", true);
}

void heap_prueba_cantidad(){
    printf("\n------inicio prueba heap cantidad\n");
    int a[] = {6,4,7,9,1,2,8,3,5,0};
    void* arr[10];

    for(size_t i = 0; i<10; i++)
        arr[i] = &a[i];

    heap_t* heap = heap_crear_arr(arr, 10, cmp_enteros);

    print_test("se creó un heap", heap != NULL);
    print_test("la cantidad en el heap es diez", heap_cantidad(heap) == 10);
    print_test("El heap desencola", heap_desencolar(heap));
    print_test("la cantidad en heap es nueve", heap_cantidad(heap) == 9);
    print_test("el heap vuelve a encolar", heap_encolar(heap, &a[7]));
    print_test("la cantidad en el heap es diez", heap_cantidad(heap) == 10);

    while(!heap_esta_vacio(heap))
        heap_desencolar(heap);

    print_test("El heap desencola todos los elementos", !heap_cantidad(heap));
    print_test("El heap está vacío", heap_esta_vacio(heap));

    heap_destruir(heap, NULL);
    print_test("se destruyó el heap", true);
}


static void prueba_heap_volumen(size_t largo, bool debug){
    printf("\n------inicio prueba heap volumen\n");
    heap_t* heap = heap_crear(cmp_enteros);
    int* valores[largo];

    bool ok = true;
    for (size_t i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        *valores[i] = (int)i;
        ok = heap_encolar(heap, valores[i]);
        if (!ok) break;
        //print_test("Encola elem ok", ok);
    }

    if (debug) print_test("Prueba heap almacenar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);

    // Verifica que borre y devuelva los valores correctos 
    for (size_t i = 0; i < largo; i++) {
        ok = heap_desencolar(heap) == valores[largo-1-i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba heap borrar muchos elementos", ok);
    if (debug) print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    // Destruye el heap y crea uno nuevo que sí libera 
    heap_destruir(heap, free);
    heap = heap_crear(cmp_enteros);

    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = heap_encolar(heap, valores[i]);
        if (!ok) break;
    }

    // Destruye el heap - debería liberar los enteros 
    heap_destruir(heap,free);

}

// funcion auxiliar para pruebas heapsort
bool arreglo_esta_ordenado(void **arreglo, size_t cant, cmp_func_t cmp) {
    void *anterior = arreglo[0];
    for(size_t i=0; i<cant; i++) {
        if(cmp(anterior, arreglo[i]) > 0) {
            printf("se rompio en: %zu", i);
            return false;
        }
        anterior = arreglo[i];
    }
    return true;
}


static void prueba_heapsort_volumen(size_t largo){
    printf("\n------inicio prueba heapsort volumen\n");
    int* valores[largo];

    for (size_t i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        *valores[i] = (int)(rand() % largo);
    }

    print_test("el arreglo inicialmente esta desordenado", !arreglo_esta_ordenado((void**)valores, largo, cmp_enteros));
    heap_sort((void**)valores, largo, cmp_enteros);
    print_test("se le aplica heapsort al arreglo", true);
    print_test("el arreglo ahora esta ordenado", arreglo_esta_ordenado((void**)valores, largo, cmp_enteros));

    print_test("Prueba heapsort volumen", true);
    for (size_t i = 0; i < largo; i++)
        free(valores[i]);

}

void pruebas_heap_alumno(void){
    heap_prueba_crear();
    heap_pruebas_con_un_elemento();
    pruebas_heap_destruccion_con_funcion();
    heap_prueba_crear_arr();
    heap_prueba_destruir_NULL();
    heap_prueba_destruir_free();
    heap_prueba_cantidad();
    prueba_heap_volumen(LARGO,true);
    prueba_heapsort_volumen(100);
}