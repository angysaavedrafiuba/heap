#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

#define TAM 7
#define F_RED_MAX 2      //factor de redimension maximo
#define F_RED_MIN 1/2    //factor de redimension minimo
#define F_CAR_MAX 1      //factor de carga maximo
#define F_CAR_MIN 1/4    //factor de carga minimo

struct heap{
	void** datos;
	size_t capacidad;
	size_t cantidad;
	cmp_func_t cmp;
};

void swap (void *arreglo[], size_t x, size_t y) {
	void* aux = arreglo[x];
	arreglo[x] = arreglo[y];
	arreglo[y] = aux;
}

heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;

	heap->datos = malloc(sizeof(void*)*TAM);
	if(!heap->datos) {
		free(heap);
		return NULL;
	}
	heap->capacidad = TAM;
	heap->cantidad = 0;
	heap->cmp = cmp;
	return heap;
}

size_t calculo_maximo(void *arreglo[], size_t tam, cmp_func_t cmp, size_t padre, size_t izq, size_t der){
	if(izq > tam) return padre;
	
	size_t max = izq;
	if(der < tam)
		max = cmp(arreglo[izq], arreglo[der]) > 0 ? izq : der;

	return cmp(arreglo[max], arreglo[padre]) > 0 ? max : padre;
}

void upheap(void **datos, size_t hijo, cmp_func_t cmp) {
    if(hijo == 0) return;
    size_t padre = (hijo - 1) / 2;
	

    if(cmp(datos[hijo], datos[padre]) > 0) { //hijo mayor a padre
        swap(datos, hijo, padre);
        upheap(datos, padre, cmp);
    }
}


void downheap(void **datos, size_t tam, size_t padre, cmp_func_t cmp) {
    size_t hijo_der = (2 * padre) + 2;
    size_t hijo_izq = (2 * padre) + 1;
    size_t pos_maxima = tam-1;

    if(hijo_der > pos_maxima && hijo_izq > pos_maxima) {
        return;
    }

    size_t reemplazo = calculo_maximo(datos, tam, cmp, padre, hijo_izq, hijo_der);
    if(reemplazo != padre) {
        swap(datos, padre, reemplazo);
        downheap(datos, tam, reemplazo, cmp);
    }
    return;
}

void heapify(void *arreglo[], size_t n, cmp_func_t cmp){
	for(size_t i = n/2; i< n; i++)
		downheap(arreglo, n, n-i-1, cmp);
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;

	heap->datos = malloc(sizeof(void*)*n);
	if(!heap->datos) return NULL;

	for(size_t i = 0; i < n; i++)
		heap->datos[i] = arreglo[i];
	
	heapify(heap->datos, n, cmp);
	heap->capacidad = n;
	heap->cantidad = n;
	heap->cmp = cmp;
	return heap;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)){
	if(destruir_elemento)
		for(size_t i = 0; i < heap->cantidad; i++)
			destruir_elemento(heap->datos[i]);

	free(heap->datos);
	free(heap);
}

size_t heap_cantidad(const heap_t *heap){
	return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap){
	return heap->cantidad == 0;
}

bool heap_redimensionar(heap_t* heap, size_t tam_nuevo) {
	if(tam_nuevo <= TAM) {
		return true;
	}
	void** nuevos_datos = realloc(heap->datos, tam_nuevo * sizeof(void*));
	if(!nuevos_datos) {
		return false;
	}
	heap->datos = nuevos_datos;
	heap->capacidad = tam_nuevo;
	return true;
}

float factor_carga(heap_t* heap) {
	return (float)(heap->cantidad) / (float)(heap->capacidad);
}

bool heap_encolar(heap_t *heap, void *elem){
	if(!elem) return false;

	if(factor_carga(heap) >= F_CAR_MAX) {
		size_t tam_nuevo = heap->cantidad * F_RED_MAX;
		bool redim_ok = heap_redimensionar(heap, tam_nuevo);
		if(!redim_ok) {
			return false;
		}
	}

    void **datos = heap->datos;
    size_t posicion = heap->cantidad;
    datos[posicion] = elem;
    heap->cantidad ++;
    upheap(datos, posicion, heap->cmp);
    return true;
}

void *heap_ver_max(const heap_t *heap){
	if (!heap->cantidad)
		return NULL;

	return heap->datos[0];
}

void *heap_desencolar(heap_t *heap){
	if(!heap->cantidad) return NULL;
	size_t cantidad = heap->cantidad;

	swap(heap->datos, 0, heap->cantidad-1);
	void* ret = heap->datos[cantidad-1];
	heap->cantidad--;
	downheap(heap->datos, heap->cantidad, 0, heap->cmp);

	if(factor_carga(heap) <= F_CAR_MIN) {
		size_t tam_nuevo = heap->cantidad * F_RED_MIN;
		heap_redimensionar(heap, tam_nuevo);
	}
	return ret;
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	size_t n = cant; 
	heapify(elementos, n, cmp);

	for(size_t i=0; i<cant; i++) {
		swap(elementos, 0, n-1);
		n--;
		downheap(elementos, n, 0, cmp);
	}
}