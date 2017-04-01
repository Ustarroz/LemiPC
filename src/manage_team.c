/*
** manage_team.c for lemipc in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 22:59:17 2017 Edouard
** Last update Sat Apr  1 01:15:41 2017 Edouard
*/

#include <stdlib.h>
#include <sys/msg.h>
#include "game.h"
#include "manage_team.h"

int	count_players(int *map)
{
  int   i;
  int   count;

  i = -1;
  count = 0;
  while (++i < MAP_SIZE)
    {
      if (map[i] != 0)
	count++;
    }
  return (count);
}

static t_listteam	*clear_team(t_listteam **list,
				    t_listteam *tmp,
				    t_listteam *save)
{
  if (save == NULL)
    {
      *list = tmp->next;
      free(tmp);
      return (*list);
    }
  save->next = tmp->next;
  free(tmp);
  return (save->next);
}

int		count_clear_teams(t_listteam **list)
{
  t_listteam	*tmp;
  t_listteam	*save;
  int		nb_team;

  tmp = *list;
  nb_team = 0;
  save = NULL;
  while (tmp)
    if (tmp->used)
      {
	save = tmp;
	tmp->used = false;
	tmp = tmp->next;
	++nb_team;
      }
    else
      tmp = clear_team(list, tmp, save);
  return nb_team;
}

int	send_pos(t_player *leader, int pos)
{
  t_msg	msg;
  int	nb;

  msg.type = leader->team_id;
  msgrcv(leader->msg_id, &msg, sizeof(msg), leader->team_id, IPC_NOWAIT);
  msg.pos = pos;
  nb = msg.nb;
  msg.nb = 0;
  msgsnd(leader->msg_id, &msg, sizeof(msg), 0);
  return (nb);
}

int	nearest_foe(t_player *leader)
{
  int	i;
  int	pos;
  int	len;
  int	save;

  i = -1;
  save = COLUMN_NB + LINE_NB;
  pos = -1;
  while (++i < COLUMN_NB * LINE_NB)
    if (leader->map[i] != 0 && leader->map[i] != leader->team_id)
      {
	len = ABS(POSX(i) - leader->pos_x) + ABS(POSY(i) - leader->pos_y);
	if (len == 1)
	  return (i);
	else if (len < save)
	  {
	    save = len;
	    pos = i;
	  }
      }
  if (send_pos(leader, pos) <= 1)
    return (pos);
  return (POS(POSX(pos) > 2 ? POSX(pos) - 2 : POSX(pos) + 2,
	      POSY(pos) > 2 ? POSY(pos) - 2 : POSY(pos) + 2));
}
