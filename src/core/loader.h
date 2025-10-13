#ifndef LOADER_H
#define LOADER_H

#include "van.h"
#include "cabinet.h"
#include "../data_structs/list.h"

typedef struct {
  float x, y, z; 
  Cabinet *cabinet; 
} Placement;

typedef struct {
  Van *van;
  CabinetList *cabinets;
  Placement *placements; 
  int num_placements;
  int max_placements;
} LoadPlan;

// LoadPlan operations
LoadPlan *create_loadplan(Van *van);
void destroy_loadplan(LoadPlan *plan);

// Cabinet management
int add_cabinet_to_plan(LoadPlan *plan, Cabinet *cabinet);
int remove_cabinet_from_plan(LoadPlan *plan, int index);

// Placement operations
int place_cabinet(LoadPlan *plan, int cabinet_index, float x, float y, float z);
void clear_placements(LoadPlan *plan);

// Utility functions
void print_loadplan(const LoadPlan *plan);
float get_total_loaded_volume(const LoadPlan *plan);
float get_van_utilization(const LoadPlan *plan);
int validate_loadplan(const LoadPlan *plan);

#endif // !LOADER_H
