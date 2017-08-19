/*
** check.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Sat Apr 01 00:47:54 2017 aubanel_m
** Last update Sun Apr  2 05:41:52 2017 Aubanel Maxime
*/

#include "LemiPC.h"

int check_end(t_info *info)
{
  int     team;
  int     i;
  int     z;

  i = -1;
  z = 0;
  team = 0;
  if (START == 0)
    return (0);
  Use_sem(info->sem_id);
  while (++i != __MAP_SIZE__ * __MAP_SIZE__)
    {
      if (z == 0 && info->map[i] != 0)
        {
          z = 1;
          team = info->map[i];
        }
      if (z == 1 && info->map[i] != 0 && info->map[i] != team)
        {
          Release_sem(info->sem_id);
          return (0);
        }
    }
  Release_sem(info->sem_id);
  return (team);
}

int  BEGIN_OK(t_info *info)
{
  int     team;
  int     i;
  int     z;

  i = 0;
  z = 0;
  team = 0;
  Use_sem(info->sem_id);
  while (i != __MAP_SIZE__ * __MAP_SIZE__)
    {
      if (z == 0 && info->map[i] != 0)
        {
          z = 1;
          team = info->map[i];
        }
      if (z == 1 && info->map[i] != 0 && info->map[i] != team)
        {
          Release_sem(info->sem_id);
          return (0);
        }
      i = i + 1;
    }
  Release_sem(info->sem_id);
  return (-1);
}
