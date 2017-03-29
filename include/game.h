/*
** game.h for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:52:28 2017 ustarr_r
** Last update Tue Mar 28 10:47:06 2017 Edouard
*/
#ifndef GAME_H_
# define GAME_H_

#define COLUMN_NB 10
#define LINE_NB 10
#define POS(x,y) ((x) + (y) * COLUMN_NB)
#define SHM_ID 1
#define SEM_ID 2
#define SEM_ID 3

typedef struct	s_player
{
  int	team_id;
  key_t	key;
  int	semID;
  int	posX;
  int	posY;
  int	shmID;
}		t_player;

typedef struct	s_map
{
  int	**map;

}		t_map;


#endif /*!GAME_H_*/
