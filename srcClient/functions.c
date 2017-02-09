/*
** functions.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:42:52 2016 David BOIVENT
** Last update Jun 26 18:43:13 2016
*/

#include "object.h"

char *get_line()
{
	int i;
	static char buf[1024];

	i = 0;
	while (read(0, &buf[i], 1))
	{
		if (buf[i] == '\n')
		{
			buf[i + 1] = 0;
			return (buf);
		}
		i++;
	}
	buf[i] = 0;
	return (buf);
}

char *my_strtok(char *str, char c, int start)
{
	int i;
	char *res;
	int check;
	int p;

	res = malloc(sizeof(char) * (strlen(str) + 1));
	i = 0;
	check = 0;
	while (str[i] && check != start)
	{
		if (str[i] == c)
			check++;
		i++;
	}
	p = 0;
	while (str[i] && str[i] != c)
	{
		res[p] = str[i];
		i++;
		p++;
	}
	res[p] = 0;
	return (res);
}
