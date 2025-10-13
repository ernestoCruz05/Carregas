#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

// Dynamic array implementation for future use
// Placeholder for when more advanced data structures are needed

typedef struct {
  void **data;
  size_t size;
  size_t capacity;
} Vector;

// Vector operations (to be implemented later)
Vector *vector_create(size_t initial_capacity);
void vector_destroy(Vector *vec);
int vector_push(Vector *vec, void *item);
void *vector_pop(Vector *vec);
void *vector_get(const Vector *vec, size_t index);

#endif // !VECTOR_H
