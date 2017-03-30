/*
** fct_print.c for bonjour in /vagrant/rendu/systeme_unix/PSU_2016_lemipc/src
**
** Made by Vagrant Default User
** Login   <vagrant@epitech.net>
**
** Started on  Thu Mar 30 13:01:25 2017 Vagrant Default User
** Last update Thu Mar 30 13:05:46 2017 Vagrant Default User
*/
#include "game.h"

void    destroy_shared_map(t_player *tmp)
{
  shmctl(tmp->shmID, IPC_RMID, NULL);
  semctl(tmp->semID, START, IPC_RMID);
  semctl(tmp->semID, PRINT, IPC_RMID);
  semctl(tmp->semID, MAP, IPC_RMID);
}

int     count_teams(int *map)
{
  int   i;
  int   save;

  i = -1;
  while (map[++j])
    {
      if (map[j] != 0)
	save = map[j];
      if (map[j] != 0 && map[j] != save)
	return (1);
    }
  return (0);
}

void    print_game(int *map)
{
  int   i;

  i = -1;
  while (map[++i])
    {
      if (i % 10 != 0)
	printf("%d ", map[i]);
      else
	printf("%d\n", map[i]);
    }
  printf("\n\n");
}

int     count_players(int *map)
{
  int   i;
  int   count;

  i = -1;
  while (map[++i])
    {
      if (map[i] != 0)
	count++;
    }
  return (count);
}

void    print_the_game(t_player *tmp)
{
  int   nb_teams;
  int   nb_player;
  bool  end;

  end = false;
  while (!end)
    {
      set_sops(tmp->semID, MAP, 0, -1);
      nb_teams = count_teams(tmp->map);
      nb_player = count_players(tmp->map);
      if (nb_teams == 1)
	{
	  end = true;
	  tmp->map[101] = 2;
	}
      else
	print_game(tmp->map);
    }
  destroy_shared_map(tmp);
}
