/*
** protocol_client.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:49:06 2016 David BOIVENT
** Last update Jun 26 18:49:11 2016
*/

#include "object.h"

int protocol_client(int fd, char *team_name)
{
	char buffer[BUFF_SIZE];
	char coord[BUFF_SIZE];
	int n;

	memset(buffer, 0, BUFF_SIZE);
	memset(coord, 0, BUFF_SIZE);
	n = read(fd, buffer, BUFF_SIZE);
	if (n <= 0 || strcmp(buffer, "BIENVENUE\n") != 0)
		return (-1);
	printf("SERVER : %s", buffer);
	write(fd, strcat(strndup(team_name, strlen(team_name)), "\n\0"),
		strlen(team_name ) + 1);
	memset(buffer, 0, BUFF_SIZE);
	n = read(fd, buffer, BUFF_SIZE);
	if (atoi(strndup(buffer, strlen(buffer) - 1)) < 1 ||
		strcmp(buffer, "ko\n") == 0) {
		printf("No more place in this team\n");
		return (-1);
	}
	else
		read(fd, coord, BUFF_SIZE);
	printf("['%s', '%s']\n", strndup(buffer, strlen(buffer) - 1),
		strndup(coord, strlen(coord) - 1));
	return (0);
}
