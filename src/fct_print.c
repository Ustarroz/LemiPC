/*
** fct_print.c for bonjour in /vagrant/rendu/systeme_unix/PSU_2016_lemipc/src
**
** Made by Vagrant Default User
** Login   <vagrant@epitech.net>
**
** Started on  Thu Mar 30 13:01:25 2017 Vagrant Default User
** Last update Fri Mar 31 16:07:10 2017 Edouard
*/

#include <stdio.h>
#include <sys/shm.h>
#include <id_manager.h>
#include <unistd.h>
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
  int   j;
  int   save;

  j = -1;
  save = -1;
  while (++j < MAP_SIZE)
    {
      if (map[j] != 0 && save == -1)
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
  printf("\033[2J");
  while (++i < MAP_SIZE)
    {
      if (i % COLUMN_NB != COLUMN_NB - 1)
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
  count = 0;
  while (++i < MAP_SIZE)
    {
      if (map[i] != 0)
	count++;
    }
  return (count);
}

void    *print_the_game(t_player *tmp)
{
  int   nb_teams;
  int   nb_player;
  bool	end;

  end = false;
  while (!end)
    {
      printf("print to 0 \n");
      set_sem(tmp->semID, PRINT, 0);
      usleep(100);
      set_sem(tmp->semID, MAP, -1);
      nb_teams = count_teams(tmp->map);
      nb_player = count_players(tmp->map);
      print_game(tmp->map);
      if (tmp->map[MAP_SIZE] == 0)
	{
	  if (nb_teams == 1)
	    {
	      tmp->map[MAP_SIZE] = 1;
	      set_sem(tmp->semID, START, nb_player);
	      set_sem(tmp->semID, PRINT, nb_player);
	    }
	  else
	    {
	      printf("Print goes to 1 \n");
	      set_sem(tmp->semID, PRINT, 1);
	    }
	}
      else
	{
	  if (nb_teams == 0)
	    {
	      tmp->map[MAP_SIZE] = 2;
	      set_sem(tmp->semID, PRINT, nb_player);
	      end = true;
	    }
	  else
	    set_sem(tmp->semID, PRINT, nb_player);
	}
      set_sem(tmp->semID, MAP, 1);
    }
  set_sem(tmp->semID, PRINT, 0);
  printf("End of the game\n");
  destroy_shared_map(tmp);
  return (NULL);
}
