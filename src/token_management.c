/*
** token_management.c for lemipc in edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 22:59:39 2017 Edouard
** Last update Sat Apr  1 11:49:39 2017 Edouard
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "manage_team.h"
#include "id_manager.h"

static bool	check_dead(int *map, int posx, int posy, int self_id)
{
  int		sum[4];
  int		i;
  int		j;

  memset(sum, 0, 4);
  if (posx != 0)
    sum[0] = map[POS(posx - 1, posy)];
  if (posy != 0)
    sum[1] = map[POS(posx, posy - 1)];
  if (posx != COLUMN_NB - 1)
    sum[2] = map[POS(posx + 1, posy)];
  if (posy != LINE_NB - 1)
    sum[3] = map[POS(posx, posy + 1)];
  i = -1;
  while (++i < 4)
    if (sum[i] != 0 && sum[i] != self_id)
      {
	j = i;
	while (++j < 4)
	  if (sum[i] == sum[j])
	    return (true);
      }
  return (false);
}

bool	check_spot(int *map, int pos_x, int pos_y, int team_id)
{
  if (pos_x < 0 || pos_x >= COLUMN_NB || pos_y < 0 || pos_y >= COLUMN_NB)
    return (false);
  if (map[POS(pos_x, pos_y)] != 0)
    return (false);
  if (check_dead(map, pos_x, pos_y, team_id))
    return (false);
  return (true);
}

void	move_player(t_player *player)
{
  int	len;
  int	tab[4];
  int	pos;

  len = -1;
  if (check_spot(player->map, player->posX - 1,
		 player->posY, player->team_id))
    tab[++len] = POS(player->posX - 1, player->posY);
  if (check_spot(player->map, player->posX + 1,
		 player->posY, player->team_id))
    tab[++len] = POS(player->posX + 1, player->posY);

  if (check_spot(player->map, player->posX,
		 player->posY - 1, player->team_id))
    tab[++len] = POS(player->posX, player->posY - 1);
  if (check_spot(player->map, player->posX,
		 player->posY + 1, player->team_id))
    tab[++len] = POS(player->posX, player->posY + 1);
  if (len == -1)
    return ;
  pos = tab[random() % (len + 1)];
  player->map[POS(player->posX, player->posY)] = 0;
  player->map[pos] = player->team_id;
  player->posX = POSX(pos);
  player->posY = POSY(pos);
}

static void	cycle_token(t_player *player)
{
  int		pos;

  pos = 0; // to remove
  while (1)
    {
      set_sem(player->semID, PRINT, -1);
      set_sem(player->semID, MAP, -1);
      if (player->map[COLUMN_NB * LINE_NB] == 2 ||
	  check_dead(player->map, player->posX, player->posY, player->team_id))
	{
	  player->map[POS(player->posX, player->posY)] = 0;
	  set_sem(player->semID, MAP, 1);
	  break;
	}
      pos = nearest_foe(player); // to remove
      //pos = player->leader ? nearest_foe(player): receive_pos(player);
      go_to_pos(player, pos);
      set_sem(player->semID, MAP, 1);
      usleep(TIME_SLEEP);
    }
}

void	start_token(t_player *player)
{
  set_sem(player->semID, PRINT, -1);
  set_sem(player->semID, MAP, -1);
  if (!set_first_pos(player))
    {
      set_sem(player->semID, MAP, 1);
      return ;
    }
  if (player->map[COLUMN_NB * LINE_NB] == 0)
    {
      set_sem(player->semID, MAP, 1);
      set_sem(player->semID, START, -1);
    }
  else
    set_sem(player->semID, MAP, 1);
  usleep(TIME_SLEEP);
  cycle_token(player);
}
