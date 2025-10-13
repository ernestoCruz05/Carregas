#include "loader.h"
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_PLACEMENT_CAPACITY 10

LoadPlan *create_loadplan(Van *van) {
  if (van == NULL) {
    fprintf(stderr, "Cannot create loadplan with NULL van\n");
    return NULL;
  }
  
  LoadPlan *plan = (LoadPlan *)malloc(sizeof(LoadPlan));
  if (plan == NULL) {
    fprintf(stderr, "Failed to create loadplan (malloc error)\n");
    return NULL;
  }
  
  plan->van = van;
  plan->cabinets = create_cabinet_list();
  if (plan->cabinets == NULL) {
    free(plan);
    return NULL;
  }
  
  plan->placements = (Placement *)malloc(sizeof(Placement) * INITIAL_PLACEMENT_CAPACITY);
  if (plan->placements == NULL) {
    destroy_cabinet_list(plan->cabinets);
    free(plan);
    return NULL;
  }
  
  plan->num_placements = 0;
  plan->max_placements = INITIAL_PLACEMENT_CAPACITY;
  
  return plan;
}

void destroy_loadplan(LoadPlan *plan) {
  if (plan == NULL) return;
  
  destroy_cabinet_list(plan->cabinets);
  free(plan->placements);
  free(plan);
}

int add_cabinet_to_plan(LoadPlan *plan, Cabinet *cabinet) {
  if (plan == NULL || cabinet == NULL) return -1;
  
  return add_cabinet_to_list(plan->cabinets, cabinet);
}

int remove_cabinet_from_plan(LoadPlan *plan, int index) {
  if (plan == NULL) return -1;
  
  // Also remove any placement for this cabinet
  // Note: This is a simplified approach - in a full implementation,
  // you'd want to shift placements and update indices
  if (index < plan->num_placements) {
    
    for (int i = index; i < plan->num_placements - 1; i++) {
      plan->placements[i] = plan->placements[i + 1];
    }
    plan->num_placements--;
  }
  
  return remove_cabinet_from_list(plan->cabinets, index);
}

int place_cabinet(LoadPlan *plan, int cabinet_index, float x, float y, float z) {
  if (plan == NULL || cabinet_index < 0 || cabinet_index >= get_list_size(plan->cabinets)) {
    return -1;
  }
  
  if (plan->num_placements >= plan->max_placements) {
    plan->max_placements *= 2;
    Placement *new_placements = (Placement *)realloc(plan->placements, 
                                                   sizeof(Placement) * plan->max_placements);
    if (new_placements == NULL) {
      fprintf(stderr, "Failed to resize placements array\n");
      return -1;
    }
    plan->placements = new_placements;
  }
  
  Cabinet *cabinet = get_cabinet_at_index(plan->cabinets, cabinet_index);
  if (cabinet == NULL) return -1;
  
  plan->placements[plan->num_placements].x = x;
  plan->placements[plan->num_placements].y = y;
  plan->placements[plan->num_placements].z = z;
  plan->placements[plan->num_placements].cabinet = cabinet;
  plan->num_placements++;
  
  return 0;
}

void clear_placements(LoadPlan *plan) {
  if (plan != NULL) {
    plan->num_placements = 0;
  }
}

void print_loadplan(const LoadPlan *plan) {
  if (plan == NULL) {
    printf("LoadPlan is NULL\n");
    return;
  }
  
  printf("=== LOAD PLAN ===\n");
  printf("Van details:\n");
  print_van(plan->van);
  printf("\n");
  
  printf("Cabinets to load:\n");
  print_cabinet_list(plan->cabinets);
  printf("\n");
  
  printf("Placement plan:\n");
  for (int i = 0; i < plan->num_placements; i++) {
    printf("[%d] %s at position (%.2f, %.2f, %.2f)\n", 
           i, 
           plan->placements[i].cabinet->name,
           plan->placements[i].x,
           plan->placements[i].y,
           plan->placements[i].z);
  }
  
  printf("\nUtilization: %.1f%%\n", get_van_utilization(plan));
}

float get_total_loaded_volume(const LoadPlan *plan) {
  if (plan == NULL) return 0.0f;
  
  float total = 0.0f;
  for (int i = 0; i < plan->num_placements; i++) {
    total += cabinet_volume(plan->placements[i].cabinet);
  }
  
  return total;
}

float get_van_utilization(const LoadPlan *plan) {
  if (plan == NULL || plan->van == NULL) return 0.0f;
  
  float van_vol = van_volume(plan->van);
  float loaded_vol = get_total_loaded_volume(plan);
  
  if (van_vol == 0.0f) return 0.0f;
  
  return (loaded_vol / van_vol) * 100.0f;
}

int validate_loadplan(const LoadPlan *plan) {
  if (plan == NULL) return 0;
  
  for (int i = 0; i < plan->num_placements; i++) {
    Placement *p = &plan->placements[i];
    Cabinet *c = p->cabinet;
    
    if (p->x + c->length > plan->van->length ||
        p->y + c->width > plan->van->width ||
        p->z + c->height > plan->van->height) {
      printf("Warning: Cabinet %s extends beyond van boundaries\n", c->name);
      return 0;
    }
    
    if (c->is_fragile && p->z == 0.0f) {
      printf("Warning: Fragile cabinet %s is placed at the bottom\n", c->name);
      return 0;
    }
  }
  
  return 1; 
}
