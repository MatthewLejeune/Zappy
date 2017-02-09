/*
** see2.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Sun Jun 26 17:43:26 2016 Matthew LEJEUNE
** Last update Sun Jun 26 18:40:25 2016 David BOIVENT
*/

#include "server.h"

t_case *check_move_line(t_client *client, t_case *actual_case)
{
  if (client->player_direction == UP)
    return (actual_case->right);
  else if (client->player_direction == DOWN)
    return (actual_case->left);
  else if (client->player_direction == LEFT)
    return (actual_case->up);
  else if (client->player_direction == RIGHT)
    return (actual_case->down);
  return (NULL);
}

void get_items(char **str, int to_verify, int *found, t_case *tmp_case)
{
  int i;
  unsigned int index;

  i = 0;
  while (i < ELEMS)
  {
    if (tmp_case->elem[i] > 0)
    {
      index = 0;
      while (index < tmp_case->elem[i])
      {
        if (*found == 1)
          strcat(*str, " ");
        strcat(*str, Objects[i]);
        *found = 1;
        index++;
      }
    }
    i++;
  }
}

void get_player(char **str, t_case *tmp_case, int *found)
{
  int nb_joueurs;

  nb_joueurs = 0;
  while (nb_joueurs < tmp_case->nbr_clients)
  {
    if (*found == 1)
      strcat(*str, " ");
    strcat(*str, "joueur");
    *found = 1;
    nb_joueurs++;
  }
}
