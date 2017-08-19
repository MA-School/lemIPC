/*
** algo.c for PSU_2016_lemipc in /home/aubanel_m/tek2/PSU_2016_lemipc
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Sun Apr 02 00:35:19 2017 aubanel_m
** Last update Sun Apr  2 16:23:31 2017 Aubanel Maxime
*/

#include "LemiPC.h"

int       check_free(int pos, int *map)
{
  if (pos > __MAP_SIZE__ * __MAP_SIZE__ || pos < 0)
    return (-1);
  if (map[pos] != 0)
    return (map[pos]);
  return (0);
}

int       check_side(int pos, int dir, int *map)
{
  int     reste;

  reste = __MAP_SIZE__ - (pos % __MAP_SIZE__) - 1;
  if (dir == 1 && reste == 0)
    return (-1);
  if (dir == 0 && reste == __MAP_SIZE__ - 1)
    return (-1);
  if (map[pos] != 0)
    return (map[pos]);
  return (0);
}

int                 find_ennemy_side(int pos, int *map, int team)
{
  int               x;
  int               ret;

  x = -1;
  while (((ret = check_side(pos - ++x, 0, map)) != -1) && x <= __RANGE__)
    {
      if (ret != team && ret != 0 && check_side(pos - 1, 0, map) == 0
          && map[pos - 1] == 0)
        return (pos - 1);
    }
  x = -1;
  while (((ret = check_side(++x + pos, 1, map)) != -1) && x <= __RANGE__)
    {
      if (ret != team && ret != 0 && check_side(pos + 1, 1, map) == 0
          && map[pos + 1] == 0)
        return (pos + 1);
    }
  return (-1);
}

int                 find_ennemy(int pos, int *map, int team)
{
  int               x;
  int               ret;

  x = -1;
  while (((ret = check_free(pos - (++x * __MAP_SIZE__), map)) != -1)
        && x <= __RANGE__)
    {
      if (ret != team && ret != 0 && check_free(pos - __MAP_SIZE__, map) == 0
          && map[pos - __MAP_SIZE__] == 0)
        return (pos - __MAP_SIZE__);
    }
  x = -1;
  while (((ret = check_free(pos + (++x * __MAP_SIZE__), map)) != -1)
        && x <= __RANGE__)
    {
      if (ret != team && ret != 0 && check_free(pos + __MAP_SIZE__, map) == 0
          && map[pos + __MAP_SIZE__] == 0)
        return (pos + __MAP_SIZE__);
    }
  return (find_ennemy_side(pos, map, team));
}

int                 attack_algo(int pos, int *map, int team)
{
  int               new_pos;

  new_pos = find_ennemy(pos, map, team);
  if (new_pos == -1 || map[new_pos] != 0)
    new_pos = find_random_pos(pos, map);
  return (new_pos);
}
