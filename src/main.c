/*
** main.c for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:27:20 2017 ustarr_r
** Last update Fri Mar 31 22:59:02 2017 Edouard
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <pthread.h>
#include "game.h"
#include "id_manager.h"

void	init_map(int *map)
{
  int	i;

  i = -1;
  while (++i < MAP_SIZE)
    map[i] = 0;
  map[MAP_SIZE] = 0;
}

bool	create_first_thread(t_player *tmp, pthread_t *print)
{
  if ((tmp->shmID = shmget(tmp->key, MEM_SIZE, IPC_CREAT | SHM_R | SHM_W))
      == -1)
    return (false);
  if ((tmp->map = shmat(tmp->shmID, NULL, SHM_R | SHM_W)) == NULL)
    {
      shmctl(tmp->shmID, IPC_RMID, NULL);
      return (false);
    }
  init_map(tmp->map);
  if ((tmp->semID = semget(tmp->key, 3, IPC_CREAT | SHM_R | SHM_W)) == -1)
    {
      shmctl(tmp->shmID, IPC_RMID, NULL);
      return (false);
    }
  semctl(tmp->semID, MAP, SETVAL, 1);
  semctl(tmp->semID, PRINT, SETVAL, 1);
  semctl(tmp->semID, START, SETVAL, 0);
  if (pthread_create(print, NULL,
		     (void * (*)(void*))&print_the_game, tmp) != 0)
    {
      destroy_shared_map(tmp);
      return (false);
    }
  tmp->first = true;
  tmp->leader = false;
  return (true);
}

t_player	*check_and_init(char *key_path, char *team_number)
{
  t_player	*tmp;

  if ((tmp = malloc(sizeof(t_player))) == NULL)
    {
      fprintf(stderr, "Malloc Error\n");
      return (NULL);
    }
  if ((tmp->team_id = atoi(team_number)) <= 0)
    {
      fprintf(stderr, "Wrong team\n");
      return (NULL);
    }
  if ((tmp->key = ftok(key_path, 0)) == -1)
    {
      fprintf(stderr, "Wrong path\n");
      return (NULL);
    }
  tmp->first = false;
  return (tmp);
}

t_player	*init_player(char *key_path, char *team_number, pthread_t *print)
{
  t_player	*tmp;

  if ((tmp = check_and_init(key_path, team_number)) == NULL)
    return (NULL);
  if ((tmp->shmID = shmget(tmp->key, MEM_SIZE, SHM_R | SHM_W)) == -1)
    {
      if (create_first_thread(tmp, print) == false)
	{
	  fprintf(stderr, "Can't start the first thread\n");
	  return (NULL);
	}
    }
  else if ((tmp->map = shmat(tmp->shmID, NULL, SHM_R | SHM_W)) == NULL)
    {
      fprintf(stderr, "Can't get shared memory\n");
      return (NULL);
    }
  else if ((tmp->semID = semget(tmp->key, 3, IPC_CREAT | SHM_R | SHM_W)) == -1)
    {
      fprintf(stderr, "Can't get semaphore\n");
      return (NULL);
    }
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
