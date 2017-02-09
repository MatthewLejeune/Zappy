/*
** cmd_tmp.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sat Jun 25 12:37:42 2016 Matthew LEJEUNE
** Last update Sat Jun 25 15:55:39 2016 David BOIVENT
*/

#include "server.h"

void nb_joueur(t_server *server, t_client *client, char *buffer)
{
  buffer = buffer;
  dprintf(client->fd, "Nb joueurs sur case : %d\n",
                  server->map[server->last->y][server->last->x]->nbr_clients);
}

void get_pose(t_server *server, t_client *client, char *buffer)
{
  buffer = buffer;
  server = server;
  dprintf(client->fd, "Client X : %d ;; Client Y : %d\n",
                        client->x, client->y);
}

void level(t_server *server, t_client *client, char *buffer)
{
  buffer = buffer;
  server = server;
  dprintf(client->fd, "Level client : %d\n", client->level);
}
