/*
** write_read.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:50:15 2016 David BOIVENT
** Last update Jun 26 18:50:18 2016
*/

#include "object.h"

TypeCommand last_command;

void write_client(int fd, char *line)
{
	int i;

	i = 0;
	while (i < WRONG && (strlen(line) < strlen(NameCommand[i])
		|| strncmp(NameCommand[i], line, strlen(NameCommand[i])) != 0))
		i++;
	last_command = i;
	printf("%s", line);
	write(fd, line, strlen(line));
}

void  read_client(int fd, int fd_w)
{
	int len;
	char  *line;
	char  rec[1024];
	char **all_line;
	int i;

	if (fd == 0)
	{
		line = get_line();
		if (line[strlen(line) - 1] == '\n')
			write_client(fd_w, line);
	}
	else
	{
		len = recv(fd, &rec[0], 1024, MSG_DONTWAIT);
		rec[len] = 0;
		i = -1;
		all_line = parse_command(rec);
		while (all_line[++i] != NULL)
		{
			ia(all_line[i], fd);
			free(all_line[i]);
		}
	}
}
