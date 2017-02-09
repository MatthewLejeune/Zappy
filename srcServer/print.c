/*
** string.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Thu Jun 09 13:53:35 2016 David BOIVENT
** Last update	Sat Jun 25 11:35:22 2016 Matthew LEJEUNE
*/

#include "server.h"

void write_everywhere(t_server *server, char *string,
                      t_client *client, int dir)
{
  t_client *tmp;

  client = client;
  tmp = server->first;
  while (tmp != NULL)
  {
    if (client->fd != tmp->fd)
      dprintf(tmp->fd, "message %d,%s", dir, string);
    tmp = tmp->next;
  }
}

void write_to_someone(t_client *src, t_client *dest, char *string)
{
  dprintf(dest->fd, PINK"%d : ", src->fd);
  dprintf(dest->fd, "%s"NORMAL, string);
}
