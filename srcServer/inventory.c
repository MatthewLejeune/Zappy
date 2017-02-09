/*
** inventory.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Thu Jun 09 15:17:07 2016 Matthew LEJEUNE
** Last update	Sun Jun 26 17:40:42 2016 Matthew LEJEUNE
*/

#include "server.h"

void get_str_elem(int i, unsigned int elems[ELEMS], char str_elem[1024])
{
  int i1 = 0;
  memset(str_elem, '\0', 1024);
  if (i == FOOD)
    sprintf(str_elem, "nourriture %d", elems[i]);
  else if (i == LINEMATE)
    sprintf(str_elem, "linemate %d", elems[i]);
  else if (i == DERAUMERE)
    sprintf(str_elem, "deraumere %d", elems[i]);
  else if (i == SIBUR)
    sprintf(str_elem, "sibur %d", elems[i]);
  else if (i == MENDIANE)
    sprintf(str_elem, "mendiane %d", elems[i]);
  else if (i == PHIRAS)
    sprintf(str_elem, "phiras %d", elems[i]);
  else if (i == THYSTAME)
    sprintf(str_elem, "thystame %d", elems[i]);
}

char *get_inventory(unsigned int elems[ELEMS])
{
  int i;
  char *inventory;
  char value[1024];

  i = 0;
  if ((inventory = malloc(sizeof(char) * 1024)) == NULL)
    return (NULL);
  memset(inventory, '\0', 1024);
  inventory[0] = '{';
  while (i < ELEMS)
  {
    get_str_elem(i, elems, value);
    inventory = strncat(inventory, value, strlen(value));
    if ((i + 1) != ELEMS)
      inventory = strcat(inventory, ", ");
    i++;
  }
  inventory = strcat(inventory, "}");
  return (inventory);
}
