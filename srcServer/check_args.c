/*
** check_args.c for PSU_2015_zappy
**
** Made by	Matthew LEJEUNE
** Login	lejeun_m
**
** Started on	Mon Jun 13 11:22:09 2016 Matthew LEJEUNE
** Last update Sat Jun 25 15:51:45 2016 David BOIVENT
*/

#include "server.h"

void usage_server() {
	printf("USAGE\n");
	printf("\t./zappy_server -p port -x width -y height -c team_max_players ");
	printf("-n team_1 team_2 ... -t delay\n\n");

	printf("DESCRIPTION\n");
	printf("\t-p numero de port\n");
	printf("\t-x largeur du Monde\n\t-y hauteur du Monde\n");
	printf("\t-c nombre de clients par équipe autorisés au début du jeu\n");
	printf("\t-n nom_de_equipe_1 nom_de_equipe_2 ...\n");
	printf("\t-t delai temporel d’execution des actions\n");
}

int check_args(int ac, char **av)
{
  int index;
  int i_args;
  int found;
  char format[] = "pxynct";

  index = -1;
  while (format[++index] != '\0')
  {
    i_args = -1;
    found = 0;
    while (++i_args < ac)
      if (strncmp(&format[index], &av[i_args][1], 1) == 0)
        found = 1;
    if (found == 0)
    {
      usage_server();
      dprintf(1, "\nMissing argument '%c'\n", format[index]);
      return (-1);
    }
  }
  return (0);
}
