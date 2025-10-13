#ifndef CABINET_H
#define CABINET_H

#include <stdbool.h>

typedef struct {
  float height;
  float width;
  float length;
  bool is_fragile;  // fragile cabinets should not be placed at the bottom
  char name[64];    // optional name/identifier for the cabinet
} Cabinet;

Cabinet *create_cabinet(float height, float width, float length, bool is_fragile, const char *name);

void destroy_cabinet(Cabinet *cabinet);

void print_cabinet(const Cabinet *cabinet);

float cabinet_volume(const Cabinet *cabinet);

#endif // !CABINET_H
