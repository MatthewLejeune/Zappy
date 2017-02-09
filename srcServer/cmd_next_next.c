/*
** cmd_next_next.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Fri Jun 10 14:23:15 2016 David BOIVENT
** Last update	Sun Jun 26 17:23:07 2016 Matthew LEJEUNE
*/

#include "server.h"

void reproduce(t_server *server, t_client *client, char *buffer)
{
  int64_t verif;

  buffer = buffer;
  client = client;
  verif = get_actual_time();
  dprintf(client->fd, "ok\n");
  printf("Client %d laid an egg\n", client->fd);
  server = add_egg(server, client);
  strcpy(server->last_egg->buffer, "hatch\n");
  push_back_eggstack(&g_egg_pile, server, server->last_egg);
}

void hatch(t_server *server, t_egg *egg, char *buffer) {
  buffer = buffer;
  server = server;
  printf("The egg at X:%d Y:%d has hatched\n", egg->x, egg->y);
  egg->squad->max_client++;
  egg->hatch = 1;
}

void connect_slot(t_server *server, t_client *client, char *buffer)
{
  server = server;
  buffer = buffer;
  dprintf(client->fd, "%d\n", server->max_client_per_squad -
                              client->squad->nb_players);
}

unsigned int verif_lvl_clients(t_server *server, t_client *client)
{
  int i;
  unsigned int nb_client;

  i = 0;
  nb_client = 0;
  while (i < server->map[client->y][client->x]->nbr_clients)
  {
    if (server->map[client->y][client->x]->clients_on_case[i]->level ==
                                                                client->level)
      nb_client++;
    i++;
  }
  return (nb_client);
}
