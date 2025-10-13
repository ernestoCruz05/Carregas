#include "list.h"
#include <stdio.h>
#include <stdlib.h>

CabinetList *create_cabinet_list(void) {
  CabinetList *list = (CabinetList *)malloc(sizeof(CabinetList));
  
  if (list == NULL) {
    fprintf(stderr, "Failed to create cabinet list (malloc error)\n");
    return NULL;
  }
  
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  
  return list;
}

void destroy_cabinet_list(CabinetList *list) {
  if (list == NULL) return;
  
  clear_cabinet_list(list);
  free(list);
}

int add_cabinet_to_list(CabinetList *list, Cabinet *cabinet) {
  if (list == NULL || cabinet == NULL) return -1;
  
  ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));
  if (new_node == NULL) {
    fprintf(stderr, "Failed to add cabinet to list (malloc error)\n");
    return -1;
  }
  
  new_node->cabinet = cabinet;
  new_node->next = NULL;
  
  if (list->head == NULL) {
    list->head = new_node;
    list->tail = new_node;
  } else {
    list->tail->next = new_node;
    list->tail = new_node;
  }
  
  list->size++;
  return 0;
}

int remove_cabinet_from_list(CabinetList *list, int index) {
  if (list == NULL || index < 0 || index >= list->size) return -1;
  
  ListNode *current = list->head;
  ListNode *previous = NULL;
  
  for (int i = 0; i < index; i++) {
    previous = current;
    current = current->next;
  }
  
  if (previous == NULL) {
    list->head = current->next;
    if (list->head == NULL) {
      list->tail = NULL;
    }
  } else {
    previous->next = current->next;
    if (current == list->tail) {
      list->tail = previous;
    }
  }
  
  destroy_cabinet(current->cabinet);
  free(current);
  list->size--;
  
  return 0;
}

Cabinet *get_cabinet_at_index(const CabinetList *list, int index) {
  if (list == NULL || index < 0 || index >= list->size) return NULL;
  
  ListNode *current = list->head;
  for (int i = 0; i < index; i++) {
    current = current->next;
  }
  
  return current->cabinet;
}

int get_list_size(const CabinetList *list) {
  return (list != NULL) ? list->size : 0;
}

void print_cabinet_list(const CabinetList *list) {
  if (list == NULL) {
    printf("Cabinet list is NULL\n");
    return;
  }
  
  printf("Cabinet List (%d items):\n", list->size);
  printf("========================\n");
  
  ListNode *current = list->head;
  int index = 0;
  
  while (current != NULL) {
    printf("[%d] ", index);
    print_cabinet(current->cabinet);
    printf("\n");
    current = current->next;
    index++;
  }
  
  printf("Total volume: %.2f cubic units\n", total_volume_in_list(list));
}

float total_volume_in_list(const CabinetList *list) {
  if (list == NULL) return 0.0f;
  
  float total = 0.0f;
  ListNode *current = list->head;
  
  while (current != NULL) {
    total += cabinet_volume(current->cabinet);
    current = current->next;
  }
  
  return total;
}

void clear_cabinet_list(CabinetList *list) {
  if (list == NULL) return;
  
  ListNode *current = list->head;
  while (current != NULL) {
    ListNode *next = current->next;
    destroy_cabinet(current->cabinet);
    free(current);
    current = next;
  }
  
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}