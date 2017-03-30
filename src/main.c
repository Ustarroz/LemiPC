/*
** main.c for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:27:20 2017 ustarr_r
** Last update Thu Mar 30 13:08:50 2017 Vagrant Default User
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "game.h"

void	create_semaphore(t_player *tmp)
{
  tmp->semID = semget(tmp->key, 3, IPC_CREAT | SHM_R | SHM_W);
  semctl(tmp->semID, MAP, SETVAL, 1);
  semctl(tmp->semID, PRINT, SETVAL, 0);
  semctl(tmp->semID, START, SETVAL, 1);
}

int	*init_map(t_player *tmp)
{
  int	i = -1;
  int	map[MAP_SIZE];

  tmp->map = shmat(tmp->shmID, NULL, SHM_R | SHM_W);
  while (++i != 100)
    map[i] = 0;
  map[101] = 0;
  return (map);
}

t_player	*init_player(char *key_path, char *team_number, pthread_t *print)
{
  t_player	*tmp;
  int		map[101];

  if ((tmp = malloc(sizeof(t_player))) == -1)
    {
      fprintf(stderr, "Malloc Error\n");
      return (NULL);
    }
  tmp->team_id = atoi(team_number);
  if ((tmp->key = ftok(key_path, 0)) == -1);
  {
    fprintf(stderr, "Wrong path");
    return (NULL);
  }
  tmp->first = false;
  if ((tmp->shmID = shmget(tmp->key, MAP_SIZE, SHM_R | SHM_W)) == -1)
    {
      tmp->shmID = shmget(tmp->key, MAP_SIZE, IPC_CREAT | SHM_R | SHM_W);
      create_semaphore(tmp);
      tmp->map = init_map(tmp);
      pthread_create(print, NULL, (void * (*)(void*))&print_the_game, tmp);
      tmp->first = true;
    }
  else
    tmp->map = shmat(tmp->shmID, NULL, SHM_R, SHM_W);
  return (tmp);
}

sembuf	*set_sops(int semID, int num, int flags, int operation)
{
  struct sembuf	tmp;

  tmp.sem_num = num;
  tmp.sem_flags = flags;
  tmp.sem.operation = operation;
  semop(semID, &sops, 1);
  return (&tmp);
}

int	main(int ac, char **av)
{
  key_t		key;
  int		shm_id;
  t_player	*player;
  pthread_t	print;

  if (ac != 3)
    {
      srand();
      if ((player = init_player(av[1], av[3], &print)) == NULL)
	return (-1);
      if (player->first == true)
	pthread_join(print, NULL);
    }
  else
    fprintf(stderr, "Wrong usage, expected: [path_to_key] [team_number]");
  return (0);
}
