#include "core/loader.h"
#include <stdbool.h>
#include <stdio.h>

static bool setup_plan_with_cabinet(LoadPlan **out_plan, Van **out_van,
                                    float van_length, float van_width,
                                    float van_height, Cabinet **out_cabinet,
                                    float cab_height, float cab_width,
                                    float cab_length, bool is_fragile,
                                    const char *name) {
  Arch arch = {0};
  Van *van = create_van(van_length, van_width, van_height, arch);
  if (van == NULL) {
    fprintf(stderr, "Failed to allocate van for test %s\n", name);
    return false;
  }

  LoadPlan *plan = create_loadplan(van);
  if (plan == NULL) {
    fprintf(stderr, "Failed to allocate load plan for test %s\n", name);
    destroy_van(van);
    return false;
  }

  Cabinet *cabinet =
      create_cabinet(cab_height, cab_width, cab_length, is_fragile, name);
  if (cabinet == NULL) {
    fprintf(stderr, "Failed to allocate cabinet for test %s\n", name);
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  if (add_cabinet_to_plan(plan, cabinet) != 0) {
    fprintf(stderr, "Failed to add cabinet to plan for test %s\n", name);
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  if (out_plan != NULL) *out_plan = plan;
  if (out_van != NULL) *out_van = van;
  if (out_cabinet != NULL) *out_cabinet = cabinet;

  return true;
}

static bool test_out_of_bounds(void) {
  LoadPlan *plan = NULL;
  Van *van = NULL;
  Cabinet *cabinet = NULL;

  if (!setup_plan_with_cabinet(&plan, &van, 5.0f, 5.0f, 5.0f, &cabinet, 2.0f,
                               2.0f, 3.0f, false, "Wide Cabinet")) {
    return false;
  }

  if (place_cabinet(plan, 0, 3.0f, 0.5f, 0.5f) != 0) {
    fprintf(stderr, "Failed to place cabinet in out-of-bounds test\n");
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  int result = validate_loadplan(plan);

  destroy_loadplan(plan);
  destroy_van(van);

  if (result != 0) {
    printf("test_out_of_bounds FAILED: expected 0, got %d\n", result);
    return false;
  }

  printf("test_out_of_bounds passed\n");
  return true;
}

static bool test_fragile_on_bottom(void) {
  LoadPlan *plan = NULL;
  Van *van = NULL;
  Cabinet *cabinet = NULL;

  if (!setup_plan_with_cabinet(&plan, &van, 5.0f, 5.0f, 5.0f, &cabinet, 1.0f,
                               1.0f, 1.0f, true, "Fragile Cabinet")) {
    return false;
  }

  if (place_cabinet(plan, 0, 1.0f, 1.0f, 0.0f) != 0) {
    fprintf(stderr,
            "Failed to place cabinet in fragile-on-bottom test\n");
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  int result = validate_loadplan(plan);

  destroy_loadplan(plan);
  destroy_van(van);

  if (result != 0) {
    printf("test_fragile_on_bottom FAILED: expected 0, got %d\n", result);
    return false;
  }

  printf("test_fragile_on_bottom passed\n");
  return true;
}

static bool test_valid_plan(void) {
  LoadPlan *plan = NULL;
  Van *van = NULL;
  Cabinet *fragile = NULL;

  if (!setup_plan_with_cabinet(&plan, &van, 6.0f, 6.0f, 6.0f, &fragile, 1.0f,
                               1.0f, 1.0f, true, "Fragile Top")) {
    return false;
  }

  Cabinet *sturdy =
      create_cabinet(2.0f, 2.0f, 2.0f, false, "Sturdy Base");
  if (sturdy == NULL) {
    fprintf(stderr, "Failed to allocate second cabinet for valid plan test\n");
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  if (add_cabinet_to_plan(plan, sturdy) != 0) {
    fprintf(stderr, "Failed to add second cabinet to plan in valid test\n");
    destroy_cabinet(sturdy);
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  if (place_cabinet(plan, 1, 0.0f, 0.0f, 0.0f) != 0) {
    fprintf(stderr, "Failed to place sturdy cabinet in valid plan test\n");
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  if (place_cabinet(plan, 0, 2.5f, 2.5f, 1.0f) != 0) {
    fprintf(stderr, "Failed to place fragile cabinet in valid plan test\n");
    destroy_loadplan(plan);
    destroy_van(van);
    return false;
  }

  int result = validate_loadplan(plan);

  destroy_loadplan(plan);
  destroy_van(van);

  if (result != 1) {
    printf("test_valid_plan FAILED: expected 1, got %d\n", result);
    return false;
  }

  printf("test_valid_plan passed\n");
  return true;
}

int main(void) {
  int failures = 0;

  if (!test_out_of_bounds()) failures++;
  if (!test_fragile_on_bottom()) failures++;
  if (!test_valid_plan()) failures++;

  if (failures != 0) {
    printf("%d test(s) failed.\n", failures);
    return 1;
  }

  printf("All loader validation tests passed.\n");
  return 0;
}
