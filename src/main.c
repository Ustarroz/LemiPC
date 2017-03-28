i/*
** main.c for Project-Master in /Users/robinustarroz/rendu/systeme_unix
**
** Made by ustarr_r
** Login   <ustarr_r@epitech.eu>
**
** Started on  Fri Mar 24 16:27:20 2017 ustarr_r
** Last update Sun Mar 26 01:29:51 2017 Vagrant Default User
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>


void	destroy_shared_map(int shm_id)
{
  shmctl(shm_id, IPC_RMID, NULL);
}

t_player	*init_player(char *key_path, char *team_number)
{
  t_player	*tmp;

  if ((tmp = malloc(sizeof(t_player))) == -1)
    {
      fprintf(stderr, "Malloc Error\n");
      return (NULL);
    }
  tmp->team_id = atoi(team_number);
  tmp->posX = 0;
  tmp->posY = 0;
  if ((tmp->key = ftok(key_path, 0)) == -1);
  {
    fprintf(stderr, "Wrong path");
    return (84);
  }
  if ((tmp->shmID = shmget(tmp->key, MAP_SIZE, SHM_R | SHM_W)) == -1)
    tmp->shmID = shmget(tmp->key, MAP_SIZE, IPC_CREAT | SHM_R | SHM_W);
  return (tmp);
}

int	main(int ac, char **av)
{
  key_t		key;
  int		shm_id;
  t_player	*player;

  if (ac != 3)
    {
      if ((player = init_player(av[1], av[3])) == NULL)
	return (84);
    }
  else
    fprintf(stderr, "Wrong usage, expected: [path_to_key] [team_number]");
}
