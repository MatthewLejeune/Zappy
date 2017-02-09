/*
** expulse.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sun Jun 26 17:30:17 2016 Matthew LEJEUNE
** Last update Sun Jun 26 18:53:11 2016 David BOIVENT
*/

#include "server.h"

t_server *get_position_expulse(t_server *server, t_client *client, int i)
{
	if (client->player_direction == UP)
		server->map[client->y][client->x]->clients_on_case[i]->y =
			get_real_pos(server, client->x, client->y - 1)[1];
	else if (client->player_direction == DOWN)
		server->map[client->y][client->x]->clients_on_case[i]->y =
			get_real_pos(server, client->x, client->y + 1)[1];
	else if (client->player_direction == LEFT)
		server->map[client->y][client->x]->clients_on_case[i]->x =
			get_real_pos(server, client->x - 1, client->y)[0];
	else if (client->player_direction == RIGHT)
		server->map[client->y][client->x]->clients_on_case[i]->x =
			get_real_pos(server, client->x + 1, client->y)[0];
	return (server);
}

t_server *expulse_act(t_server *server, t_client *client)
{
	int fd;
	int i;
	int orig;

	i = -1;
	orig = 0;
	while (++i < server->map[client->y][client->x]->nbr_clients) {
  if (server->map[client->y][client->x]->clients_on_case[i]->fd != client->fd)
  {
    fd = server->map[client->y][client->x]->clients_on_case[i]->fd;
		server = get_position_expulse(server, client, i);
    push_client_case(server->map[server->map[client->y][client->x]->clients_on_case[i]->y][server->map[client->y][client->x]->clients_on_case[i]->x],
                    server->map[client->y][client->x]->clients_on_case[i]);
    dprintf(fd, "deplacement: %d\n", orig);
    out_client_case(server->map[client->y][client->x],
                    server->map[client->y][client->x]->clients_on_case[i]);
    i--;
  }
  }
	return (server);
}

void expulse(t_server *server, t_client *client, char *buffer)
{
  buffer = buffer;
  if (server->map[client->y][client->x]->nbr_clients == 1)
  {
    write(client->fd, "ko\n", strlen("ko\n"));
    return ;
  }
	expulse_act(server, client);
  if (server->map[client->y][client->x]->nbr_clients == 1)
    write(client->fd, "ok\n", strlen("ok\n"));
  else
    write(client->fd, "ko\n", strlen("ko\n"));
}
