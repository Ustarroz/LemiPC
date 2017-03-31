#include <sys/types.h>
#include <sys/sem.h>
#include <stdio.h>

int		set_sem(int sem_id,
			unsigned short sem_num,
			short sem_op)
{
  struct sembuf sops;

  switch (sem_num)
    {
    case 0:
      printf("MAP: %d\n", sem_op);
      break;
    case 1:
      printf("PRINT: %d\n", sem_op);
      break;
    case 2:
      printf("START: %d\n", sem_op);
      break;
    }
  sops.sem_flg = 0;
  sops.sem_num = sem_num;
  sops.sem_op = sem_op;
  return (semop(sem_id, &sops, 1));
}
