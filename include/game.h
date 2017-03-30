/*
** game.h for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:52:28 2017 ustarr_r
// Last update Thu Mar 30 13:08:47 2017 Vagrant Default User
*/
#ifndef GAME_H_
# define GAME_H_

#include <sys/ipc.h>
#include <sys/shm.h>

#define COLUMN_NB 10
#define LINE_NB 10
#define MAP_SIZE size(int) * COLUMN_NB * LINE_NB + 8
#define POS(x,y) ((x) + (y) * COLUMN_NB)

typedef struct	s_player
{
  int		team_id;
  key_t		key;
  int		semID;
  int		posX;
  int		posY;
  int		shmID;
  bool		first;
  int		*map;
 }		t_player;

enum sem_type
  {
    MAP = 0,
    PRINT,
    START
  };

void		create_semaphore(t_player *tmp);
int		*init_map(t_player *tmp);
t_player        *init_player(char *key_path, char *team_number, pthread_t *print);
sembuf		*set_sops(int semID, int num, int flags, int operation);
void		destroy_shared_map(t_player *tmp);
int		count_teams(int *map);
void		print_game(int *map);
int		count_players(int *map);
void		print_the_game(t_player *tmp);

#endif /*!GAME_H_*/
