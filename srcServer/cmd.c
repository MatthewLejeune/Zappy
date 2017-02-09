/*
** cmd.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Thu Jun 09 13:53:31 2016 David BOIVENT
** Last update	Sun Jun 26 17:38:02 2016 Matthew LEJEUNE
*/

#include "server.h"

void move(t_server *server, t_client *client, char *buffer)
{
  buffer = buffer;
  server->map[client->y][client->x] =
    out_client_case(server->map[client->y][client->x], client);
  if (client->player_direction == UP)
    client->y = get_real_pos(server, client->x, client->y - 1)[1];
  else if (client->player_direction == DOWN)
    client->y = get_real_pos(server, client->x, client->y + 1)[1];
  else if (client->player_direction == LEFT)
    client->x = get_real_pos(server, client->x - 1, client->y)[0];
  else if (client->player_direction == RIGHT)
    client->x = get_real_pos(server, client->x + 1, client->y)[0];
  write(client->fd, "ok\n", 3);
  server->map[client->y][client->x] =
    push_client_case(server->map[client->y][client->x], client);
  printf("Client %d avance\n", client->fd);
}

void right(t_server *server, t_client *client, char *buffer)
{
  server = server;
  buffer = buffer;
  if (client->player_direction == LEFT)
    client->player_direction = UP;
  else
    client->player_direction += 1;
  write(client->fd, "ok\n", 3);
  printf("Client %d tourne vers la droite\n", client->fd);
}

void left(t_server *server, t_client *client, char *buffer)
{
  server = server;
  buffer = buffer;
  if (client->player_direction == UP)
    client->player_direction = LEFT;
  else
    client->player_direction -= 1;
  write(client->fd, "ok\n", 3);
  printf("Client %d tourne vers la gauche\n", client->fd);
}

void see(t_server *server, t_client *client, char *buffer)
{
  char *see_str;

  server = server;
  buffer = buffer;
  get_see(client, server);
}

void inventory(t_server *server, t_client *client, char *buffer)
{
  char *inventory;

  server = server;
  buffer = buffer;
  inventory = get_inventory(client->elem);
  dprintf(client->fd, "%s\n", inventory);
  printf("Client %d inventaire\n", client->fd);
}
