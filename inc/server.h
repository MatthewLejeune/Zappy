/*
** client_list.c for PSU_2015_myirc in /home/boivent/B4/1.UnixProg/PSU_2015_myirc/srcServer
**
** Made by David BOIVENT
** Login   <boivent@epitech.net>
**
** Started on  Fri May 20 10:31:25 2016 David BOIVENT
** Last update Jun 26 18:39:57 2016
*/

#ifndef _SERVER_H_
#define _SERVER_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#include <pthread.h>

#define LIFE_UNIT 10
#define TIME_UNIT 126

#define SIZE_BUFF 2048
#define ELEMS 7

#define FD_SERVER 3
#define MAX_FD 30

#define SET 0
#define ISSET 1

#define RED				"\033[31m"
#define GREEN			"\033[32m"
#define YELLOW		"\033[33m"
#define DARKBLUE	"\033[34m"
#define PINK			"\033[35m"
#define TEAL			"\033[36m"

#define NORMAL		"\033[0m"

typedef enum DIR { UP, RIGHT, DOWN, LEFT } DIR;

typedef enum ELEMENTS {
	FOOD,
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME
} ELEMENTS;

extern char* Objects[8];

extern unsigned int elevations[8][7];

typedef struct s_server t_server;
typedef struct s_client t_client;
typedef struct s_egg t_egg;

typedef struct s_squad {

	int id;
	int nb_players;
	int max_client;
	char *team_name;

	struct s_squad *next;
	struct s_squad *prev;

} t_squad;

typedef struct s_stack {
  int fd;
  int x;
  int y;
  char *cmd;
  int64_t end_time;
  void (*f)(t_server *, t_client *, char *);
  void (*e)(t_server *, t_egg *, char *);
  struct s_stack *next;
} t_stack;

typedef struct s_client {

  unsigned int x;
  unsigned int y;

  unsigned int life_units;
  unsigned int time_units;
  unsigned int elem[ELEMS];

  DIR player_direction;

  char fd;
  char buffer[SIZE_BUFF];

	t_squad *squad;

	unsigned int level;
	int64_t t;

  struct sockaddr_in client_sin;
  unsigned int client_sin_len;

	t_stack *client_stack;

  struct s_client *next;
  struct s_client *prev;

} t_client;

typedef struct s_egg {
	int hatch;

	unsigned int x;
	unsigned int y;

	char fd;
	char buffer[SIZE_BUFF];

	DIR player_direction;
	t_squad *squad;

	t_stack *egg_stack;

	struct s_egg *next;
	struct s_egg *prev;
} t_egg;

typedef struct s_case {

  int nbr_clients;
  int x;
  int y;

  unsigned int elem[ELEMS];

  t_client **clients_on_case;

  struct s_case *left;
  struct s_case *right;
  struct s_case *up;
  struct s_case *down;
} t_case;

typedef struct s_server {

  int port;
  int fd;
  int s;
  struct sockaddr_in sin;

  struct timeval tv;

  int nb_client;
  struct s_client *first;
  struct s_client *last;

  struct s_squad *first_squad;
  struct s_squad *last_squad;

  struct s_egg *first_egg;
  struct s_egg *last_egg;

	unsigned int world_height;
	unsigned int world_width;

	unsigned int frequency;

	unsigned int max_client_per_squad;

	t_case ***map;

  t_case *corner_upleft;
  t_case *corner_downleft;
  t_case *corner_upright;
  t_case *corner_downright;
} t_server;

typedef struct s_cmd {

  char *cmd;
	unsigned int t;
  void (*func)(t_server *, t_client *, char *);

} t_cmd;

extern t_cmd g_command[];
extern t_stack *g_exec_pile;
extern t_stack *g_egg_pile;

int check_args(int, char **);
void usage_server();
int parse_squad(t_server **, char **);
int parse_opt(char**, t_server **);

int start_server(t_server *);
t_server *init_server(int);
t_server *add_client(t_server *);
t_server *add_egg(t_server *, t_client *);
void add_team(t_server **server, char *, int);
void add_team_from_team(t_client **, t_squad **);
int count_team(t_server *);
t_server *remove_client(int, t_server *);
t_server *remove_egg(unsigned int, unsigned int, t_server *);
t_server *client_from_egg(t_server *, t_client *, t_egg *);
t_egg *egg_in_team(t_server *, t_client *);
t_server *client_read(t_server *, int);
t_server *fd_settings(t_server *, fd_set *, int);
t_client *get_client_from_name(t_server *, char *);
char *concat_message(t_client *);
void write_everywhere(t_server *, char *, t_client *, int);
void get_cmd(char *, t_client *, t_server *);
int check_msg(char *);
int create_server(int);
void write_to_someone(t_client *, t_client *, char *);

t_server *create_map(t_server *);

void push_back_stack(t_stack **, t_server *, t_client *);
void push_back_eggstack(t_stack **, t_server *, t_egg *);
t_stack *create_egg_stack(t_server *, t_egg *);
int push_back_stack_from_elem(t_server *, t_stack **, t_stack *);
void print_stack();
t_stack *pop_stack(t_stack **, int);
t_stack *pop_eggstack(t_stack **, int, int);
int count_elem_stack_per_fd(t_stack *, int);

t_case *push_client_case(t_case *, t_client *);
t_case *pop_client_case(t_case *);
t_case *out_client_case(t_case *, t_client *);
t_client *get_client(t_server *, int);
t_egg *get_egg(t_server *server, int, int);

int *get_real_pos(t_server *, int, int);
void print_map(t_server *);
char *get_inventory(unsigned int[ELEMS]);
char *get_see(t_client *, t_server *);

int64_t get_actual_time();
int64_t get_final_time(int, char *);
void exec_cmd_time(t_server *);

t_server *check_loose_life(t_server *);

// protocol
t_server *protocol_server(t_server *);
t_server *protocol_send(t_server *, char *);
t_server *protocol_valid(t_server *, t_squad *);
t_server *protocol_error(t_server *);

// cmd
int get_elem_from_name(char *);

void move(t_server *, t_client *, char *);
void right(t_server *, t_client *, char *);
void left(t_server *, t_client *, char *);
void see(t_server *, t_client *, char *);
void inventory(t_server *, t_client *, char *);
void take(t_server *, t_client *, char *);
void drop(t_server *, t_client *, char *);
void expulse(t_server *, t_client *, char *);
void broadcast(t_server *, t_client *, char *);
void incant(t_server *, t_client *, char *);
void reproduce(t_server *, t_client *, char *);
void connect_slot(t_server *, t_client *, char *);

// TEST cmd

void nb_joueur(t_server *, t_client *, char *);
void hatch(t_server *, t_egg *, char *);
int tablen(t_client **);
void get_pose(t_server *, t_client *, char *);
void level(t_server *, t_client *, char *);

t_server *spawn_ressources(t_server *);
t_case *check_move_line(t_client *, t_case *);

#endif
