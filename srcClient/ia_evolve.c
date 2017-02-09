/*
** ia_evolve.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:46:15 2016 David BOIVENT
** Last update Jun 26 18:46:41 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

void  broadcastIncant2()
{
	Commands *save;

	commands = malloc(sizeof(Commands) + 1);
	commands->next = NULL;
	commands->act_str = malloc(sizeof(char) *
		(strlen(NameCommand[BROADCAST]) + 6));
	sprintf(commands->act_str, "%sincant%i\n", NameCommand[BROADCAST],
     player->level + 1);
	save = malloc(sizeof(Commands) + 1);
	save->act_str = NULL;
	save->actuelle = INCANT;
	save->next = NULL;
	commands->next = save;
	evolve = 3;
}

void  broadcastIncant(int  items_case[7])
{
	if (items_case[6] >= elevations_required[player->level][6])
		broadcastIncant2();
	else
	{
		commands = malloc(sizeof(Commands) + 1);
		commands->next = NULL;
		commands->act_str = malloc(sizeof(char) *
			(strlen(NameCommand[BROADCAST]) + 6));
		sprintf(commands->act_str, "%slvl%i\n", NameCommand[BROADCAST],
			player->level + 1);
	}
}

void  notYet(int i, int items_case[7])
{
	if (items_case[i] < elevations_required[player->level][i])
	{
		commands = malloc(sizeof(Commands) + 1);
		commands->act_str = malloc(sizeof(char) *
			(strlen(NameCommand[PUT]) + strlen(NameObject[i]) + 3));
		commands->next = NULL;
		sprintf(commands->act_str, "%s%s\n", NameCommand[PUT],
		NameObject[i]);
	}
	else
	{
		commands = malloc(sizeof(Commands) + 1);
		commands->act_str = malloc(sizeof(char) *
			(strlen(NameCommand[TAKE]) + strlen(NameObject[i]) + 3));
		commands->next = NULL;
		sprintf(commands->act_str, "%s%s\n", NameCommand[TAKE],
		NameObject[i]);
	}
}

int  checkCaseForElevation(int check, int items_case[7])
{
	int i;

	for (i = 0; i < 6; ++i)
	{
		if (items_case[i] != elevations_required[player->level][i])
		{
			check++;
			notYet(i, items_case);
		}
	}
	return (check);
}

void ia_evolve(char *rec, int fd)
{
	TypeObject	**obj;
	int  items_case[7];
	int i;

	for (i = 0; i < 7; ++i)
		items_case[i] = 0;
	if (last_command == LOOK)
	{
		obj = parse_see(rec);
		i = -1;
		while (obj[0][++i] != OUTOFLIMITE)
		{
			if (obj[0][i] == PLAYER + 1)
				items_case[6]++;
			else if (obj[0][i] < FOOD)
				items_case[obj[0][i] - 1]++;
		}
		if (checkCaseForElevation(0, items_case) == 0)
			broadcastIncant(items_case);
		if (commands != NULL)
			exec_cmd_pile(fd);
	}
	else
		write_client(fd, NameCommand[LOOK]);
}
