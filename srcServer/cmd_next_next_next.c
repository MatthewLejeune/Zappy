/*
** cmd_next_next_next.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sun Jun 26 17:22:41 2016 Matthew LEJEUNE
** Last update	Sun Jun 26 18:08:02 2016 Matthew LEJEUNE
*/

#include "server.h"

void display_level(t_server *server, t_client *client)
{
  int index;

  index = 0;
  while (server->map[client->y][client->x]->clients_on_case[index] != NULL)
  {
    server->map[client->y][client->x]->clients_on_case[index]->level += 1;
    dprintf(server->map[client->y][client->x]->clients_on_case[index]->fd,
      "niveau actuel : %d\n",
      server->map[client->y][client->x]->clients_on_case[index]->level);
    index++;
  }
}

void incant(t_server *server, t_client *client, char *buffer)
{
  int i;
  int found;

  buffer = buffer;
  i = 1;
  found = 1;
  dprintf(client->fd, "elevation en cours\n");
  if (verif_lvl_clients(server, client) == elevations[client->level - 1][0])
  {
    while (i < ELEMS && found == 1)
    {
      if (server->map[client->y][client->x]->elem[i] <
                                            elevations[client->level - 1][i])
        found = 0;
      i++;
    }
    if (found == 1)
    {
      i = 0;
      while (++i < ELEMS)
        server->map[client->y][client->x]->elem[i] -=
                                            elevations[client->level - 1][i];
    }
  }
  display_level(server, client);
}
