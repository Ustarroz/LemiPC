/*
** listteam.c for lemicp in /home/edouard/Documents/concur/PSU_2016_lemipc
**
** Made by Edouard
** Login   <edouard@epitech.net>
**
** Started on  Fri Mar 31 22:58:21 2017 Edouard
** Last update Fri Mar 31 22:58:28 2017 Edouard
*/

#include <stdlib.h>
#include <stdio.h>
#include "listteam.h"
#include "game.h"

static char	next_symb(char symb)
{
  if (symb == '9')
    return ('A');
  if (symb == 'Z')
    return ('a');
  if (symb == 'z')
    return ('#');
  return (symb + 1);
}

static t_listteam	*new_team(t_listteam **list, int team_id)
{
  t_listteam		*node;
  t_listteam		*tmp;

  if ((node = malloc(sizeof(t_listteam))) == NULL)
    return (NULL);
  node->team_id = team_id;
  node->next = *list;
  node->used = false;
  tmp = *list;
  if (*list == NULL)
    {
      node->symb = '#';
      node->color = RED;
    }
  else if ((node->color = (tmp->color + 1) % NB_COLOR) == RED)
    node->symb = next_symb(tmp->symb);
  else
    node->symb = tmp->symb;
  *list = node;
  return (node);
}

t_listteam	*find_team(t_listteam **list, int team_id)
{
  t_listteam	*tmp;

  tmp = *list;
  while (tmp)
    {
      if (tmp->team_id == team_id)
	return (tmp);
      tmp = tmp->next;
    }
  if ((tmp = new_team(list, team_id)) == NULL)
    return (NULL);
  return (tmp);
}

t_listteam	*print_map(int *map, t_listteam *list, char *color[NB_COLOR])
{
  int		i;
  t_listteam	*tmp;
  char		sep;

  i = -1;
  printf("\033[2J");
  while (++i < MAP_SIZE)
    {
      if (i % COLUMN_NB != COLUMN_NB - 1)
	sep = ' ';
      else
	sep = '\n';
      if (map[i] == 0)
	printf(STR_BLACK"0%c"CLEAR, sep);
      else
	{
	  if ((tmp = find_team(&list, map[i])) == NULL)
	    return (NULL);
	  printf("%s%c%c"CLEAR, color[tmp->color], tmp->symb, sep);
	  tmp->used = true;
	}
    }
  return (list);
}
