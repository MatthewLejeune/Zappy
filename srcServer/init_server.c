/*
** init_server.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Thu Jun 09 14:07:36 2016 David BOIVENT
** Last update	Sun Jun 26 18:04:59 2016 Matthew LEJEUNE
*/

#include "server.h"

pthread_mutex_t mu_graphic = PTHREAD_MUTEX_INITIALIZER;

t_server *fd_settings(t_server *server, fd_set *fd_read, int val)
{
  t_client *tmp;
  t_client *tmp2;

  if (val == SET)
  {
    tmp = server->first;
    FD_SET(server->s, fd_read);
    while (tmp != NULL)
    {
      FD_SET(tmp->fd, fd_read);
      tmp = tmp->next;
    }
  }
  else
  {
    tmp = server->first;
    while (tmp != NULL)
    {
      tmp2 = tmp->next;
      if (FD_ISSET(tmp->fd, fd_read))
        server = client_read(server, tmp->fd);
      tmp = tmp2;
    }
  }
  return (server);
}

void *graphic_thread(void *arg)
{
  t_server *server;
  pthread_mutex_lock (&mu_graphic);
  server = (t_server *)arg;
  pthread_mutex_unlock (&mu_graphic);
  display(server, arg);
  pthread_exit(NULL);
}

t_server *start2(t_server *server, fd_set *fd_read)
{
  if (server->nb_client <= MAX_FD)
  {
    if (select(server->nb_client + 8,
                    fd_read, NULL, NULL, &(server->tv)) == -1)
      perror("Select error @start_server ");
    if (FD_ISSET(server->s, fd_read))
    {
      server = add_client(server);
      dprintf(1, "tablen init before : %d\n",
      tablen(server->map[server->last->y][server->last->x]->clients_on_case));
      server->map[server->last->y][server->last->x] =
            push_client_case(
            server->map[server->last->y][server->last->x], server->last);
      dprintf(1, "tablen init after : %d\n",
      tablen(server->map[server->last->y][server->last->x]->clients_on_case));
      server = protocol_server(server);
    }
  }
  return (server);
}

int start_server(t_server *server)
{
  fd_set fd_read;
  pthread_t t_graphic;

  pthread_create(&t_graphic, NULL, graphic_thread, server);
  srand(time(0));
  while (1)
  {
    pthread_mutex_lock(&mu_graphic);
    FD_ZERO(&fd_read);
    server = fd_settings(server, &fd_read, SET);
    start2(server, &fd_read);
    server = fd_settings(server, &fd_read, ISSET);
    exec_cmd_time(server);
    exec_egg_time(server);
    pthread_mutex_unlock (&mu_graphic);
    server = check_loose_life(server);
  }
  return (0);
}
