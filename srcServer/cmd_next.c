/*
** cmd_next.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Fri Jun 10 14:18:28 2016 David BOIVENT
** Last update	Sun Jun 26 17:37:49 2016 Matthew LEJEUNE
*/

#include <math.h>
#include "server.h"

unsigned int elevations[8][7] = {
									{1, 1, 0, 0, 0, 0, 0},
									{2, 1, 1, 1, 0, 0, 0},
									{2, 2, 0, 1, 0, 2, 0},
									{4, 1, 1, 2, 0, 1, 0},
									{4, 1, 2, 1, 3, 0, 0},
									{6, 1, 2, 3, 0, 1, 0},
									{6, 2, 2, 2, 2, 2, 1}
								};

void take(t_server *server, t_client *client, char *buffer)
{
  char *elem;
  int totake;
  server = server;
  elem = &buffer[6];
  totake = get_elem_from_name(elem);
  if (server->map[client->y][client->x]->elem[totake] > 0 && totake != -1)
  {
    server->map[client->y][client->x]->elem[totake] -= 1;
    client->elem[totake] += 1;
    dprintf(client->fd, "ok\n");
    printf("Client %d prend %s\n", client->fd, elem);
  }
  else
  {
    dprintf(client->fd, "ko\n");
    printf("Client %d ne prend pas %s - NOT ENOUGH\n", client->fd, elem);
  }
}

void drop(t_server *server, t_client *client, char *buffer)
{
  char *elem;
  int todrop;
  server = server;
  dprintf(1, "%s", buffer);
  elem = &buffer[5];
  todrop = get_elem_from_name(elem);
  if (client->elem[todrop] > 0 && todrop != -1)
  {
    client->elem[todrop] -= 1;
    server->map[client->y][client->x]->elem[todrop] += 1;
    dprintf(client->fd, "ok\n");
    printf("Client %d pose %s\n", client->fd, elem);
  }
  else
  {
    dprintf(client->fd, "ko\n");
    printf("Client %d ne pose pas %s - NOT ENOUGH\n", client->fd, elem);
  }
}
