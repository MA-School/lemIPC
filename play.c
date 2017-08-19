/*
** play.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Fri Mar 31 23:29:06 2017 aubanel_m
** Last update Sun Apr  2 17:34:44 2017 Maxime AUBANEL
*/

#include "LemiPC.h"

int       find_random_pos(int pos, int *map)
{
  int     dir;

  dir = rand() % 4;
  if (dir == 0 && check_free(pos - __MAP_SIZE__, map) == 0
      && map[pos - __MAP_SIZE__] == 0)
    return (pos - __MAP_SIZE__);
  else if (dir == 1 && check_free(pos + __MAP_SIZE__, map) == 0
      && map[pos + __MAP_SIZE__] == 0)
    return (pos + __MAP_SIZE__);
  else if (dir == 2 && check_side(pos, 1, map) == 0 && map[pos + 1] == 0)
    return (pos + 1);
  else if (dir == 3 && check_side(pos, 0, map) == 0 && map[pos - 1] == 0)
    return (pos - 1);
  return (pos);
}

int      check_2_same(int *tab, int team)
{
  int    x;
  int    y;

  y = -1;
  while (++y != 8)
    {
      x = -1;
      while (++x != 8)
        {
          if (x != y
            && tab[y] == tab[x]
            && tab[y] != 0
            && tab[y] != team
            && tab[y] != -1)
            {
              return (0);
            }
        }
    }
  return (-1);
}

int      check_dead(t_player *player, int *map, int sem_id)
{
  int    tab[8];

  Use_sem(sem_id);
  tab[0] = check_free(player->pos - __MAP_SIZE__, map);
  tab[1] = check_free(player->pos - __MAP_SIZE__ - 1, map);
  tab[2] = check_free(player->pos - __MAP_SIZE__ + 1, map);
  tab[3] = check_free(player->pos + __MAP_SIZE__, map);
  tab[4] = check_free(player->pos + __MAP_SIZE__ - 1, map);
  tab[5] = check_free(player->pos + __MAP_SIZE__ + 1, map);
  tab[6] = check_free(player->pos - 1, map);
  tab[7] = check_free(player->pos + 1, map);
  Release_sem(sem_id);
  if (check_2_same(tab, player->team) == 0)
    {
      Use_sem(sem_id);
      map[player->pos] = 0;
      Release_sem(sem_id);
      return (-1);
    }
  return (0);
}

void              Play(t_player *player, t_info *info)
{
  if (player->state != ALIVE)
    return ;
  if (check_dead(player, info->map, info->msg_id) == -1)
    {
      player->state = DEAD;
      sendMsgDeath(player, info->msg_id);
      return ;
    }
  if (Use_sem(info->sem_id) == -1)
    {
      player->state = WINNER;
      return ;
    }
  info->map[player->pos] = 0;
  player->pos = attack_algo(player->pos, info->map, player->team);
  info->map[player->pos] = player->team;
  Release_sem(info->sem_id);
  usleep(100000);
}
