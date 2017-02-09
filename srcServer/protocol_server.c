/*
** protocol_server.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sat Jun 25 15:58:42 2016 David BOIVENT
** Last update Jun 25 16:56:25 2016
*/

#include "server.h"

t_server *protocol_server(t_server *server)
{
	char buffer[SIZE_BUFF];
	int nbr_client_request;
	int n;

	n = 0;
	nbr_client_request = 0;
	memset(buffer, 0, SIZE_BUFF);
	write(server->last->fd, "BIENVENUE\n", strlen("BIENVENUE\n"));
	while (nbr_client_request < 10 && n <= 0)
	{
		n = read(server->last->fd, buffer, SIZE_BUFF);
		nbr_client_request++;
	}

	if (nbr_client_request > 10)
	{
		printf("Client %i : connection time out.", server->last->fd);
		server = remove_client(server->last->fd, server);
	}
	else
		server = protocol_send(server, buffer);
	return (server);
}

t_server *protocol_send(t_server *server, char *team)
{
	t_squad *squad;

	squad = server->first_squad;

	if (squad != NULL)
	{
		while (squad != NULL &&
				strcmp(squad->team_name, strndup(team, strlen(team) - 1)) != 0)
			squad = squad->next;
		if (squad != NULL)
			server = protocol_valid(server, squad);
		else
			server = protocol_error(server);
	}
	else
		server = protocol_error(server);
	return (server);
}

t_server *protocol_valid(t_server *server, t_squad *squad)
{
	t_egg *egg;
	char num_clients[16];
	char map_scale[19];

	egg = server->first_egg;
	memset(num_clients, 0, 16);
	memset(map_scale, 0, 19);
	sprintf(num_clients, "%d\n", squad->max_client - squad->nb_players);
	sprintf(map_scale, "%d %d\n", server->world_width, server->world_height);
	if ((squad->max_client - squad->nb_players) < 1)
	{
		printf("Client %i removed\n", server->last->fd);
		write(server->last->fd, num_clients, 16);
		server = remove_client(server->last->fd, server);
		return (server);
	}
	write(server->last->fd, num_clients, 16);
	write(server->last->fd, map_scale, 19);
	add_team_from_team(&(server->last), &squad);
	squad->nb_players += 1;
	if (server->first_egg != NULL && egg->hatch == 1 &&
			(egg = egg_in_team(server, server->last)) != NULL)
		server = client_from_egg(server, server->last, egg);
	printf("Client %i accepted\n", server->last->fd);
	return (server);
}

t_server *protocol_error(t_server *server) {
	printf("Bad Protocol - Exit Client\n");
	write(server->last->fd, "0\n", 16);
	printf("Client %i removed\n", server->last->fd);
	server = remove_client(server->last->fd, server);
	return (server);
}
