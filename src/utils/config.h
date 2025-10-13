#ifndef CONFIG_H
#define CONFIG_H

// Configuration management for the application

typedef struct {
  // Default van dimensions
  float default_van_length;
  float default_van_width;
  float default_van_height;
  
  // Default settings
  int auto_save_enabled;
  char last_save_directory[256];
  
  // Display preferences
  int show_warnings;
  int metric_units; // 1 for metric, 0 for imperial
} AppConfig;

// Configuration functions
AppConfig *create_default_config(void);
void destroy_config(AppConfig *config);

// File operations
int load_config_from_file(const char *filename, AppConfig *config);
int save_config_to_file(const char *filename, const AppConfig *config);

#endif // !CONFIG_H
