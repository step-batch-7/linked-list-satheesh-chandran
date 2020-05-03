#include <stdio.h>
#include <stdlib.h>
#include "list.h"

char get_character(void)
{
  char action;
  printf("Enter any character : ");
  action = getchar();
  return action;
}

int main(void)
{
  List_ptr list = create_list();
  char action = get_character();
  while(action != 'm')
  {
    decide_actions(list, action);
    action = get_character();
  }
  return 0;
}