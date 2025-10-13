#ifndef FILE_IO_H
#define FILE_IO_H

#include "../core/loader.h"

// File I/O functions for saving and loading plans
int save_loadplan_to_file(const char *filename, const LoadPlan *plan);
LoadPlan *load_loadplan_from_file(const char *filename);

#endif // !FILE_IO_H
