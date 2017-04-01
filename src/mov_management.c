/*
** mov_management.c for lemipc in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 22:59:29 2017 Edouard
** Last update Sat Apr  1 09:05:07 2017 Edouard
*/

#include <stdlib.h>
#include "game.h"

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
	player->posX = POSX(pos[i]);
	player->posY = POSY(pos[i]);
	return (true);
      }
  i = random() % len;
  player->map[pos[i]] = player->team_id;
  player->posX = POSX(pos[i]);
  player->posY = POSY(pos[i]);
  return (true);
}

void	go_to_pos(t_player *player, int pos)
{
  int	dirx;
  int	diry;
  int	lenx;
  int	leny;

  if (pos == -1)
    return ;
  lenx = ABS(POSX(pos) - player->posX);
  leny = ABS(POSY(pos) - player->posY);
  dirx = player->posX > POSX(pos) ? player->posX - 1 : player->posX + 1;
  diry = player->posY > POSY(pos) ? player->posY - 1 : player->posY + 1;
  if (lenx >= leny && lenx >= 1 &&
      check_spot(player->map, dirx, player->posY, player->team_id))
    {
      player->map[POS(player->posX, player->posY)] = 0;
      player->map[POS(dirx, player->posY)] = player->team_id;
      player->posX = dirx;
    }
  else if (leny >= lenx && lenx >= 1 &&
      check_spot(player->map, player->posX, diry, player->team_id))
    {
      player->map[POS(player->posX, player->posY)] = 0;
      player->map[POS(player->posX, diry)] = player->team_id;
      player->posY = diry;
    }
}
