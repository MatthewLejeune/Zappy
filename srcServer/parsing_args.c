/*
** parsing_args.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Fri Jun 10 15:46:01 2016 Matthew LEJEUNE
** Last update	Mon Jun 13 15:31:13 2016 Matthew LEJEUNE
*/

#include "server.h"

int find_port(char **av)
{
  int index;

  index = 0;
  while (av[index] != NULL)
  {
    if (strcmp(av[index], "-p") == 0)
      return (atoi(av[index + 1]));
    index++;
  }
  return (-1);
}

void parse_h_w(char **av, t_server **server)
{
  int number;

  if (!av[1] || (number = atoi(av[1])) == 0)
  {
    dprintf(1, "World size must be > 0 in each axes\n");
    exit(EXIT_FAILURE);
  }
  if (av[0][1] == 'x')
    (*server)->world_width = atoi(av[1]);
  else if (av[0][1] == 'y')
    (*server)->world_height = atoi(av[1]);
}

void parse_nb_client(char **av, t_server **server)
{
  if (!av[1] || av[1][0] == '-')
  {
    dprintf(1, "Missing argument for '%c'\n", av[0][1]);
    exit(EXIT_FAILURE);
  }
  (*server)->max_client_per_squad = atoi(av[1]);
}

void parse_frequency(char **av, t_server **server)
{
  if (!av[1] || av[1][0] == '-' || atoi(av[1]) <= 0)
  {
    dprintf(1, "Invalid argument for '%c'\n", av[0][1]);
    exit(EXIT_FAILURE);
  }
  (*server)->frequency = atoi(av[1]);
}

int parse_opt(char **av, t_server **server)
{
  int index;
  int port;

  index = 0;
  if ((port = find_port(av)) == -1)
  {
    dprintf(1, "Port not found");
    return (-1);
  }
  *server = init_server(port);
  (*server)->port = port;
  while (av[index] != NULL)
  {
    if (av[index][1] == 'x' || av[index][1] == 'y')
      parse_h_w(&av[index], server);
    if (av[index][1] == 'c')
      parse_nb_client(&av[index], server);
    if (av[index][1] == 't')
      parse_frequency(&av[index], server);
    if (av[index][1] == 'n')
      parse_squad(server, &av[index + 1]);
    index++;
  }
  return (0);
}
