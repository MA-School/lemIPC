/*
** position.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Fri Mar 31 19:56:06 2017 aubanel_m
** Last update Sun Apr  2 00:41:45 2017 Aubanel Maxime
*/

#include "LemiPC.h"

int               FindFreespace(int *map, int sem_id)
{
  int             pos;

  pos = rand() % (__MAP_SIZE__ * __MAP_SIZE__);
  Use_sem(sem_id);
  if (map[pos] == 0)
    {
      Release_sem(sem_id);
      return (pos);
    }
  Release_sem(sem_id);
  return (FindFreespace(map, sem_id));
}
