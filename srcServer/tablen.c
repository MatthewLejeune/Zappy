/*
** tablen.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sat Jun 25 12:38:15 2016 Matthew LEJEUNE
** Last update	Sun Jun 26 17:45:08 2016 Matthew LEJEUNE
*/

#include "server.h"

int tablen(t_client **tab)
{
  int i;

  i = 0;
  if (tab == NULL)
    return (0);
  while (tab[i] != NULL)
    i++;
  return (i);
}

t_stack *pop_stack(t_stack **stack, int fd)
{
  t_stack *tmp;
  t_stack *to_free;

  tmp = *stack;
  if (tmp == NULL)
    return (NULL);
  if (tmp->fd == fd)
  {
    *stack = tmp->next;
    return (tmp);
  }
  while (tmp != NULL && tmp->next != NULL && tmp->next->fd != fd)
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

int count_elem_stack_per_fd(t_stack *stack, int fd)
{
  int i;
  t_stack *tmp;

  i = 0;
  tmp = stack;
  while (tmp != NULL)
  {
    if (fd == tmp->fd)
      i++;
    tmp = tmp->next;
  }
  return (i);
}

void clean_pile(t_client *client)
{
  pop_stack(&g_exec_pile, client->fd);
  pop_stack(&(client->client_stack), client->fd);
}
