/*
** parse_obj.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:47:57 2016 David BOIVENT
** Last update Jun 26 18:48:13 2016
*/

#include "object.h"

Player  *player;

TypeObject	parse_objects(char *origin)
{
	TypeObject obj;
	int i;
	int p;

	p = 0;
	i = 0;
	while (NameObject[i] != NULL && p == 0 && i < OTHER)
	{
		if (strcmp(NameObject[i], origin) == 0)
			p = 1;
		i++;
	}
	obj = i;
	return (obj);
}

void  parseInventaire(char *str)
{
	int i;
	int ind;

	i = 0;
	ind = -1;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (ind < 0)
				player->food = atoi(&str[i]);
			else
				player->inv[ind] = atoi(&str[i]);
			ind++;
			while (str[i] && str[i] >= '0' && str[i] <= '9')
				i++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
}

char **parse_command(char *tab)
{
	int i;
	char **res;
	int max;
	char *str;

	i = 0;
	if (tab == NULL)
		return (NULL);
	for (max = 0; tab[i]; i++)
	{
		if (tab[i] == '\n')
			max++;
	}
	i = 0;
	res = malloc(sizeof(char *) * (max + 3));
	while (max > i)
	{
		str = my_strtok(tab, '\n', i);
		res[i] = str;
		i++;
	}
	res[i] = NULL;
	return (res);
}
