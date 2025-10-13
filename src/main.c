#include <stdio.h>
#include <stdlib.h>

#include "core/van.h"
#include "core/cabinet.h"
#include "core/loader.h"
#include "io/input.h"
#include "algorithms/packing.h"

int main(void) {

  Van *van = NULL;
  LoadPlan *plan = NULL;
  
  while (1) {
    show_main_menu();
    int choice = get_menu_choice(1, 7);
    
    switch (choice) {
      case 1: 
        if (van != NULL) {
          destroy_van(van);
        }
        if (plan != NULL) {
          destroy_loadplan(plan);
          plan = NULL;
        }
        
        van = input_van_details();
        if (van != NULL) {
          plan = create_loadplan(van);
          if (plan == NULL) {
            printf("Failed to create load plan\n");
            destroy_van(van);
            van = NULL;
          }
        }
        break;
        
      case 2: 
        if (plan == NULL) {
          printf("Please create a van profile first (option 1)\n");
          break;
        }
        input_cabinet_list(plan);
        break;
        
      case 3: 
        if (plan == NULL) {
          printf("No load plan created yet. Please create a van profile first.\n");
        } else {
          print_loadplan(plan);
        }
        break;
        
      case 4: 
        printf("Save functionality not implemented yet\n");
        break;
        
      case 5: 
        printf("Load functionality not implemented yet\n");
        break;
        
      case 6: 
        if (plan == NULL) {
          printf("No load plan created yet. Please create a van profile first.\n");
          break;
        }
        
        if (get_list_size(plan->cabinets) == 0) {
          printf("No cabinets added yet. Please add cabinets first (option 2)\n");
          break;
        }
        
        printf("Choose packing strategy:\n");
        printf("1. Bottom-up (fragile items on top)\n");
        printf("2. First-fit\n");
        printf("3. Best-fit\n");
        printf("4. Largest-first\n");
        
        int strategy_choice = get_menu_choice(1, 4);
        PackingStrategy strategy = (PackingStrategy)(strategy_choice - 1);
        
        if (auto_pack_cabinets(plan, strategy) == 0) {
          printf("\nPacking completed! Here's your load plan:\n");
          print_loadplan(plan);
          
          if (validate_loadplan(plan)) {
            printf("\n Load plan is valid!\n");
          } else {
            printf("\n Load plan has warnings. Please review.\n");
          }
        } else {
          printf("Failed to generate packing plan\n");
        }
        break;
        
      case 7: 
        if (plan != NULL) {
          destroy_loadplan(plan);
        }
        if (van != NULL) {
          destroy_van(van);
        }
        return 0;
        
      default:
        printf("Invalid choice\n");
        break;
    }
    
    printf("\nPress Enter to continue...");
    getchar();
  }
  
  return 0;
}