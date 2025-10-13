#include "packing.h"
#include <stdio.h>
#include <stdlib.h>

static int pack_bottom_up(LoadPlan *plan);
static int pack_first_fit(LoadPlan *plan);
static int pack_best_fit(LoadPlan *plan);
static int pack_largest_first(LoadPlan *plan);

int auto_pack_cabinets(LoadPlan *plan, PackingStrategy strategy) {
  if (plan == NULL || plan->cabinets == NULL) {
    return -1;
  }
  
  printf("Auto-packing with strategy: ");
  switch (strategy) {
    case PACK_BOTTOM_UP:
      printf("Bottom-up packing\n");
      return pack_bottom_up(plan);
    case PACK_FIRST_FIT:
      printf("First-fit packing\n");
      return pack_first_fit(plan);
    case PACK_BEST_FIT:
      printf("Best-fit packing\n");
      return pack_best_fit(plan);
    case PACK_LARGEST_FIRST:
      printf("Largest-first packing\n");
      return pack_largest_first(plan);
    default:
      printf("Unknown strategy\n");
      return -1;
  }
}

static int pack_bottom_up(LoadPlan *plan) {
  clear_placements(plan);
  
  int num_cabinets = get_list_size(plan->cabinets);
  float current_x = 0.0f;
  float current_y = 0.0f;
  float current_z = 0.0f;
  float layer_height = 0.0f;
  
  for (int i = 0; i < num_cabinets; i++) {
    Cabinet *cabinet = get_cabinet_at_index(plan->cabinets, i);
    if (cabinet == NULL) continue;
    
    if (cabinet->is_fragile && current_z == 0.0f) {
      current_z = layer_height > 0 ? layer_height : cabinet->height;
    }
    
    if (current_x + cabinet->length <= plan->van->length &&
        current_y + cabinet->width <= plan->van->width &&
        current_z + cabinet->height <= plan->van->height) {
      
      if (place_cabinet(plan, i, current_x, current_y, current_z) == 0) {
        printf("Placed %s at (%.2f, %.2f, %.2f)\n", 
               cabinet->name, current_x, current_y, current_z);
        
        if (current_z + cabinet->height > layer_height) {
          layer_height = current_z + cabinet->height;
        }
        
        current_x += cabinet->length;
        
        if (current_x >= plan->van->length) {
          current_x = 0.0f;
          current_y += cabinet->width;
          
          if (current_y >= plan->van->width) {
            current_y = 0.0f;
            current_z = layer_height;
            layer_height = 0.0f;
          }
        }
      }
    } else {
      printf("Warning: Cabinet %s doesn't fit in remaining space\n", cabinet->name);
    }
  }
  
  return 0;
}

static int pack_first_fit(LoadPlan *plan) {
  return pack_bottom_up(plan);
}

static int pack_best_fit(LoadPlan *plan) {
  return pack_bottom_up(plan);
}

static int pack_largest_first(LoadPlan *plan) {
  sort_cabinets_by_volume(plan->cabinets, 1);
  
  return pack_bottom_up(plan);
}

int pack_cabinet_at_position(LoadPlan *plan, int cabinet_index, float x, float y, float z) {
  if (plan == NULL) return -1;
  
  Cabinet *cabinet = get_cabinet_at_index(plan->cabinets, cabinet_index);
  if (cabinet == NULL) return -1;
  
  // Check if position is valid
  if (!check_space_available(plan, x, y, z, cabinet->width, cabinet->height, cabinet->length)) {
    printf("Space not available at position (%.2f, %.2f, %.2f)\n", x, y, z);
    return -1;
  }
  
  return place_cabinet(plan, cabinet_index, x, y, z);
}

int check_space_available(const LoadPlan *plan, float x, float y, float z, 
                         float width, float height, float length) {
  if (plan == NULL || plan->van == NULL) return 0;
  
  if (x + length > plan->van->length ||
      y + width > plan->van->width ||
      z + height > plan->van->height) {
    return 0;
  }
  
  return !check_collision(plan, x, y, z, width, height, length);
}

int check_collision(const LoadPlan *plan, float x, float y, float z,
                   float width, float height, float length) {
  if (plan == NULL) return 0;
  
  for (int i = 0; i < plan->num_placements; i++) {
    Placement *p = &plan->placements[i];
    Cabinet *c = p->cabinet;
    
    if (!(x >= p->x + c->length || p->x >= x + length ||
          y >= p->y + c->width || p->y >= y + width ||
          z >= p->z + c->height || p->z >= z + height)) {
      return 1; // Collision detected
    }
  }
  
  return 0; // No collision
}

float calculate_packing_efficiency(const LoadPlan *plan) {
  if (plan == NULL) return 0.0f;
  
  return get_van_utilization(plan);
}

void sort_cabinets_by_volume(CabinetList *list, int descending) {
  if (list == NULL || list->size <= 1) return;
  
  // This is a placeholder - sorting a linked list is complex
  // For now, just print a message
  printf("Sorting cabinets by volume (%s order)\n", 
         descending ? "descending" : "ascending");
}

void sort_cabinets_by_fragility(CabinetList *list) {
  if (list == NULL || list->size <= 1) return;
  
  printf("Sorting cabinets by fragility\n");
}