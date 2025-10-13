#include "cabinet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Cabinet *create_cabinet(float height, float width, float length, bool is_fragile, const char *name) {
  Cabinet *new_cabinet = (Cabinet *)malloc(sizeof(Cabinet));

  if (new_cabinet == NULL) {
    fprintf(stderr, "Failed to create a new cabinet (malloc error)\n");
    return NULL;
  }

  new_cabinet->height = height;
  new_cabinet->width = width;
  new_cabinet->length = length;
  new_cabinet->is_fragile = is_fragile;
  
  // Copy name or set default
  if (name != NULL) {
    strncpy(new_cabinet->name, name, sizeof(new_cabinet->name) - 1);
    new_cabinet->name[sizeof(new_cabinet->name) - 1] = '\0';
  } else {
    strcpy(new_cabinet->name, "Unnamed Cabinet");
  }

  return new_cabinet;
}

void destroy_cabinet(Cabinet *cabinet) {
  if (cabinet != NULL) {
    free(cabinet);
  }
}

void print_cabinet(const Cabinet *cabinet) {
  if (cabinet == NULL) {
    printf("Cabinet is NULL\n");
    return;
  }
  
  printf("Cabinet: %s\n", cabinet->name);
  printf("  Dimensions: %.2f x %.2f x %.2f (H x W x L)\n", 
         cabinet->height, cabinet->width, cabinet->length);
  printf("  Volume: %.2f cubic units\n", cabinet_volume(cabinet));
  printf("  Fragile: %s\n", cabinet->is_fragile ? "Yes" : "No");
}

float cabinet_volume(const Cabinet *cabinet) {
  if (cabinet == NULL) return 0.0f;
  return cabinet->height * cabinet->width * cabinet->length;
}
