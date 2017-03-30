#include <sys/types.h>
#include <sys/sem.h>

int		set_sem(int sem_id,
			unsigned short sem_num,
			unsigned short sem_op)
{
  struct sembuf sops;

  sops.sem_flg = 0;
  sops.sem_num = sem_num;
  sops.sem_op = sem_op;
  return (semop(sem_id, &sops, 1));
}
