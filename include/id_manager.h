#ifndef ID_MANAGER_H_
#define ID_MANAGER_H_

#include <stdbool.h>
#include "game.h"

int	set_sem(int sem_id, unsigned short sem_num, short sem_op);
void	start_token(t_player *player);
bool	set_first_pos(t_player *player);

#endif /* !ID_MANAGER_H_ */
