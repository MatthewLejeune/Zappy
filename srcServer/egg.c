/*
** egg.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sat Jun 25 15:51:20 2016 David BOIVENT
** Last update Jun 25 15:55:50 2016
*/

#include "server.h"

t_egg *create_egg(t_server *server, t_client *client)
{
  t_egg *newEgg;

  if ((newEgg = malloc(sizeof(t_egg))) == NULL)
    return (NULL);
  newEgg->fd = 0;
  newEgg->player_direction = rand() % 3;
  newEgg->squad = client->squad;
  newEgg->x = client->x;
  newEgg->y = client->y;
  newEgg->next = NULL;
  return (newEgg);
}

t_server *add_egg(t_server *server, t_client *client)
{
  t_egg *newEgg;

  if ((newEgg = create_egg(server, client)) == NULL)
    return (NULL);
  newEgg->hatch = 0;
  if (server->first_egg == NULL)
  {
    newEgg->prev = NULL;
    server->first_egg = newEgg;
  }
  else
  {
    server->last_egg->next = newEgg;
    newEgg->prev = server->last_egg;
  }
  server->last_egg = newEgg;
  return (server);
}

t_server *remove_egg(unsigned int x, unsigned int y, t_server *server)
{
  t_egg *tmp;
  t_egg *tmpnext;
  t_egg *tmpprev;

  tmp = server->first_egg;
  while (tmp != NULL && tmp->x != x && tmp->y != y)
    tmp = tmp->next;
  if (tmp != NULL)
  {
    tmpnext = tmp->next;
    tmpprev = tmp->prev;
    if (tmpnext != NULL)
      tmpnext->prev = tmpprev;
    else
      server->last_egg = tmpprev;
    if (tmpprev != NULL)
      tmpprev->next = tmpnext;
    else
      server->first_egg = tmpnext;
    free (tmp);
  }
  return (server);
}
