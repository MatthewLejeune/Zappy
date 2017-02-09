/*
** spawn_ressources.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Fri Jun 24 15:25:56 2016 Matthew LEJEUNE
** Last update Sun Jun 26 18:54:20 2016 David BOIVENT
*/

#include "server.h"

t_server *spawn_ressources(t_server *server)
{
  int y;
  int x;
  int seed;

  y = 0;
  srand((unsigned) time(NULL));
  while (y < server->world_height) {
    x = 0;
    while (x < server->world_width) {
      if ((seed = (rand() % 50)) <= 15) {
        server->map[y][x]->elem[LINEMATE] = rand() % 6;
        server->map[y][x]->elem[DERAUMERE] = rand() % 6;
        server->map[y][x]->elem[SIBUR] = rand() % 6;
      }
      if (seed <= 5)
        server->map[y][x]->elem[MENDIANE] = rand() % 6;
      if (seed <= 2) {
        server->map[y][x]->elem[PHIRAS] = (rand() % 3);
        server->map[y][x]->elem[THYSTAME] = (rand() % 3);
      }
      x++;
    }
    y++;
  }
  return (server);
}
