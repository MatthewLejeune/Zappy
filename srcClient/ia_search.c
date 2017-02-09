/*
** ia_search.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:47:30 2016 David BOIVENT
** Last update Jun 26 18:47:33 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

void  defaultSearch(int fd)
{
	commands = malloc(sizeof(Commands) + 1);
	commands->next = NULL;
	commands->act_str = NULL;
	commands->actuelle = LOOK;
	write_client(fd, NameCommand[INVENTORY]);
}

void  ia_search(char *rec, int fd)
{
	TypeObject	**obj;
	int *res;
	int i;

	if (last_command == LOOK)
	{
		obj = parse_see(rec);
		if (player->food > 30)
			i = gotTo(obj);
		else
			i = gotToFood(obj);
		if (i != -1)
		{
			res = take_first_footsteps(i);
			basic_take(res[0], res[1], res[2]);
		}
		if (commands != NULL)
			exec_cmd_pile(fd);
		else
			write_client(fd, NameCommand[WALK]);
	}
	else
		defaultSearch(fd);
}
