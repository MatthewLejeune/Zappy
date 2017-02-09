/*
** life_management.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Tue Jun 21 14:42:05 2016 Matthew LEJEUNE
** Last update	Sat Jun 25 16:00:27 2016 Matthew LEJEUNE
*/

#include "server.h"

t_server *check_loose_life(t_server *server)
{
  int64_t act_time;
  t_client *tmp;
  t_client *tmp2;

  act_time = get_actual_time();
  tmp = server->first;
  while (tmp != NULL)
  {
    if ((tmp->t + ((126 / server->frequency) * 1000)) <= act_time)
    {
      tmp->elem[FOOD] -= 1;
      tmp->t += ((126 / server->frequency) * 1000);
    }
    if (tmp->elem[FOOD] == 0)
    {
      tmp2 = tmp->next;
      dprintf(tmp->fd, "mort\n");
      server = remove_client(tmp->fd, server);
      tmp = NULL;
      tmp = tmp2;
    }
    else
      tmp = tmp->next;
  }
  return (server);
}
