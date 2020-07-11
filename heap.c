#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"

#define TAM 7

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
	if(!heap->datos) return NULL;

	heap->capacidad = TAM;
	heap->cantidad = 0;
	heap->cmp = cmp;
	return heap;
}

size_t calculo_maximo(void *arreglo[], cmp_func_t cmp, size_t padre, size_t izq, size_t der){
	size_t max;
	max = cmp(arreglo[izq], arreglo[der]) > 0 ? izq : der;
	return cmp(arreglo[max], arreglo[padre]) > 0 ? max : padre;
}

void downheap(void *arreglo[], size_t tam, size_t padre, cmp_func_t cmp){
	if (padre >= tam) return;
	size_t izq = 2 * padre + 1;
	size_t der = 2 * padre + 2;
	size_t max = calculo_maximo(arreglo, cmp, padre, izq, der);
	if(max != padre){
		swap(arreglo, max, padre);
		downheap(arreglo, tam, max, cmp);
	}
}

void** heapify(void *arreglo[], size_t n, cmp_func_t cmp){
	void** datos = malloc(sizeof(void*)*n);
	if(!datos) return NULL;

	for(size_t i = 0; i < n; i++)
		datos[i] = arreglo[i];

	downheap(datos, n, n-1, cmp);

	return datos;
}

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if(!heap) return NULL;
	
	heap->datos = heapify(arreglo, n, cmp);
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
