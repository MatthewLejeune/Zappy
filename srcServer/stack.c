/*
** stack.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Thu Jun 09 16:28:42 2016 David BOIVENT
** Last update	Sun Jun 26 17:48:43 2016 Matthew LEJEUNE
*/

#include "server.h"

t_stack *g_stack = NULL;

t_stack *create_elem_stack(t_server *server, t_client *client)
{
  int x;
  t_stack *new_elem;

  x = 0;
  if ((new_elem = malloc(sizeof(t_stack))) == NULL)
    return (NULL);
  new_elem->fd = client->fd;
  new_elem->x = client->x;
  new_elem->y = client->y;
  new_elem->end_time = get_final_time(server->frequency, client->buffer);
  new_elem->cmd = client->buffer;
  while (g_command[x].cmd != NULL)
  {
    if (strstr(client->buffer, g_command[x].cmd) != NULL)
    {
      new_elem->f = g_command[x].func;
      dprintf(1, "Found\n");
    }
    x++;
  }
  new_elem->next = NULL;
  return (new_elem);
}

t_stack *create_stack_from_elem(t_server *server, t_stack *elem)
{
  t_stack *new_elem;

  if ((new_elem = malloc(sizeof(t_stack))) == NULL)
    return (NULL);
  new_elem->fd = elem->fd;
  new_elem->end_time = get_final_time(server->frequency, elem->cmd);
  new_elem->cmd = elem->cmd;
  new_elem->f = elem->f;
  new_elem->e = elem->e;
  new_elem->next = NULL;
  return (new_elem);
}

void push_back_stack(t_stack **stack, t_server *server, t_client *client)
{
  t_stack *new_elem;
  t_stack *last_elem;

  if ((new_elem = create_elem_stack(server, client)) == NULL)
    return;
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

int push_back_stack_from_elem(t_server *server, t_stack **stack, t_stack *elem)
{
  t_stack *new_elem;
  t_stack *last_elem;

  if ((new_elem = create_stack_from_elem(server, elem)) == NULL)
    return (-1);
  if (*stack == NULL)
    *stack = new_elem;
  else
  {
    last_elem = *stack;
    while (last_elem->next != NULL)
      last_elem = last_elem->next;
    last_elem->next = new_elem;
  }
  return (0);
}
