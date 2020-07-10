#include <stddef.h>
#include "heap.h"

struct heap{
	void** datos;
	size_t capacidad;
	size_t cantidad;
	cmp_func_t cmp;
};