/*
** id_manager.c for lemipc in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 22:58:07 2017 Edouard
** Last update Fri Mar 31 23:17:03 2017 Edouard
*/

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stddef.h>
#include "game.h"

void	destroy_shared_map(t_player *tmp)
{
  shmctl(tmp->shmID, IPC_RMID, NULL);
  semctl(tmp->semID, START, IPC_RMID);
  semctl(tmp->semID, PRINT, IPC_RMID);
  semctl(tmp->semID, MAP, IPC_RMID);
}

int		set_sem(int sem_id,
			unsigned short sem_num,
		        short sem_op)
{
  struct sembuf sops;

  sops.sem_flg = 0;
  sops.sem_num = sem_num;
  sops.sem_op = sem_op;
  return (semop(sem_id, &sops, 1));
}
