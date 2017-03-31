#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>

int		set_sem(int sem_id,
			short sem_num,
		        short sem_op)
{
  struct sembuf sops;

  printf("here is ----> semop op = %d, sem = %d!!\n", sem_op, sem_num);
  sops.sem_flg = 0;
  sops.sem_num = sem_num;
  sops.sem_op = sem_op;
  return (semop(sem_id, &sops, 1));
}
