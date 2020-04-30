#ifndef __LIST_H
#define __LIST_H

typedef enum
{
  Failure,
  Success
} Status;

typedef struct node
{
  int value;
  struct node *next;
} Node;

typedef Node *Node_ptr;

typedef struct
{
  Node *head;
  Node *last;
  int count;
} List;

typedef List *List_ptr;

List_ptr create(void);

Status add_to_end(List_ptr, int value);
Status add_to_start(List_ptr, int value);
Status insert(List_ptr, int value, int position);
Status add_unique(List_ptr, int value);

void display(List_ptr);

Status remove_from_start(List_ptr);
Status remove_from_end(List_ptr);
Status remove(List_ptr, int position);

Status remove_first_occurrence(List_ptr, int value);
Status remove_all_occurrences(List_ptr, int value);

Status clear(List_ptr); // Removes all elements in the list

void destroy(List_ptr); // Frees the elements and the list structure from memory

#endif