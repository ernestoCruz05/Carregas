#ifndef PACKING_H
#define PACKING_H

#include "../core/loader.h"

// Packing algorithm types
typedef enum {
  PACK_BOTTOM_UP,    // Start from bottom, respect fragile items
  PACK_FIRST_FIT,    // First available space
  PACK_BEST_FIT,     // Best space utilization
  PACK_LARGEST_FIRST // Pack largest items first
} PackingStrategy;

// Main packing functions
int auto_pack_cabinets(LoadPlan *plan, PackingStrategy strategy);
int pack_cabinet_at_position(LoadPlan *plan, int cabinet_index, float x, float y, float z);

// Utility functions for packing
int check_space_available(const LoadPlan *plan, float x, float y, float z, 
                         float width, float height, float length);
int check_collision(const LoadPlan *plan, float x, float y, float z,
                   float width, float height, float length);
float calculate_packing_efficiency(const LoadPlan *plan);

// Sorting functions for different strategies
void sort_cabinets_by_volume(CabinetList *list, int descending);
void sort_cabinets_by_fragility(CabinetList *list);

#endif // !PACKING_H
