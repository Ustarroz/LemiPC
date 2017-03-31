/*
** id_manager.h for lemipc in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 23:30:25 2017 Edouard
** Last update Fri Mar 31 23:30:27 2017 Edouard
*/

#ifndef ID_MANAGER_H_
#define ID_MANAGER_H_

#include <stdbool.h>
#include "game.h"

int	set_sem(int sem_id, unsigned short sem_num, short sem_op);
void	start_token(t_player *player);
bool	set_first_pos(t_player *player);
int	set_sem(int sem_id,
		unsigned short sem_num,
		short sem_op);

#endif /* !ID_MANAGER_H_ */
