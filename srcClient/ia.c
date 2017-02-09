/*
** ia.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:45:20 2016 David BOIVENT
** Last update Jun 26 18:45:58 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

void  ia(char *rec, int fd)
{
	if (strlen(rec) >= strlen("mort") && strncmp(rec, "mort", strlen("mort"))
		== 0)
		exit(1);
	if (strlen(rec) >= strlen("ko") && strncmp(rec, "ko", strlen("ko")) == 0)
	{
		commands = NULL;
		commands = malloc(sizeof(Commands) + 1);
		commands->next = NULL;
		evolve = 0;
		commands->act_str = NULL;
		commands->actuelle = LOOK;
		write_client(fd, NameCommand[INVENTORY]);
		return ;
	}
	ia2(rec, fd);
}

void  ia2(char *rec, int fd)
{
	if (evolve == 3)
	{
		if (strlen(rec) < strlen("message ") || strncmp(rec, "message ",
				strlen("message ")) != 0)
		{
			if (commands != NULL)
			{
				exec_cmd_pile(fd);
				return ;
			}
		}
		if (strlen(rec) > strlen("niveau actuel :") && strncmp(rec,
				"niveau actuel :", strlen("niveau actuel :")) == 0)
		{
			player->level = atoi(&rec[strlen("niveau actuel :") + 1]) - 1;
			commands = NULL;
			evolve = 0;
			write_client(fd, NameCommand[INVENTORY]);
			return ;
		}
		else
			return ;
	}
	ia3(rec, fd);
}

void  ia3(char *rec, int fd)
{
	if (strlen(rec) >= strlen("elevation en cours") && strncmp(rec,
		"elevation en cours", strlen("elevation en cours")) == 0)
		return;
	if (strlen(rec) > strlen("message ") && strncmp(rec, "message ",
		strlen("message ")) == 0 && evolve != 2 && evolve != 3)
	{
		if (strlen(rec) >= strlen("message  ,lvl ") &&
			strncmp(&rec[strlen("message ") + 1], ",lvl", strlen(",lvl")) == 0)
		{
			if (atoi(&rec[strlen("message  ,lvl")]) - 1 == player->level)
			{
				commands = NULL;
				evolve = 2;
				return;
			}
			else
				return;
		}
		else
			return;
	}
	ia4(rec, fd);
}

void  ia4(char *rec, int fd)
{
	if (strlen(rec) > strlen("niveau actuel :") && strncmp(rec,
		"niveau actuel :", strlen("niveau actuel :")) == 0 && evolve != 3)
	{
		player->level = atoi(&rec[strlen("niveau actuel :") + 1]) - 1;
		commands = malloc(sizeof(Commands) + 1);
		commands->next = NULL;
		evolve = 0;
		commands->act_str = NULL;
		commands->actuelle = INVENTORY;
		return;
	}
	if (last_command == INVENTORY)
		parseInventaire(rec);
	ia5(rec, fd);
}

void  ia5(char *rec, int fd)
{
	if (strlen(rec) < strlen("message ") || strncmp(rec, "message ",
		strlen("message ")) != 0)
	{
		if (commands != NULL)
		{
			exec_cmd_pile(fd);
			return;
		}
	}
	if (last_command == INVENTORY)
		parseInventaire(rec);
	if (check_requirement() == 0)
		ia_search(rec, fd);
	else if (evolve == 1)
		ia_evolve(rec, fd);
	else if (evolve == 2)
		ia_evolve_search(rec, fd);
}
