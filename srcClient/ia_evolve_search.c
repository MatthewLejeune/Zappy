/*
** ia_evolve_search.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:46:53 2016 David BOIVENT
** Last update Jun 26 18:46:55 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

void  move_to(TypeCommand cmd)
{
	Commands *save;

	evolve = 2;
	commands = malloc(sizeof(Commands) + 1);
	commands->act_str = NULL;
	commands->actuelle = cmd;
	save = malloc(sizeof(Commands) + 1);
	save->act_str = NULL;
	save->actuelle = INVENTORY;
	save->next = NULL;
	commands->next = save;
}

void Help(char *rec, int fd)
{
	int dir;

	if (strlen(rec) >= strlen("message  ,lvl ") &&
		strncmp(&rec[strlen("message ") + 1], ",lvl", strlen(",lvl")) == 0)
	{
		if (atoi(&rec[strlen("message  ,lvl")]) - 1 == player->level)
		{
			dir = atoi(&rec[strlen("message ")]);
			if (dir == 0)
			{
				evolve = 3;
				commands = NULL;
			}
			else if (dir == 1 || dir == 2 || dir == 8)
				move_to(WALK);
			else if (dir == 3 || dir == 4 || dir == 5)
				move_to(LEFT);
			else
				move_to(RIGHT);
		}
	}
}

void  incantOrNot(char *rec, int fd)
{
	if (strlen(rec) >= strlen("message  ,incant ") &&
		strncmp(&rec[strlen("message ") + 1], ",incant", strlen(",incant"))
		 == 0)
	{
		if (atoi(&rec[strlen("message  ,incant")]) - 1 == player->level)
		{
			if (atoi(&rec[strlen("message ")]) == 0)
			{
				evolve = 2;
				commands = NULL;
			}
			else
			{
				evolve = 0;
				commands = NULL;
				commands = malloc(sizeof(Commands) + 1);
				commands->act_str = NULL;
				commands->actuelle = INVENTORY;
				commands->next = NULL;
			}
		}
	}
}

void ia_evolve_search(char *rec, int fd)
{
	if (strlen(rec) > strlen("message ") && strncmp(rec, "message ",
		strlen("message ")) == 0)
	{
		incantOrNot(rec, fd);
		Help(rec, fd);
	}
	else
		write_client(fd, NameCommand[INVENTORY]);
}
