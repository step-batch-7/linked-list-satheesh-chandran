#ifndef __LIST_H
#define __LIST_H

typedef enum
{
  Failure,
  Success
} STATUS;

typedef struct node
{
  int value;
  struct node *next;
} NODE;

typedef NODE* Node_ptr;

typedef struct
{
  NODE *head;
  NODE *last;
  int count;
} LIST;

typedef LIST* List_ptr;

typedef struct {
  Node_ptr prev;
  Node_ptr current;
} Prev_Current_Pair;

List_ptr create_list(void);
Node_ptr create_node(int value);

STATUS add_to_end(List_ptr, int value); // a
STATUS add_to_start(List_ptr, int value); // b
STATUS add_unique(List_ptr, int value); // d
STATUS remove_first_occurrence(List_ptr, int value); // h
STATUS remove_all_occurrences(List_ptr, int value); // i

void display(List_ptr); // l
STATUS remove_from_start(List_ptr); // e
STATUS remove_from_end(List_ptr); // f
STATUS clear_list(List_ptr); // Removes all elements in the list j
void destroy_list(List_ptr); // Frees the elements and the list structure from memory

STATUS remove_at(List_ptr, int position); // g
STATUS insert_at(List_ptr, int value, int position); // c

void decide_actions(List_ptr list, char decider);

#endif