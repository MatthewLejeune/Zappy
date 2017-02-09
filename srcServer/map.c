/*
** map.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Thu Jun 09 13:02:53 2016 Matthew LEJEUNE
** Last update	Sun Jun 26 18:10:53 2016 Matthew LEJEUNE
*/

#include "server.h"

t_case *create_elem_map(int x, int y) {
  t_case *new_case;

  if ((new_case = malloc(sizeof(t_case))) == NULL)
    return (NULL);
  new_case->nbr_clients = 0;
  new_case->x = x;
  new_case->y = y;
  new_case->elem[FOOD] = 3;
  new_case->elem[LINEMATE] = 0;
  new_case->elem[DERAUMERE] = 0;
  new_case->elem[SIBUR] = 0;
  new_case->elem[MENDIANE] = 0;
  new_case->elem[PHIRAS] = 0;
  new_case->elem[THYSTAME] = 0;
  new_case->clients_on_case = NULL;
  new_case->left = NULL;
  new_case->right = NULL;
  new_case->up = NULL;
  new_case->down = NULL;
  return (new_case);
}

t_case ***create_tab_map(t_server *server)
{
  unsigned int x;
  unsigned int y;
  t_case ***temp_map;

  y = 0;
  if ((temp_map = malloc(sizeof(t_case *) *
      (server->world_height + 1))) == NULL)
    return (NULL);
  memset(temp_map, 0, server->world_height + 1);
  while (y < server->world_height)
  {
    if ((temp_map[y] = malloc(sizeof(t_case) *
        (server->world_width + 1))) == NULL)
      return (NULL);
    x = 0;
    while (x < server->world_width)
    {
      temp_map[y][x] = create_elem_map(x, y);
      x++;
    }
    y++;
  }
  return (temp_map);
}

int *get_real_pos(t_server *server, int x, int y)
{
  int *new_pos;

  if ((new_pos = malloc(sizeof(int) * 2)) == NULL)
    return (NULL);
  if (x < 0)
    new_pos[0] = server->world_width - 1;
  else if (x >= (int)server->world_width)
    new_pos[0] = 0;
  else
    new_pos[0] = x;
  if (y < 0)
    new_pos[1] = server->world_height - 1;
  else if (y >= (int)server->world_height)
    new_pos[1] = 0;
  else
    new_pos[1] = y;
  return (new_pos);
}

t_case ***create_node_map(t_case ***map, t_server *server)
{
  unsigned int x;
  unsigned int y;
  int *new_pos;

  y = -1;
  while (++y < server->world_height)
  {
    x = -1;
    while (++x < server->world_width)
    {
      new_pos = get_real_pos(server, x - 1, y);
      map[y][x]->left = map[new_pos[1]][new_pos[0]];
      free(new_pos);
      new_pos = get_real_pos(server, x, y - 1);
      map[y][x]->up = map[new_pos[1]][new_pos[0]];
      free(new_pos);
      new_pos = get_real_pos(server, x, y + 1);
      map[y][x]->down = map[new_pos[1]][new_pos[0]];
      free(new_pos);
      new_pos = get_real_pos(server, x + 1, y);
      map[y][x]->right = map[new_pos[1]][new_pos[0]];
      free(new_pos);
    }
  }
  return (map);
}

void print_map(t_server *server)
{
  unsigned int ct;
  unsigned int ctd;
  int i;

  for (ct = 0; ct < server->world_height; ct++)
  {
    for (ctd = 0; ctd < server->world_width; ctd++)
    {
      i = 0;
      printf("[");
      if (server->map[ct][ctd]->nbr_clients > 0)
      {
        while (i < server->map[ct][ctd]->nbr_clients)
        {
          printf("%d,", server->map[ct][ctd]->clients_on_case[i]->fd);
          i++;
        }
      }
      else
        printf(" ");
      printf("]");
    }
    printf("\n");
  }
}

t_server *create_map(t_server *server)
{
  t_case ***map;

  map = create_tab_map(server);
  map = create_node_map(map, server);

  server->corner_upleft = map[0][0];
  server->corner_upright = server->corner_upleft->left;
  server->corner_downright = server->corner_upright->up;
  server->corner_downleft = server->corner_downright->right;

  server->map = map;
  print_map(server);
  return (server);
}
