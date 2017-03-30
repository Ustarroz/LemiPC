/*
** main.c for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:27:20 2017 ustarr_r
** Last update Thu Mar 30 23:19:52 2017 Edouard
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <pthread.h>
#include "game.h"
#include "id_manager.h"

void	create_semaphore(t_player *tmp)
{
  tmp->semID = semget(tmp->key, 3, IPC_CREAT | SHM_R | SHM_W);
  semctl(tmp->semID, MAP, SETVAL, 1);
  semctl(tmp->semID, PRINT, SETVAL, 1);
  semctl(tmp->semID, START, SETVAL, 0);
}

int	*init_map(t_player *tmp)
{
  int	i;

  i = -1;
  tmp->map = shmat(tmp->shmID, NULL, SHM_R | SHM_W);
  while (++i < MAP_SIZE)
    tmp->map[i] = 0;
  tmp->map[MAP_SIZE] = 0;
  return (tmp->map);
}

t_player	*init_player(char *key_path, char *team_number, pthread_t *print)
{
  t_player	*tmp;

  if ((tmp = malloc(sizeof(t_player))) == NULL)
    {
      fprintf(stderr, "Malloc Error\n");
      return (NULL);
    }
  tmp->team_id = atoi(team_number);
  if ((tmp->key = ftok(key_path, 0)) == -1)
    {
      fprintf(stderr, "Wrong path");
      return (NULL);
    }
  tmp->first = false;
  if ((tmp->shmID = shmget(tmp->key, MEM_SIZE, SHM_R | SHM_W)) == -1)
    {
      tmp->shmID = shmget(tmp->key, MEM_SIZE, IPC_CREAT | SHM_R | SHM_W);
      create_semaphore(tmp);
      init_map(tmp);
      pthread_create(print, NULL, (void * (*)(void*))&print_the_game, tmp);
      tmp->first = true;
    }
  else
    tmp->map = shmat(tmp->shmID, NULL, SHM_R | SHM_W);
  return (tmp);
}

int	main(int ac, char **av)
{
  t_player	*player;
  pthread_t	print;

  if (ac == 3)
    {
      srand(time(NULL));
      if ((player = init_player(av[1], av[2], &print)) == NULL)
	return (-1);
      start_token(player);
      if (player->first == true)
	pthread_join(print, NULL);
    }
  else
    fprintf(stderr, "Wrong usage, expected: %s [path_to_key] [team_number]\n",
	    av[0]);
  return (0);
}
