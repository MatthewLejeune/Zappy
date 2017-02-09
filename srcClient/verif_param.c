/*
** verif_param.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:49:29 2016 David BOIVENT
** Last update Jun 26 18:49:54 2016
*/

#include "object.h"

void	gestion_params_client(char **av, t_env *env)
{
	int	i;

	env->machine = "127.0.0.1";
	i = 1;
	while (av[i] && av[i + 1])
	{
		if (!strcmp(av[i] , "-n") && av[i + 1])
			env->team = av[i + 1];
		if (!strcmp(av[i] , "-p") && av[i + 1])
			env->port = atoi(av[i + 1]);
		if (!strcmp(av[i] , "-h") && av[i + 1])
			env->machine = av[i + 1];
		i += 2;
	}
}

void	usage_client() {
	printf("USAGE\n");
	printf("\t./zappy_ai -n team -p port -h hostname\n\n");

	printf("DESCRIPTION\n");
	printf("\t-n nom d’equipe\n");
	printf("\t-p numero de port\n");
	printf("\t-h nom de la machine, par defaut localhost\n");
}
