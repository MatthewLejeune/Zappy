/*
** ia_func.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:47:10 2016 David BOIVENT
** Last update Jun 26 18:47:19 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

void  exec_cmd_pile(int fd)
{
	Commands *save;

	if (commands->act_str != NULL)
		write_client(fd, commands->act_str);
	else
		write_client(fd, NameCommand[commands->actuelle]);
	save = commands;
	commands = commands->next;
	free(save);
}

int  check_requirement()
{
	int i;

	i = 0;
	if (evolve != 0)
		return (evolve);
	if (player->food < 10)
	{
		evolve = 0;
		return (evolve);
	}
	for (i = 0; i < 6; i++)
	{
	  if (player->inv[i] < elevations_required[player->level][i])
	  	return (evolve);
	}
	evolve = 1;
	return (evolve);
}
