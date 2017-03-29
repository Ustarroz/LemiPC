/*
** main.c for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:27:20 2017 ustarr_r
** Last update Wed Mar 29 15:22:28 2017 Vagrant Default User
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include "game.h"

void	destroy_shared_map(int shm_id)
{
  shmctl(shm_id, IPC_RMID, NULL);
}

void	create_semaphore(t_player *tmp)
{
  tmp->semID = semget(tmp->key, 3, IPC_CREAT | SHM_R | SHM_W);
  semctl(tmp->semID, MAP, SETVAL, 0);
  semctl(tmp->semID, PRINT, SETVAL, 0);
  semctl(tmp->semID, PLAYER, SETVAL, 0);
}

t_player	*init_player(char *key_path, char *team_number, pthread_t *print)
{
  t_player	*tmp;

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
      tmp->map = shmat(tmp->shmID, NULL, SHM_R | SHM_W);
      pthread_create(print, NULL, (void * (*)(void*))&print_the_game, tmp);
      tmp->first = true;
    }
  else
    tmp->map = shmat(tmp->shmID, NULL, SHM_R, SHM_W);
  return (tmp);
 }

void	print_the_game(t_player *tmp)
{

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
