/*
** list.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Thu Jun 09 13:53:25 2016 David BOIVENT
** Last update	Sun Jun 26 17:41:14 2016 Matthew LEJEUNE
*/

#include "server.h"

t_server *init_server(int port)
{
  t_server *newServer;

  if ((newServer = malloc(sizeof(t_server))) == NULL)
    return (NULL);
  newServer->port = port;
  newServer->fd = FD_SERVER;
  newServer->s = socket(PF_INET, SOCK_STREAM, 0);
  newServer->sin.sin_family = AF_INET;
  newServer->sin.sin_port = htons(newServer->port);
  newServer->sin.sin_addr.s_addr = INADDR_ANY;
  bind(newServer->s, (struct sockaddr*)&newServer->sin,
        sizeof(newServer->sin));
  listen(newServer->s, 42);
  newServer->first = NULL;
  newServer->last = NULL;
  newServer->first_squad = NULL;
  newServer->last_squad = NULL;
  newServer->first_egg = NULL;
  newServer->last_egg = NULL;
  newServer->tv.tv_sec = 1;
  newServer->tv.tv_usec = 0;
  newServer->nb_client = 0;
  return (newServer);
}

t_client *create_client(t_server *server)
{
  t_client *newClient;

  if ((newClient = malloc(sizeof(t_client))) == NULL)
    return (NULL);
  newClient->life_units = LIFE_UNIT;
  newClient->time_units = TIME_UNIT;
  newClient->player_direction = UP;
  newClient->elem[FOOD] = 10;
  newClient->elem[LINEMATE] = 0;
  newClient->elem[DERAUMERE] = 0;
  newClient->elem[SIBUR] = 0;
  newClient->elem[MENDIANE] = 0;
  newClient->elem[PHIRAS] = 0;
  newClient->elem[THYSTAME] = 0;
  newClient->client_stack = NULL;
  newClient->t = get_actual_time();
  newClient->squad = NULL;
  newClient->x = rand() % (server->world_width - 1);
  newClient->y = rand() % (server->world_height - 1);
  newClient->level = 1;
  newClient->client_sin_len = sizeof(newClient->client_sin);
  newClient->fd = accept(FD_SERVER, (struct sockaddr *)&newClient->client_sin,
                          &newClient->client_sin_len);
  return (newClient);
}

t_server *add_client(t_server *server)
{
  t_client *newClient;

  if ((newClient = create_client(server)) == NULL)
    return (NULL);
  if (server->first == NULL)
  {
    newClient->prev = NULL;
    server->first = newClient;
  }
  else
  {
    server->last->next = newClient;
    newClient->prev = server->last;
  }
  newClient->next = NULL;
  server->last = newClient;
  server->nb_client += 1;
  return (server);
}

t_server *client_from_egg(t_server *server, t_client *client, t_egg *egg)
{
	server->map[client->y][client->x] =
                  out_client_case(server->map[client->y][client->x], client);
	client->x = egg->x;
	client->y = egg->y;
	server->map[client->y][client->x] =
                  push_client_case(server->map[client->y][client->x], client);
	client->player_direction = egg->player_direction;
	server = remove_egg(egg->x, egg->y, server);
	printf("New Client get out of the egg\n");
	return (server);
}

t_egg *egg_in_team(t_server *server, t_client *client) {
	t_egg *egg;

	egg = server->first_egg;
	while (egg != NULL && strcmp(egg->squad->team_name,
                                client->squad->team_name) != 0)
		egg = egg->next;
	return (egg);
}

t_server *remove_client(int fd, t_server *server)
{
  t_client *tmp;
  t_client *tmpnext;
  t_client *tmpprev;

  tmp = server->first;
  while (tmp != NULL && tmp->fd != fd)
    tmp = tmp->next;
  if (tmp != NULL)
  {
    if (tmp->squad != NULL)
      tmp->squad->nb_players -= 1;
    server->map[tmp->x][tmp->y] =
                          out_client_case(server->map[tmp->x][tmp->y], tmp);
    tmpnext = tmp->next;
    tmpprev = tmp->prev;
    if (tmpnext != NULL)
      tmpnext->prev = tmpprev;
    else
      server->last = tmpprev;
    if (tmpprev != NULL)
      tmpprev->next = tmpnext;
    else
      server->first = tmpnext;
    if (tmp->fd != -1) {
      clean_pile(tmp);
      close(tmp->fd);
    }
    free (tmp);
  }
  return (server);
}
