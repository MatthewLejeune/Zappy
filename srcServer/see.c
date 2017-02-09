/*
** see.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Fri Jun 10 00:41:35 2016 Matthew LEJEUNE
** Last update Sun Jun 26 18:53:56 2016 David BOIVENT
*/

#include "server.h"

char* Objects[8] = {"nourriture", "linemate", "deraumere", "sibur",
                    "mendiane", "phiras", "thystame", "joueur"};

char *get_items_line(t_client *client, t_case *c, int to_verify, int lvl)
{
  int check;
  static int found = 0;
  char *str;
  t_case *tmp_case;

  check = 0;
  tmp_case = c;
  if ((str = malloc(sizeof(char) * 1024)) == NULL)
    return (NULL);
  memset(str, '\0', 1024);
  while (check < to_verify)
  {
    get_items(&str, to_verify, &found, tmp_case);
    get_player(&str, tmp_case, &found);
    tmp_case = check_move_line(client, tmp_case);
    check++;
    if (lvl != (int)client->level || check < to_verify)
      strcat(str, ",");
  }
  found = 0;
  return (str);
}

t_case *check_move(t_client *client, t_case *actual_case)
{
  if (client->player_direction == UP)
    return (actual_case->up->left);
  else if (client->player_direction == DOWN)
    return (actual_case->down->right);
  else if (client->player_direction == LEFT)
    return (actual_case->left->down);
  else if (client->player_direction == RIGHT)
    return (actual_case->right->up);
  return (NULL);
}

char *look_up(t_client *client, t_case ***map, char **see_str)
{
  unsigned int to_verify;
  unsigned int to_check;
  t_case *tmp_case;

  to_verify = 1;
  to_check = 0;
  tmp_case = map[client->y][client->x];
  while (to_check <= client->level)
  {
    strcat(*see_str, get_items_line(client, tmp_case, to_verify, to_check));
    to_check++;
    to_verify += 2;
    tmp_case = check_move(client, tmp_case);
  }
  return (*see_str);
}

char *get_see(t_client *client, t_server *server)
{
  char *see_str;

  if ((see_str = malloc(sizeof(char) * 2048)) == NULL)
    return (NULL);
  memset(see_str, '\0', 2048);
  see_str[0] = '{';
  look_up(client, server->map, &see_str);
  see_str = strcat(see_str, "}");
  dprintf(client->fd, "%s\n", see_str);
  free(see_str);
  return (NULL);
}
