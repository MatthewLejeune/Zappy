/*
** egg_stack.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sat Jun 25 12:54:39 2016 Matthew LEJEUNE
** Last update	Sat Jun 25 16:36:08 2016 Matthew LEJEUNE
*/

#include "server.h"

t_stack *create_egg_stack(t_server *server, t_egg *egg)
{
  t_stack *new_elem;

  if ((new_elem = malloc(sizeof(t_stack))) == NULL)
    return (NULL);
  new_elem->fd = egg->fd;
  new_elem->x = egg->x;
  new_elem->y = egg->y;
  new_elem->end_time = ((600 / server->frequency) * 1000) + get_actual_time();
  new_elem->cmd = egg->buffer;
  if (strstr(egg->buffer, "hatch\n") != NULL)
  {
    new_elem->e = hatch;
    dprintf(1, "Found\n");
  }
  new_elem->next = NULL;
  return (new_elem);
}

void push_back_eggstack(t_stack **stack, t_server *server, t_egg *egg)
{
  t_stack *new_elem;
  t_stack *last_elem;

  if ((new_elem = create_egg_stack(server, egg)) == NULL)
    return ;
  if (*stack == NULL)
    *stack = new_elem;
  else
  {
    last_elem = *stack;
    while (last_elem->next != NULL)
      last_elem = last_elem->next;
    last_elem->next = new_elem;
  }
}
t_stack *pop_eggstack(t_stack **stack, int x, int y)
{
  t_stack *tmp;
  t_stack *to_free;

  tmp = *stack;
  if (tmp == NULL)
    return (NULL);
  if (tmp->x == x && tmp->y == y)
  {
    *stack = tmp->next;
    return (tmp);
  }
  while (tmp != NULL && tmp->next != NULL &&
                          (tmp->next->x != x && tmp->next->y != y))
    tmp = tmp->next;
  if (tmp != NULL)
  {
    to_free = tmp->next;
    if (tmp->next != NULL && tmp->next->next != NULL)
      tmp->next = tmp->next->next;
    else
      tmp->next = NULL;
    return (to_free);
  }
  return (NULL);
}
