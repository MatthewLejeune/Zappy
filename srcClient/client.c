/*
** client.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:41:49 2016 David BOIVENT
** Last update Jun 26 18:42:28 2016
*/

#include "object.h"

#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 255

Player  *player = NULL;
TypeCommand last_command = CONNECT;
Commands *commands = NULL;
int evolve = 0;

void client_fdset(int fd, fd_set fd_read, struct timeval tv)
{
	FD_ZERO(&fd_read);
	FD_SET(0, &fd_read);
	FD_SET(fd, &fd_read);
	if (select(fd + 1, &fd_read, NULL, NULL, &tv) == -1)
		perror("select");
	if (FD_ISSET(0, &fd_read))
		read_client(0, fd);
	if (FD_ISSET(fd, &fd_read))
		read_client(fd, 1);
}

int begin_client(t_env *env, struct protoent *pe, struct timeval tv)
{
	int   fd;
	fd_set fd_read;
	struct sockaddr_in  s_in;

	fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
	if (fd == -1)
		return (-1);
	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(env->port);
	s_in.sin_addr.s_addr = inet_addr(env->machine);
	if (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)) == -1) {
	  if (close(fd) == -1)
	 		return (-1);
	  return (-1);
	}
	if (protocol_client(fd, env->team) == -1) {
		if (close(fd) == -1)
			 	return (-1);
		return (-1);
	}
	write_client(fd, NameCommand[INVENTORY]);
	while (1)
		client_fdset(fd, fd_read, tv);
	if (close(fd) == -1)
		return (1);
}

int main(int ac, char **av)
{
	t_env	*env;
	struct protoent *pe;
	int i;
	struct timeval tv;

	env = NULL;
	player = malloc(sizeof(Player));
	player->food = 10;
	player->level = 0;
	for (i = 0; i < 6; i++)
	  player->inv[i] = 0;
	if (ac < 5 || ac > 7) {
	  usage_client();
	  return (-1);
	}
	env = malloc(sizeof(t_env));
	gestion_params_client(av, env);
	tv.tv_sec = 20;
	tv.tv_usec = 0;
	pe = getprotobyname("TCP");
	if (!pe)
		return (-1);
	begin_client(env, pe, tv);
	return (0);
}
