#ifndef	OBJECT_H
#define	OBJECT_H

#define FD_FREE 0
#define FD_CLIENT 1
#define FD_SERVER 2
#define MAX_FD 255

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE 512

extern char* NameCommand[12];
extern int elevations_required[8][8];
extern char* NameObject[8];

typedef enum	TypeObject {
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	FOOD,
	PLAYER,
	OTHER,
	OUTOFLIMITE
}TypeObject;

typedef enum	TypeCommand {
	WALK,
	RIGHT,
	LEFT,
	LOOK,
	INVENTORY,
	TAKE,
	PUT,
	EXPULSE,
	BROADCAST,
	INCANT,
	FORK,
	CONNECT,
	WRONG
}TypeCommand;

typedef struct Commands {
	char *act_str;
	TypeCommand	actuelle;
	struct Commands	*next;
} Commands;

typedef struct Player {
	int food;
	int level;
	int inv[6];
}Player;

typedef struct	Object{
	int	x;
	int	y;
	TypeObject	type;
}Object;

struct s_env;

typedef void (*fct)(struct s_env*, int);

typedef struct s_env
{
  char fd_type[MAX_FD];
  fct fct_read[MAX_FD];
  fct fct_write[MAX_FD];
  int port;
  char *team;
  char *machine;
} t_env;

int   begin_client(t_env *, struct protoent *, struct timeval);
void  client_fdset(int, fd_set, struct timeval);
int   protocol_client(int, char *);
void  write_client(int, char *);
void  read_client(int, int);
void  basic_take(int, int, int);
void  basic_take2(int, int, Commands *, Commands *);
char  *my_strtok(char *, char, int);
char  *get_line();
void  move_to(TypeCommand);
void Help(char *, int);
int   gotTo(TypeObject **);
int   gotToFood(TypeObject **);
int  message_take_send(int, int);
int  noPlayersInCase(int, int, int, TypeObject **);
void  notYet(int, int items_case[7]);
void  incantOrNot(char *, int);
void  gestion_params_client(char **, t_env *);
int   *take_first_footsteps(int);
int   *take_first_footsteps2(int, int, int *);
void  broadcastIncant(int  items_case[7]);
void  broadcastIncant2();
int   check_requirement();
int  checkCaseForElevation(int, int items_case[7]);
void  usage_client();
void  exec_cmd_pile(int fd);
Commands  *cmdRegister(TypeCommand, Commands *);

// parse
TypeObject  parse_objects(char *);
char        **parse_command(char *);
void        parseInventaire(char *);
char        **parse_case(char *, int);
TypeObject  **parse_see3(char ***, int);
char        **parse_see2(char *);
TypeObject  **parse_see(char *);

// ia
void  ia(char *, int);
void  ia2(char *, int);
void  ia3(char *, int);
void  ia4(char *, int);
void  ia5(char *, int);
void  ia_search(char *, int);
void  defaultSearch(int);
void  ia_evolve(char *, int);
void  ia_evolve_search(char *, int);

#endif
