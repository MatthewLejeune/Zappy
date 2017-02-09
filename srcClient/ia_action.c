/*
** ia_action.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:44:46 2016 David BOIVENT
** Last update Jun 26 18:45:7 2016
*/

#include "object.h"

Player  *player;
TypeCommand last_command;
Commands *commands;
int evolve;

Commands  *cmdRegister(TypeCommand type, Commands *ptr2)
{
	ptr2 = malloc(sizeof(Commands));
	ptr2->act_str = NULL;
	ptr2->actuelle = type;
	ptr2->next = NULL;
	return (ptr2);
}

void basic_take2(int dir, int second_footsteps, Commands *ptr, Commands *save)
{
	Commands	*ptr2;

	if (dir == 1)
	{
		ptr->next = cmdRegister(LEFT, ptr2);
		ptr = ptr->next;
	}
	else if (dir == 2)
	{
		ptr->next = cmdRegister(RIGHT, ptr2);
		ptr = ptr->next;
	}
	while (--second_footsteps >= 0)
	{
		ptr->next = cmdRegister(WALK, ptr2);
		ptr = ptr->next;
	}
	if (ptr != NULL)
	{
		ptr->next = commands;
		commands = save;
	}
}

void	basic_take(int footsteps, int direction, int second_footsteps)
{
	Commands	*ptr;
	Commands	*ptr2;
	Commands	*save;

	ptr = NULL;
	save = NULL;
	while (--footsteps >= 0)
	{
		ptr2 = cmdRegister(WALK, ptr2);
		if (ptr == NULL)
		{
			ptr = ptr2;
			save = ptr;
		}
		else
		{
			ptr->next = ptr2;
			ptr = ptr->next;
		}
	}
	basic_take2(direction, second_footsteps, ptr, save);
}

int  *take_first_footsteps2(int dest, int i, int *res)
{
	if (dest < i)
	{
		res[1] = 1;
		res[2] = i - dest;
	}
	else if (dest > i)
	{
		res[1] = 2;
		res[2] = dest - i;
	}
	return (res);
}

int  *take_first_footsteps(int dest)
{
	int i;
	int  inc;
	static int res[3];

	i = 0;
	inc = 3;
	res[0] = 0;
	res[1] = 0;
	res[2] = 0;
	while (i < dest)
	{
		res[0]++;
		i = i + inc;
		inc = inc + 2;
	}
	inc = inc - 2;
	i = i - (inc / 2);
	return (take_first_footsteps2(dest, i, res));
}
