/*
** main.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Thu Jun 09 13:53:09 2016 David BOIVENT
** Last update	Sun Jun 26 18:10:25 2016 Matthew LEJEUNE
*/

#include "server.h"

t_stack *g_exec_pile = NULL;
t_stack *g_egg_pile = NULL;

int check_cmd(t_server *server, t_client *client)
{
  int x = 0;

  while (g_command[x].cmd != NULL)
  {
    if (strstr(client->buffer, g_command[x].cmd) != NULL)
    {
      if (count_elem_stack_per_fd(g_exec_pile, client->fd) >= 1
      &&  count_elem_stack_per_fd(client->client_stack, client->fd) < 9)
      {
        push_back_stack(&(client->client_stack), server, client);
        dprintf(1, "Ajout stack\n");
      }
      else if (count_elem_stack_per_fd(g_exec_pile, client->fd) == 0)
      {
        push_back_stack(&g_exec_pile, server, client);
        dprintf(1, "Ajout pile\n");
      }
      return (0);
    }
    x++;
  }
  return (1);
}

t_client *get_client(t_server *server, int fd)
{
  t_client *tmp;

  tmp = server->first;
  while (tmp != NULL && tmp->fd != fd)
    tmp = tmp->next;
  return (tmp);
}

t_egg *get_egg(t_server *server, int x, int y)
{
  t_egg *tmp;

  tmp = server->first_egg;
  while (tmp != NULL && tmp->x != x && tmp->y != y)
    tmp = tmp->next;
  return (tmp);
}

t_server *client_read(t_server *server, int fd)
{
  int r;
  t_client *client;

  if ((client = get_client(server, fd)) == NULL)
    perror("Client doesn't exist\n");
  r = read(client->fd, client->buffer, SIZE_BUFF);
  if (r > 0)
  {
    client->buffer[r] = '\0';
    dprintf(1, "%d : %s", client->fd, client->buffer);
    if (check_cmd(server, client) == 1)
      write(client->fd, "COMMANDE INVALIDE\n", strlen("COMMANDE INVALIDE\n"));
  }
  else
  {
    printf("%d: Connection closed\n", fd);
    client->squad->nb_players -= 1;
    return (remove_client(fd, server));
  }
  return (server);
}

int main(int ac, char **av)
{
  t_server *server;

  server = NULL;
  if (check_args(ac, av) == -1)
    return (0);
  parse_opt(av, &server);
  server = create_map(server);
  server = spawn_ressources(server);
  return (start_server(server));
}
