/*
** mov_management.c for lemipc in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 22:59:29 2017 Edouard
** Last update Sat Apr  1 11:08:09 2017 Edouard
*/

#include <stdlib.h>
#include <sys/msg.h>
#include "manage_team.h"

static int	check_free(t_player *player, int **pos)
{
  int		i;
  int		len;
  int		j;

  i = -1;
  len = 0;
  while (++i < COLUMN_NB * LINE_NB)
    if (player->map[i] == 0)
      ++len;
  if (len == 0 || (*pos = malloc(sizeof(int) * (len + 1))) == NULL)
    return (0);
  i = -1;
  j = 0;
  while (++i < COLUMN_NB * LINE_NB)
    if (player->map[i] == 0)
      {
	(*pos)[j] = i;
	++j;
      }
  return (len);
}

static bool	check_pos_id(t_player *player, int pos)
{
  int		posX;
  int		posY;

  posX = POSX(pos) - 2;
  while (++posX < POSX(pos) + 2)
    if (posX >= 0 && posX < COLUMN_NB)
      {
	posY = POSY(pos) - 2;
	while (++posY < POSY(pos) + 2)
	  if (posY >= 0 && posY < LINE_NB &&
	      player->map[POS(posX, posY)] == player->team_id)
	    return (true);
      }
  return (false);
}

bool	set_first_pos(t_player *player)
{
  int	*pos;
  int	len;
  int	i;

  if ((len = check_free(player, &pos)) == 0)
    return (false);
  i = -1;
  while (++i < len)
    if (check_pos_id(player, pos[i]))
      {
	player->map[pos[i]] = player->team_id;
	player->pos_x = POSX(pos[i]);
	player->pos_y = POSY(pos[i]);
	return (true);
      }
  i = random() % len;
  player->map[pos[i]] = player->team_id;
  player->pos_x = POSX(pos[i]);
  player->pos_y = POSY(pos[i]);
  player->leader = true;
  return (true);
}

int	receive_pos(t_player *player)
{
  t_msg		msg;

  msg.type = player->team_id;
  if (msgrcv(player->msg_id, &msg, sizeof(msg),
	     player->team_id, IPC_NOWAIT) == -1)
    return (-1);
  ++msg.nb;
  msgsnd(player->msg_id, &msg, sizeof(msg), 0);
  return (msg.pos);
}

void	go_to_pos(t_player *player, int pos)
{
  int	dirx;
  int	diry;

  if (pos == -1)
    return (move_player(player));
  dirx = player->pos_x > POSX(pos) ? player->pos_x - 1 : player->pos_x + 1;
  diry = player->pos_y > POSY(pos) ? player->pos_y - 1 : player->pos_y + 1;
  if (ABS(POSX(pos) - player->pos_x) > 1 &&
      check_spot(player->map, dirx, player->pos_y, player->team_id))
    {
      player->map[POS(player->pos_x, player->pos_y)] = 0;
      player->map[POS(dirx, player->pos_y)] = player->team_id;
      player->pos_x = dirx;
    }
  else if (ABS(POSY(pos) - player->pos_y) > 1 &&
      check_spot(player->map, player->pos_x, diry, player->team_id))
    {
      player->map[POS(player->pos_x, player->pos_y)] = 0;
      player->map[POS(player->pos_x, diry)] = player->team_id;
      player->pos_y = diry;
    }
  else
    return (move_player(player));
}
