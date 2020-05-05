#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void print_status(STATUS result)
{
  if (result == Success)
  {
    printf("Done\n");
    return;
  }
  printf("Not done\n");
}

int get_input(const char question[])
{
  int input;
  printf("%s", question);
  scanf("%d", &input);
  while((getchar()) != '\n');
  return input;
}

Node_ptr create_node(int value)
{
  Node_ptr node = malloc(sizeof(NODE));
  node->value = value;
  node->next = NULL;
  return node;
}

List_ptr create_list(void)
{
  List_ptr list = malloc(sizeof(LIST));
  list->head = NULL;
  list->last = list->head;
  list->count = 0;
  return list;
}

void display(List_ptr list)
{
  Node_ptr p_walk = list->head;
  while(p_walk != NULL)
  {
    printf("%d ", p_walk->value);
    p_walk = p_walk->next;
  }
  printf("\n");
}


STATUS insert_at(List_ptr list, int value, int position)
{
  if (position == 0) return add_to_start(list, value);
  if (position == list->count) return add_to_end(list, value);
  if (position < 0 || position > list->count + 1) return Failure;
  Node_ptr current_node = list->head;
  for (int index = 0; index < position; index++)
  {
    current_node = current_node->next;
  }
  Node_ptr new_node = create_node(value);
  new_node->next = current_node->next;
  current_node->next = new_node;
  list->count++;
  return Success;
}

STATUS add_to_end(List_ptr list, int value)
{
  Node_ptr node = create_node(value);
  STATUS result = Failure;
  if(list->head == NULL)
  {
    list->head = node;
  }
  else
  {
    list->last->next = node;
  }
  list->last = node;
  list->count++;
  result = Success;
  return result;
}

STATUS add_to_start(List_ptr list, int value)
{
  Node_ptr current_head = list->head;
  Node_ptr new_node = create_node(value);
  if(current_head == NULL)
  {
    list->last = new_node;
  }
  else
  {
    new_node->next = current_head;
  }
  list->head = new_node;
  list->count++;
  return Success;
}

STATUS add_unique(List_ptr list, int value)
{
  Node_ptr current_node = list->head;
  while (current_node != NULL)
  {
    if (current_node->value == value) return Failure;
    current_node = current_node->next;
  }
  return add_to_end(list, value);
}

STATUS remove_from_start(List_ptr list)
{
  if (list->count == 0) return Failure;
  if (list->head == list->last) return clear_list(list);
  Node_ptr head = list->head->next;
  list->head = head;
  list->count--;
  return Success;
}

STATUS remove_from_end(List_ptr list)
{
  if (list->count == 0) return Failure;
  if (list->head == list->last) return clear_list(list);
  Node_ptr current_node = list->head;
  for (int index = 1; index < list->count - 1; index++)
  {
    current_node = current_node->next;
  }
  Node_ptr node_to_be_free = current_node->next;
  list->last = current_node;
  free(node_to_be_free);
  current_node->next = NULL;
  list->count--;
  return Success;
}

STATUS free_nodes(List_ptr list)
{
  Node_ptr node_to_be_free = list->head;
  while (node_to_be_free != list->last)
  {
    Node_ptr next_node = node_to_be_free->next;
    free(node_to_be_free);
    node_to_be_free = next_node;
    list->count--;
  }
  free(list->last);
  return Success;
}

void destroy_list(List_ptr list)
{
  free_nodes(list);
  free(list);
}

STATUS clear_list(List_ptr list)
{
  free_nodes(list);
  list->last = NULL;
  list->head = NULL;
  return Success;
}

STATUS remove_at(List_ptr list, int position)
{
  if (position >= list->count || position < 0) return Failure;
  if (position == 0) return remove_from_start(list);
  if (position == list->count - 1) return remove_from_end(list);
  Node_ptr current_node = list->head;
  for (int index = 1; index < position; index++)
  {
    current_node = current_node->next;
  }
  Node_ptr node_to_be_free = current_node->next;
  current_node->next = node_to_be_free->next;
  free(node_to_be_free);
  list->count--;
  return Success;
}

STATUS remove_first_occurrence(List_ptr list, int value) // h
{
  Prev_Current_Pair pair = { NULL, list->head };
  while (pair.current != NULL)
  {
    if(pair.current->value == value)
    {
      Node_ptr node_to_be_free = pair.current;
      if (pair.prev == NULL)
      {
        list->head = node_to_be_free->next;
      }
      else
      {
        pair.prev->next = node_to_be_free->next;
      }
      pair.current = node_to_be_free->next;
      free(node_to_be_free);
      list->count--;
      return Success;
    }
    pair.prev = pair.current;
    pair.current = pair.current->next;
  }
  return Success;
}

STATUS remove_all_occurrences(List_ptr list, int value) // i
{
  Prev_Current_Pair pair = { NULL, list->head };
  while (pair.current != NULL)
  {
    if (pair.current->value == value)
    {
      Node_ptr node_to_be_free = pair.current;
      if (pair.prev == NULL)
      {
        list->head = node_to_be_free->next;
      }
      else
      {
        pair.prev->next = node_to_be_free->next;
      }
      pair.current = node_to_be_free->next;
      free(node_to_be_free);
      list->count--;
    }
    else
    {
      pair.prev = pair.current;
      pair.current = pair.current->next;
    }
  }
  return Success;
}

STATUS perform_actions_upon_input_value(List_ptr list, char decider)
{
  int value;
  STATUS result = Success;
  value = get_input("Enter a number as an input value : ");
  if (decider == 'a') result = add_to_end(list, value);
  if (decider == 'b') result = add_to_start(list, value);
  if (decider == 'd') result = add_unique(list, value);
  if (decider == 'h') result = remove_first_occurrence(list, value);
  if (decider == 'i') result = remove_all_occurrences(list, value);
  return result;
}

STATUS perform_action_only_on_list(List_ptr list, char decider)
{
  STATUS result = Success;
  if (decider == 'l') display(list);
  if (decider == 'e') result = remove_from_start(list);
  if (decider == 'f') result = remove_from_end(list);
  if (decider == 'j') result = clear_list(list);
  return result;
}

void decide_actions(List_ptr list, char decider)
{
  int value, position = 0;
  STATUS result = Success;

  while(getchar() != '\n');

  if (decider == 'a' || decider == 'b' || decider == 'd'|| decider == 'h' || decider == 'i')
  {
    result = perform_actions_upon_input_value(list, decider);
  }
  if(decider == 'l' || decider == 'e' || decider == 'f'|| decider == 'j')
  {
    result = perform_action_only_on_list(list, decider);
  }
  if (decider == 'g') 
  {
    position = get_input("Enter the position : ");
    result = remove_at(list, position);
  }
  if (decider == 'c') 
  {
    value = get_input("Enter a number as an input value : ");
    position = get_input("Enter the position : ");
    result = insert_at(list, value, position);
  }
  print_status(result);
}
