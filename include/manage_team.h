/*
** manage_team.h for lemipc in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 23:31:08 2017 Edouard
** Last update Sat Apr  1 09:06:34 2017 Edouard
*/

#ifndef MANAGE_TEAM_H_
#define MANAGE_TEAM_H_

#include "game.h"
#include "listteam.h"

typedef struct	s_msg
{
  long 		type;
  int 		pos;
  int 		nb;
} t_msg;

int	count_clear_teams(t_listteam **list);
int     count_players(int *map);
int	nearest_foe(t_player *leader);
void	move_player(t_player *player);
void	go_to_pos(t_player *player, int pos);
int	receive_pos(t_player *player);
int	send_pos(t_player *leader, int pos);

#endif /* !MANAGE_TEAM_H_ */
