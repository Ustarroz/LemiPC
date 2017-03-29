#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>

int	main(int ac, char **av)
{
  key_t	key;
  int	shm_id;
  int	sem_id;
  int	*addr;
  struct sembuf sops;

  if (ac < 2)
    {
      fprintf(stderr, "no argument\n");
      return (1);
    }
  key = ftok(av[1], 1);
  shm_id = shmget(key, 42, SHM_R | SHM_W);
  if (shm_id == -1)
    {
      shm_id = shmget(key, 42, IPC_CREAT | SHM_R | SHM_W);
      printf("Created shm segment %d\n", shm_id);
      addr = shmat(shm_id, NULL, SHM_R | SHM_W);
      memset(addr, 0, 42);
      addr[0] = 123;
      addr[1] = 125;
    }
  else
    {
      printf("Using shm segment %d\n", shm_id);
      addr = shmat(shm_id, NULL, SHM_R | SHM_W);
      printf("Result: %d %d\n", addr[0], addr[1]);
      shmctl(shm_id, IPC_RMID, NULL);
    }
  sem_id = semget(key, 1, SHM_R | SHM_W);
  if (sem_id == -1)
    {
      sem_id = semget(key, 1, IPC_CREAT | SHM_R | SHM_W);
      printf("Created sem %d\n", sem_id);
      semctl(sem_id, 0, SETVAL, 4);
    }
  else
    {
      printf("Using sem %d\n", sem_id);
      sops.sem_num = 0;
      sops.sem_flg = 0;
      sops.sem_op = -1;
      semop(sem_id, &sops, 1);
      printf("Get val %d\n", semctl(sem_id, 0, GETVAL));
      if (semctl(sem_id, 0, GETVAL) == 0)
	semctl(sem_id, 0, IPC_RMID, NULL);
    }
  return (0);
}
