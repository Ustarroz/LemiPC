/*
** game.h for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:52:28 2017 ustarr_r
// Last update Sun Mar 26 02:32:57 2017 Vagrant Default User
*/
#ifndef GAME_H_
# define GAME_H_

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
  int	map[100];

}		t_map;


#endif /*!GAME_H_*/
