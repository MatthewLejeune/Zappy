/*
** cmd_list.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Fri Jun 10 12:25:32 2016 David BOIVENT
** Last update	Sat Jun 25 12:46:46 2016 Matthew LEJEUNE
*/

#include "server.h"

void invalid(t_server *server, t_client *client, char *buffer) {
  server = server;
  buffer = buffer;
  write(client->fd, "COMMANDE INVALIDE\n", strlen("COMMANDE INVALIDE\n"));
}

int get_elem_from_name(char *elem)
{
  if (strcmp(elem, "nourriture\n") == 0)
    return (FOOD);
  else if (strcmp(elem, "linemate\n") == 0)
    return (LINEMATE);
  else if (strcmp(elem, "deraumere\n") == 0)
    return (DERAUMERE);
  else if (strcmp(elem, "sibur\n") == 0)
    return (SIBUR);
  else if (strcmp(elem, "mendiane\n") == 0)
    return (MENDIANE);
  else if (strcmp(elem, "phiras\n") == 0)
    return (PHIRAS);
  else if (strcmp(elem, "thystame\n") == 0)
    return (THYSTAME);
  else
    return (-1);
}

t_cmd g_command[] = {
  {"avance\n", 7, move},
  {"droite\n", 7, right},
  {"gauche\n", 7, left},
  {"voir\n", 7, see},
  {"inventaire\n", 7, inventory},
  {"prend", 7, take},
  {"pose", 7, drop},
  {"expulse\n", 7, expulse},
  {"broadcast", 7, broadcast},
  {"incantation\n", 300, incant},
  {"fork\n", 42, reproduce},
  {"connect_nbr\n", 0, connect_slot},
  {"nb\n", 0, nb_joueur},
  {"pos\n", 0, get_pose},
  {"lvl\n", 0, level},
  {NULL, 0, invalid}
};
