/*
** display.c for PSU_2016_lemipc in /home/aubanel_m/tek2/PSU_2016_lemipc
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Sun Apr 02 17:35:21 2017 aubanel_m
** Last update Sat Aug 19 23:44:11 2017 sshSupreme
*/

#include "LemiPC.h"

int               Print_map(int *map, t_info *info)
{
  int             y;
  int             x;

  y = -1;
  (void)map;
  while (++y != __MAP_SIZE__)
    {
      x = -1;
      while (++x != __MAP_SIZE__)
        {
          if (Use_sem(info->sem_id) == -1)
            return (-1);
          // my_putchar(map[(__MAP_SIZE__ * y) + x] + '0');
          Release_sem(info->sem_id);
        }
      // my_putchar('\n');
    }
  // my_putchar('\n');
  // my_putchar('\n');
  return (0);
}
