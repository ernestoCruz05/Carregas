#include "van.h"
#include <stdio.h>
#include <stdlib.h>

Van *create_van(float length, float width, float height, Arch wheels) {
  Van *new_van = (Van *)malloc(sizeof(Van));

  if (new_van == NULL) {
    fprintf(stderr, "Failed to create a new van (malloc error)\n");
    return NULL;
  }

  new_van->length = length;
  new_van->width = width;
  new_van->height = height;
  new_van->wheels = wheels;

  return new_van;
}

void destroy_van(Van *van) {
  if (van != NULL) {
    free(van);
  }
}

void print_van(Van *van) {
  if (van == NULL) {
    printf("Van is NULL\n");
    return;
  }
  
  printf("Van Information:\n");
  printf(" == Dimensions ==\n");
  printf("Length: %.2f\n", van->length);
  printf("Width:  %.2f\n", van->width);
  printf("Height: %.2f\n", van->height);
  printf(" == Wheel Arch ==\n");
  printf("Start:  %.2f\n", van->wheels.start);
  printf("End:    %.2f\n", van->wheels.end);
  printf("Width:  %.2f\n", van->wheels.width);
  printf("Inner clearance: %.2f\n", van->wheels.inner_clearance);
  printf("Total volume: %.2f cubic units\n", van_volume(van));
}

float van_volume(const Van *van) {
  if (van == NULL) return 0.0f;
  return van->length * van->width * van->height;
}
