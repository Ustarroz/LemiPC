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
#include <sys/msg.h>
#include "game.h"

void	destroy_shared_map(t_player *tmp)
{
  shmctl(tmp->shm_id, IPC_RMID, NULL);
  semctl(tmp->sem_id, START, IPC_RMID);
  semctl(tmp->sem_id, PRINT, IPC_RMID);
  semctl(tmp->sem_id, MAP, IPC_RMID);
  msgctl(tmp->msg_id, IPC_RMID, NULL);
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
