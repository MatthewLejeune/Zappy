/*
** squad.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Thu Jun 23 12:19:04 2016 Matthew LEJEUNE
** Last update	Sat Jun 25 12:01:08 2016 Matthew LEJEUNE
*/

#include "server.h"

int count_team(t_server *server)
{
	int i;
	t_squad *tmp;

	i = 0;
	if (!server->first_squad)
		return (0);
	tmp = server->first_squad;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void add_team(t_server **server, char *name, int max)
{
	t_squad *new_squad;

	if ((new_squad = malloc(sizeof(t_squad))) != NULL)
	{
		if ((*server)->first_squad == NULL)
		{
			(*server)->first_squad = new_squad;
			new_squad->prev = NULL;
		}
		else
		{
			new_squad->prev = (*server)->last_squad;
			(*server)->last_squad->next = new_squad;
		}
		new_squad->team_name = name;
		new_squad->max_client = max;
		new_squad->nb_players = 0;
		new_squad->next = NULL;
		(*server)->last_squad = new_squad;
		new_squad->id = count_team(*server);
	}
}

void add_team_from_team(t_client **client, t_squad **squad)
{
	(*client)->squad = *squad;
}

t_server *remove_team(t_server *server, char *name_team)
{
	t_squad *tmp;
	t_squad *tmpnext;
	t_squad *tmpprev;

	tmp = server->first_squad;
	while (tmp != NULL && strcmp(tmp->team_name, name_team) != 0)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		tmpnext = tmp->next;
		tmpprev = tmp->prev;
		if (tmpnext != NULL)
			tmpnext->prev = tmpprev;
		else
			server->last_squad = tmpprev;
		if (tmpprev != NULL)
			tmpprev->next = tmpnext;
		else
			server->first_squad = tmpnext;
		free (tmp);
	}
	return (server);
}
