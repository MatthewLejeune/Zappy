/*
** vector.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sat Jun 25 12:14:27 2016 Matthew LEJEUNE
** Last update Sat Jun 25 16:01:14 2016 David BOIVENT
*/

#include "server.h"

t_case *push_client_case(t_case *n_case, t_client *client) {
	int i;
	int mem;

	i = 0;
	mem = (n_case->clients_on_case == NULL) ? 0 : 1;
	if ((n_case->clients_on_case = realloc(n_case->clients_on_case,
			(sizeof(n_case->clients_on_case) * (n_case->nbr_clients + 1))
                                              + sizeof(t_client))) == NULL)
		return (NULL);
	if (mem == 0)
		memset(n_case->clients_on_case, 0,
       (sizeof(n_case->clients_on_case) * (n_case->nbr_clients + 1)));
 	while (n_case->clients_on_case[i])
   	i++;
	n_case->clients_on_case[i] = client;
	n_case->clients_on_case[i + 1] = NULL;
	n_case->nbr_clients++;
	return (n_case);
}

t_case *pop_client_case(t_case *n_case) {
	int i;

	i = 0;
	while (n_case->clients_on_case[i])
		i++;
	n_case->clients_on_case[i - 1] = NULL;
	if ((n_case->clients_on_case = realloc(n_case->clients_on_case,
			sizeof(n_case->clients_on_case) - sizeof(t_client*))) == NULL)
		return (NULL);
	n_case->nbr_clients--;
	return (n_case);
}

t_case *out_client_case(t_case *n_case, t_client *client) {
	int i;

	i = 0;
	if (n_case->nbr_clients == 0)
		return (n_case);
  while (n_case->clients_on_case[i] &&
					n_case->clients_on_case[i]->fd != client->fd)
		i++;
	i++;
	while (n_case->clients_on_case[i - 1] && n_case->clients_on_case[i])
	{
		n_case->clients_on_case[i - 1] = n_case->clients_on_case[i];
		i++;
	}
  n_case->clients_on_case[i - 1] = NULL;
	n_case->nbr_clients--;
	return (n_case);
}
