#ifndef VAN_H
#define VAN_H

typedef struct {
  float start;
  float end;
  float width;
  float inner_clearance;
} Arch;

typedef struct {
  float length;
  float width;
  float height;
  Arch wheels;
} Van;

Van *create_van(float length, float width, float height, Arch wheels);

void destroy_van(Van *van);

void print_van(Van *van);

float van_volume(const Van *van);

#endif // !VAN_H
