/*
** map.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Fri Mar 31 20:30:29 2017 aubanel_m
** Last update Sat Aug 19 23:43:42 2017 sshSupreme
*/

#include "LemiPC.h"

void              add_player(t_player *player)
{
  printf("The player : %d from team %d created at pos %d\n",
          player->id, player->team, player->pos);
}

void              remove_player(t_player *player)
{
  printf("The player : %d from team %d died at pos %d\n",
          player->id, player->team, player->pos);
}

void              maj_player(t_player *player)
{
  printf("The player : %d from team %d moved at pos %d\n",
          player->id, player->team, player->pos);
}

int               Parse_info(char *str)
{
  char            **tab;
  t_player        *player;

  player = malloc(sizeof(t_player));
  tab = str_to_word_tab(str, '-');
  player->team = atoi(tab[1]);
  player->id = atoi(tab[2]);
  player->pos = atoi(tab[3]);
  if (strcmp(tab[0], "CREATE") == 0)
    add_player(player);
  else if (strcmp(tab[0], "DELETE") == 0)
    remove_player(player);
  else if (strcmp(tab[0], "MAAAAJ") == 0)
    maj_player(player);
  free(tab[0]);
  free(tab[1]);
  free(tab[2]);
  free(tab[3]);
  free(tab);
  free(player);
  return (0);
}

int               MapHandler(t_info *info, t_player *player)
{
  t_msg           msg;
  int             i;
  int             winner;

  i = 0;
  if (START == 0 && BEGIN_OK(info) == 0)
    START = 1;
  if ((winner = check_end(info)) != 0)
    {
      free (player);
      END(info, winner);
    }
  if (Print_map(info->map, info) == -1)
    return (-1);
  while (i != 100)
    {
      if (msgrcv(info->msg_id, &msg, sizeof(msg), 0, IPC_NOWAIT) != -1)
        {
          if (Parse_info(msg.data) == -1)
            return (-1);
        }
      i = i + 1;
    }
  return (0);
}
