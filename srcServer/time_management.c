/*
** time_management.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Mon Jun 13 16:28:24 2016 Matthew LEJEUNE
** Last update	Sun Jun 26 17:45:58 2016 Matthew LEJEUNE
*/

#include "server.h"

int64_t get_actual_time()
{
  struct timeval tms;
  int64_t micros;

  if (gettimeofday(&tms, NULL) < 0)
  {
    dprintf(1, "Can't get actual time\n");
    return (-1);
  }
  micros = tms.tv_sec * 1000;
  micros += tms.tv_usec / 1000;
  if (tms.tv_usec % 1000 >= 500)
    micros++;
  return (micros);
}

int64_t get_final_time(int frequency, char *cmd)
{
  int index;
  int64_t action_time;

  index = 0;
  while (g_command[index].cmd != NULL)
  {
    if (strstr(cmd, g_command[index].cmd) != NULL)
      action_time = (g_command[index].t / frequency) * 1000;
    index++;
  }
  action_time += get_actual_time();
  return (action_time);
}

void exec_cmd_time(t_server *server)
{
  int64_t verif_time;
  t_stack *tmp;
  t_client *client;
  t_stack *transf;

  verif_time = get_actual_time();
  tmp = g_exec_pile;
  while (tmp != NULL)
  {
    if (tmp->end_time <= verif_time)
    {
      client = get_client(server, tmp->fd);
      tmp->f(server, client, client->buffer);
      transf = pop_stack(&g_exec_pile, client->fd);
      if (transf != NULL)
        free (transf);
      if ((transf = pop_stack(&(client->client_stack), client->fd)) != NULL)
      {
        push_back_stack_from_elem(server, &g_exec_pile, transf);
        free(transf);
      }
    }
    tmp = tmp->next;
  }
}

void exec_egg_time(t_server *server)
{
  int64_t verif_time;
  t_stack *tmp;
  t_egg *egg;
  t_stack *transf;

  verif_time = get_actual_time();
  tmp = g_egg_pile;
  while (tmp != NULL)
  {
    if (tmp->end_time <= verif_time)
    {
      egg = get_egg(server, tmp->x, tmp->y);
      tmp->e(server, egg, egg->buffer);
      transf = pop_eggstack(&g_egg_pile, egg->x, egg->y);
      if (transf != NULL)
        free (transf);
      if ((transf = pop_eggstack(&(egg->egg_stack), egg->x, egg->y)) != NULL)
      {
        push_back_stack_from_elem(server, &g_egg_pile, transf);
        free(transf);
      }
    }
    tmp = tmp->next;
  }
}
