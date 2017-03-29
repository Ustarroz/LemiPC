/*
** game.h for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:52:28 2017 ustarr_r
// Last update Wed Mar 29 14:53:09 2017 Vagrant Default User
*/
#ifndef GAME_H_
# define GAME_H_

#define COLUMN_NB 10
#define LINE_NB 10
#define MAP_SIZE size(int) * COLUMN_NB * LINE_NB + 8
#define POS(x,y) ((x) + (y) * COLUMN_NB)

typedef struct	s_player
{
  int	team_id;
  key_t	key;
  int	semID;
  int	posX;
  int	posY;
  int	shmID;
  bool	first;
}		t_player;

enum sem_type
  {
    MAP = 0,
    PRINT,
    PLAYER
  };

typedef struc	s_map
{
  int	*map;
  int	teams;
}		t_map;

#endif /*!GAME_H_*/
