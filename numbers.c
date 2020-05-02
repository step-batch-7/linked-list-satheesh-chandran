#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(void)
{
  List_ptr list = create_list();
  char action;
  int value, position;
  printf("Enter any character : ");
  action = getchar();
  while(action != 'm')
  {
    decide_actions(list, action);
    printf("Enter any character : ");
    action = getchar();
  }
  return 0;
}