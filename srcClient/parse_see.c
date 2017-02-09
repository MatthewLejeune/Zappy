/*
** parse_see.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:48:26 2016 David BOIVENT
** Last update Jun 26 18:48:48 2016
*/

#include "object.h"

TypeObject	**parse_see3(char ***origin, int max)
{
	int i;
	int p;
	TypeObject	**tab;

	i = 0;
	tab = malloc(sizeof(TypeObject *) * (max + 1));
	while (origin[i])
	{
		max = 0;
		while (origin[i][max])
			max++;
		tab[i] = malloc(sizeof(TypeObject) * (max + 1));
		p = 0;
		while (origin[i][p])
		{
			tab[i][p] = parse_objects(origin[i][p]);
			p++;
		}
		tab[i][p] = OUTOFLIMITE;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	**parse_see2(char *tab)
{
	int i;
	char **res;
	char *str;
	int max;

	i = 0;
	if (tab == NULL)
		return (NULL);
	if (tab && tab[0] == ' ')
		tab = &tab[1];
	for (max = 0; tab[i]; i++)
		if (tab[i] == ' ')
			max++;
	i = 0;
	res = malloc(sizeof(char *) * (max + 3));
	while (max >= i)
	{
		str = my_strtok(tab, ' ', i);
		res[i] = str;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**parse_case(char *origin, int max)
{
	int i;
	char	*save;
	char	**tab_sav;

	tab_sav = malloc(sizeof(char *) * (max + 2));
	i = -1;
	while (++i <= max)
	{
		save = my_strtok(origin, ',', i);
		if (save[0] != 0)
			tab_sav[i] = save;
		else
			tab_sav[i] = "vide";
	}
	tab_sav[i] = NULL;
	return (tab_sav);
}

TypeObject	**parse_see(char *origin)
{
	char	***tiles;
	char	**tab_sav;
	int	i;
	int max;

	origin[strlen(origin) - 2] = 0;
	origin = &origin[1];
	i = 0;
	for (max = 0; origin[i]; i++)
		if (origin[i] == ',')
			max++;
	tiles = malloc(sizeof(char **) * (max + 2));
	tab_sav = parse_case(origin, max);
	i = -1;
	while (++i <= max)
		tiles[i] = parse_see2(tab_sav[i]);
	tiles[i] = NULL;
	return (parse_see3(tiles, i));
}
