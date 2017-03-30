/*
** game.h for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:52:28 2017 ustarr_r
** Last update Wed Mar 29 21:19:48 2017 Edouard
*/

#ifndef GAME_H_
# define GAME_H_

#include <sys/types.h>
#include <stdbool.h>

#define COLUMN_NB 10
#define LINE_NB 10
#define MAP_SIZE size(int) * COLUMN_NB * LINE_NB + 8
#define POS(x,y) ((x) + (y) * COLUMN_NB)
#define POSX(i) ((i) % COLUMN_NB)
#define POSY(i) ((i) / COLUMN_NB)

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
    PLAYER
  };

#endif /*!GAME_H_*/
