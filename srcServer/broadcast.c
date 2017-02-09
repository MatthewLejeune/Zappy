/*
** broadcast.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sun Jun 26 17:34:30 2016 Matthew LEJEUNE
** Last update Sun Jun 26 18:51:55 2016 David BOIVENT
*/

#include "server.h"

void case_dir(int *X, int *Y, t_client *client)
{
  if (client->player_direction == UP)
  {
    *X = 0;
    *Y = 0;
  }
  else if (client->player_direction == LEFT)
  {
    *X = 2;
    *Y = 2;
  }
  else if (client->player_direction == DOWN)
  {
    *X = 4;
    *Y = 4;
  }
  else if (client->player_direction == RIGHT)
  {
    *X = 6;
    *Y = 6;
  }
}

int  find_case_dir(t_client *client, int x, int y)
{
  int tabx[9] = {0, -1, -1, -1, 0, 1, 1, 1};
  int taby[9] = {-1, -1, 0, 1, 1, 1, 0, -1};
  int X;
  int Y;
  int count;

  count = 1;
  if (x == 0 && y == 0)
    return (0);
  case_dir(&X, &Y, client);
  while (count <= 8)
  {
    if (tabx[X] == x && taby[Y] == y)
      return (count);
    if (X == 7)
      X = 0;
    else
      X++;
    if (Y == 7)
      Y = 0;
    else
      Y++;
    count++;
  }
  return (0);
}

int  *best_way(t_server *server, t_client *client, t_client *tmp)
{
  int x;
  int y;
  int res;
  static int ret[2];

  y = -2;
  res = 1000000;
  while (++y <= 1)
  {
    x = -2;
    while (++x <= 1)
    {
      if (sqrt(pow(((int)client->x + (x * (int)server->world_width))
    - (int)tmp->x, 2) + pow(((int)client->y + (y * (int)server->world_height))
    - (int)tmp->y, 2)) < res)
      {
        res = sqrt(pow(((int)client->x + (x * (int)server->world_width))
          - (int)tmp->x, 2) + pow(((int)client->y
          + (y * (int)server->world_height)) - (int)tmp->y, 2));
        ret[0] =  (client->x + (x * (int)server->world_width)) - tmp->x;
        ret[1] =  (client->y + (y * (int)server->world_height)) - tmp->y;
      }
    }
  }
  return (ret);
}

void broadcast2(int res[2], t_client *client, t_client *tmp, t_server *server)
{
		res[0] = client->x - tmp->x;
		res[1] = client->y - tmp->y;
		res = best_way(server, client, tmp);
		if (res[0] > 0)
			res[0] = 1;
		else if (res[0] < 0)
			res[0] = -1;
		else
			res[0] = 0;
		if (res[1] > 0)
			res[1] = 1;
		else if (res[1] < 0)
			res[1] = -1;
		else
			res[1] = 0;
}

void broadcast(t_server *server, t_client *client, char *buffer)
{
  t_client *tmp;
  float dist_x;
  float dist_y;
  float x_tmp;
  float y_tmp;
  int res[2];
  float x_client;
  float y_client;
  int soundcase_x;
  int soundcase_y;

  x_client = client->x;
  y_client = client->y;
  tmp = server->first;
  while (tmp != NULL)
  {
    if (tmp->fd != client->fd)
  	{
		  broadcast2(res, client, tmp, server);
      dprintf(tmp->fd, "message %d,%s", find_case_dir(tmp, res[0],
  																								res[1]), &buffer[10]);
  	}
    tmp = tmp->next;
  }
  dprintf(client->fd, "ok\n");
}
