/*
** cmd_elev.c for PSU_2015_zappy in /home/boivent/B4/1.UnixProg/PSU_2015_zappy/srcClient
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Sun Jun 26 18:42:40 2016 David BOIVENT
** Last update Jun 26 18:42:44 2016
*/

#include "object.h"

char* NameCommand[12] =
{
	"avance\n",
	"droite\n",
	"gauche\n",
	"voir\n",
	"inventaire\n",
	"prend ",
	"pose ",
	"expulse\n",
	"broadcast ",
	"incantation\n",
	"fork\n",
	"connect_nbr\n"
};

int elevations_required[8][8] = {
									{1, 0, 0, 0, 0, 0, 1, -1},
									{1, 1, 1, 0, 0, 0, 2, -1},
									{2, 0, 1, 0, 2, 0, 2, -1},
									{1, 1, 2, 0, 1, 0, 4, -1},
									{1, 2, 1, 3, 0, 0, 4, -1},
									{1, 2, 3, 0, 1, 0, 6, -1},
									{2, 2, 2, 2, 2, 1, 6, -1}
								};

char* NameObject[8] =
{
	"linemate",
	"deraumere",
	"sibur",
	"mendiane",
	"phiras",
	"thystame",
	"nourriture",
	"joueur"
};
