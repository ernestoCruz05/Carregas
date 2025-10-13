#include "input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Van *input_van_details(void) {
  printf("=== Van Configuration ===\n");
  
  float length = input_float("Enter van length: ", 0.1f, 20.0f);
  float width = input_float("Enter van width: ", 0.1f, 5.0f);
  float height = input_float("Enter van height: ", 0.1f, 5.0f);
  
  printf("\n=== Wheel Arch Configuration ===\n");
  Arch wheels;
  wheels.start = input_float("Wheel arch start position: ", 0.0f, length);
  wheels.end = input_float("Wheel arch end position: ", wheels.start, length);
  wheels.width = input_float("Wheel arch width: ", 0.0f, width);
  wheels.inner_clearance = input_float("Wheel arch inner clearance: ", 0.0f, height);
  
  Van *van = create_van(length, width, height, wheels);
  
  if (van != NULL) {
    printf("\nVan created successfully!\n");
    print_van(van);
  }
  
  return van;
}

Cabinet *input_cabinet_details(void) {
  printf("=== Cabinet Details ===\n");
  
  char name[64];
  input_string("Cabinet name: ", name, sizeof(name));
  
  float height = input_float("Enter cabinet height: ", 0.1f, 10.0f);
  float width = input_float("Enter cabinet width: ", 0.1f, 10.0f);
  float length = input_float("Enter cabinet length: ", 0.1f, 10.0f);
  
  bool is_fragile = input_yes_no("Is this cabinet fragile? (y/n): ");
  
  Cabinet *cabinet = create_cabinet(height, width, length, is_fragile, name);
  
  if (cabinet != NULL) {
    printf("\nCabinet created successfully!\n");
    print_cabinet(cabinet);
  }
  
  return cabinet;
}

void input_cabinet_list(LoadPlan *plan) {
  if (plan == NULL) {
    printf("Invalid load plan\n");
    return;
  }
  
  printf("=== Adding Cabinets to Load Plan ===\n");
  
  while (1) {
    Cabinet *cabinet = input_cabinet_details();
    if (cabinet == NULL) {
      printf("Failed to create cabinet\n");
      continue;
    }
    
    if (add_cabinet_to_plan(plan, cabinet) != 0) {
      printf("Failed to add cabinet to plan\n");
      destroy_cabinet(cabinet);
      continue;
    }
    
    if (!input_yes_no("Add another cabinet? (y/n): ")) {
      break;
    }
    printf("\n");
  }
}

float input_float(const char *prompt, float min_val, float max_val) {
  float value;
  char buffer[100];
  
  while (1) {
    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Error reading input. Please try again.\n");
      continue;
    }
    
    char *endptr;
    value = strtof(buffer, &endptr);
    
    if (endptr == buffer || *endptr != '\n') {
      printf("Invalid input. Please enter a number.\n");
      continue;
    }
    
    if (value < min_val || value > max_val) {
      printf("Value must be between %.2f and %.2f\n", min_val, max_val);
      continue;
    }
    
    break;
  }
  
  return value;
}

int input_int(const char *prompt, int min_val, int max_val) {
  int value;
  char buffer[100];
  
  while (1) {
    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Error reading input. Please try again.\n");
      continue;
    }
    
    char *endptr;
    value = (int)strtol(buffer, &endptr, 10);
    
    if (endptr == buffer || *endptr != '\n') {
      printf("Invalid input. Please enter an integer.\n");
      continue;
    }
    
    if (value < min_val || value > max_val) {
      printf("Value must be between %d and %d\n", min_val, max_val);
      continue;
    }
    
    break;
  }
  
  return value;
}

int input_yes_no(const char *prompt) {
  char buffer[10];
  
  while (1) {
    printf("%s", prompt);
    
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
      printf("Error reading input. Please try again.\n");
      continue;
    }
    
    if (buffer[0] == 'y' || buffer[0] == 'Y') {
      return 1;
    } else if (buffer[0] == 'n' || buffer[0] == 'N') {
      return 0;
    } else {
      printf("Please enter 'y' for yes or 'n' for no.\n");
    }
  }
}

void input_string(const char *prompt, char *buffer, int max_length) {
  while (1) {
    printf("%s", prompt);
    
    if (fgets(buffer, max_length, stdin) == NULL) {
      printf("Error reading input. Please try again.\n");
      continue;
    }
    
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
      buffer[len - 1] = '\0';
    }
    
    if (strlen(buffer) == 0) {
      printf("Please enter a non-empty string.\n");
      continue;
    }
    
    break;
  }
}

void show_main_menu(void) {
  printf("\n=== Cabinet Loader Tool ===\n");
  printf("1. Create new van profile\n");
  printf("2. Add cabinets to load\n");
  printf("3. View current load plan\n");
  printf("4. Save load plan to file\n");
  printf("5. Load plan from file\n");
  printf("6. Auto-generate load plan\n");
  printf("7. Exit\n");
  printf("========================\n");
}

int get_menu_choice(int min_choice, int max_choice) {
  return input_int("Choose an option: ", min_choice, max_choice);
}