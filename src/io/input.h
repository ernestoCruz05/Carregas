#ifndef INPUT_H
#define INPUT_H

#include "../core/van.h"
#include "../core/cabinet.h"
#include "../core/loader.h"

// Interactive input functions
Van *input_van_details(void);
Cabinet *input_cabinet_details(void);
void input_cabinet_list(LoadPlan *plan);

// Utility input functions
float input_float(const char *prompt, float min_val, float max_val);
int input_int(const char *prompt, int min_val, int max_val);
int input_yes_no(const char *prompt);
void input_string(const char *prompt, char *buffer, int max_length);

// Menu functions
void show_main_menu(void);
int get_menu_choice(int min_choice, int max_choice);

#endif // !INPUT_H
