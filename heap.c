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

