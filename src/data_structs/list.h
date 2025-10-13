#ifndef LIST_H
#define LIST_H

#include "../core/cabinet.h"

typedef struct ListNode {
  Cabinet *cabinet;
  struct ListNode *next;
} ListNode;

typedef struct {
  ListNode *head;
  ListNode *tail;
  int size;
} CabinetList;

// List operations
CabinetList *create_cabinet_list(void);
void destroy_cabinet_list(CabinetList *list);

// Add/remove operations
int add_cabinet_to_list(CabinetList *list, Cabinet *cabinet);
int remove_cabinet_from_list(CabinetList *list, int index);
Cabinet *get_cabinet_at_index(const CabinetList *list, int index);

// Utility functions
int get_list_size(const CabinetList *list);
void print_cabinet_list(const CabinetList *list);
float total_volume_in_list(const CabinetList *list);
void clear_cabinet_list(CabinetList *list);

#endif // !LIST_H