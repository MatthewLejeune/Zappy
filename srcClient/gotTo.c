/*
** gotTo.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:43:21 2016 David BOIVENT
** Last update Jun 26 18:44:25 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

int  message_take_send(int i, int count)
{
	Commands	*ptr;

	commands = malloc(sizeof(Commands) + 1);
	commands->act_str = malloc(sizeof(char) *
	(strlen(NameCommand[TAKE]) + strlen(NameObject[i]) + 3));
	sprintf(commands->act_str, "%s%s\n", NameCommand[TAKE],
	NameObject[i]);
	ptr = malloc(sizeof(Commands) + 1);
	ptr->act_str = NULL;
	ptr->actuelle = INVENTORY;
	ptr->next = NULL;
	commands->next = ptr;
	return (count);
}

int  noPlayersInCase(int count, int x, int y, TypeObject  **obj)
{
	unsigned int i;
	int nb_players;
	int p;

	i = 0;
	while (elevations_required[player->level][i + 1] != -1)
	{
		if (elevations_required[player->level][i] > player->inv[i]
				&& obj[y][x] == i + 1)
		{
			nb_players = 0;
			p = -1;
			while (obj[y][++p] != OUTOFLIMITE)
				if (obj[y][p] == PLAYER)
					nb_players++;
			if (nb_players == 0 || (nb_players == 1 && y == 0))
				return (message_take_send(i, count));
		}
		i++;
	}
	return (-1);
}

int  gotTo(TypeObject  **obj)
{
	int x;
	int y;
	int count;

	count = 0;
	y = -1;
	while (obj[++y] != NULL)
	{
		x = -1;
		while (obj[y][++x] != OUTOFLIMITE)
		{
			if (noPlayersInCase(count, x, y, obj) == count)
				return (count);
		}
		count++;
	}
	return (-1);
}

int  gotToFood(TypeObject  **obj)
{
	unsigned int i;
	int x;
	int y;
	int p;
	int nb_players;
	int count;
	Commands	*ptr;

	count = 0;
	y = 0;
	while (obj[y])
	{
		x = 0;
		while (obj[y][x] != OUTOFLIMITE)
		{
			if (obj[y][x] == FOOD + 1)
				return (message_take_send(FOOD, count));
			x++;
		}
	count++;
	y++;
	}
	return (-1);
}
