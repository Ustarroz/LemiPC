/*
** fct_print.c for bonjour in /vagrant/rendu/systeme_unix/PSU_2016_lemipc/src
**
** Made by Vagrant Default User
** Login   <vagrant@epitech.net>
**
** Started on  Thu Mar 30 13:01:25 2017 Vagrant Default User
** Last update Fri Mar 31 22:57:53 2017 Edouard
*/

#include <stdio.h>
#include <id_manager.h>
#include <unistd.h>
#include "listteam.h"
#include "id_manager.h"
#include "manage_team.h"
#include "game.h"

static void	set_color(char *color[NB_COLOR])
{
  color[RED] = STR_RED;
  color[GREEN] = STR_GREEN;
  color[YELLOW] = STR_YELLOW;
  color[BLUE] = STR_BLUE;
  color[PURPLE] = STR_PURPLE;
  color[CYAN] = STR_CYAN;
  color[WHITE] = STR_WHITE;
  color[BLACK_BOLD] = STR_BLACK_BOLD;
  color[RED_BOLD] = STR_RED_BOLD;
  color[GREEN_BOLD] = STR_GREEN_BOLD;
  color[YELLOW_BOLD] = STR_YELLOW_BOLD;
  color[BLUE_BOLD] = STR_BLUE_BOLD;
  color[PURPLE_BOLD] = STR_PURPLE_BOLD;
  color[CYAN_BOLD] = STR_CYAN_BOLD;
  color[WHITE_BOLD] = STR_WHITE_BOLD;
}

bool		end_of_the_game(t_player *player, int nb_player)
{
  player->map[MAP_SIZE] = 2;
  set_sem(player->semID, PRINT, nb_player);
  return (true);
}

bool		set_after_print(t_player *player, int nb_player, int nb_teams)
{
  bool		end;

  if (nb_teams == 0)
    return (true);
  end = false;
  if (player->map[MAP_SIZE] == 0)
    {
      if (nb_teams > 1)
	{
	  player->map[MAP_SIZE] = 1;
	  set_sem(player->semID, START, nb_player);
	  set_sem(player->semID, PRINT, nb_player);
	}
      else
	set_sem(player->semID, PRINT, 1);
    }
  else if (player->map[MAP_SIZE] == 1)
    {
      if (nb_teams <= 1)
	end = end_of_the_game(player, nb_player);
      else
	set_sem(player->semID, PRINT, nb_player);
    }
  return (end);
}

void		*print_the_game(t_player *tmp)
{
  int		nb_teams;
  int		nb_player;
  bool		end;
  char		*color[NB_COLOR];
  t_listteam	*list;

  end = false;
  set_color(color);
  list = NULL;
  while (!end)
    {
      set_sem(tmp->semID, PRINT, 0);
      usleep(100);
      set_sem(tmp->semID, MAP, -1);
      nb_player = count_players(tmp->map);
      list = print_map(tmp->map, list, color);
      nb_teams = count_clear_teams(&list);
      end = set_after_print(tmp, nb_player, nb_teams);
      set_sem(tmp->semID, MAP, 1);
    }
  set_sem(tmp->semID, PRINT, 0);
  destroy_shared_map(tmp);
  return (NULL);
}
