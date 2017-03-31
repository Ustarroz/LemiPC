/*
** game.h for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:52:28 2017 ustarr_r
** Last update Thu Mar 30 17:22:30 2017 Edouard
*/

#ifndef GAME_H_
# define GAME_H_

#include <sys/types.h>
#include <stdbool.h>
#include <sys/sem.h>

#define COLUMN_NB 10
#define LINE_NB 10
#define MAP_SIZE COLUMN_NB * LINE_NB
#define MEM_SIZE (MAP_SIZE + 1) * sizeof(int)
#define POS(x,y) ((x) + (y) * COLUMN_NB)
#define POSX(i) ((i) % COLUMN_NB)
#define POSY(i) ((i) / COLUMN_NB)
#define TIME_SLEEP 300000

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

t_player        *init_player(char *key_path,
			     char *team_number,
			     pthread_t *print);
void		destroy_shared_map(t_player *tmp);
int		count_teams(int *map);
void		print_game(int *map);
int		count_players(int *map);
void		*print_the_game(t_player *tmp);
void		destroy_shared_map(t_player *tmp);

#endif /*!GAME_H_*/
