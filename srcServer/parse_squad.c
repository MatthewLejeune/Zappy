/*
** parse_squad.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Mon Jun 13 15:27:38 2016 Matthew LEJEUNE
** Last update	Thu Jun 23 12:20:45 2016 Matthew LEJEUNE
*/

#include "server.h"

int parse_squad(t_server **server, char **av)
{
  int index;

  index = 0;
  while (av[index] && av[index][0] != '-')
  {
    add_team(server, av[index], (*server)->max_client_per_squad);
    dprintf(1, "Squad id : %d\n", (*server)->last_squad->id);
    index++;
  }
  return (0);
}
