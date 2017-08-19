/*
** Player.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Fri Mar 31 19:05:16 2017 aubanel_m
** Last update Sun Apr  2 17:36:24 2017 Maxime AUBANEL
*/

#include "LemiPC.h"

void              sendMsgMaj(t_player *player, int msg_id)
{
  t_msg           msg;

  bzero(&msg, sizeof(struct s_msg));
  msg.mtype = player->team;
  sprintf(msg.data, "MAAAAJ-%d-%d-%d", player->team, player->id, player->pos);
  msgsnd(msg_id, &msg, sizeof(struct s_msg), 0);
}

void              sendMsgDeath(t_player *player, int msg_id)
{
  t_msg           msg;

  bzero(&msg, sizeof(struct s_msg));
  msg.mtype = player->team;
  sprintf(msg.data, "DELETE-%d-%d-%d", player->team, player->id, player->pos);
  msgsnd(msg_id, &msg, sizeof(struct s_msg), 0);
}

void              sendMsgCreate(int team, int id, int pos, int msg_id)
{
  t_msg           msg;

  bzero(&msg, sizeof(struct s_msg));
  msg.mtype = team;
  sprintf(msg.data, "CREATE-%d-%d-%d", team, id, pos);
  msgsnd(msg_id, &msg, sizeof(struct s_msg), 0);
}

void              END(t_info *info, int team)
{
  shmctl(info->shm_id, IPC_RMID, NULL);
  semctl(info->sem_id, 0, IPC_RMID);
  msgctl(info->msg_id, IPC_RMID, NULL);
  printf("TEAM %d WON !\n", team);
  free (info);
  exit (0);
}

void              Player(t_info *info, int team)
{
  t_player        *player;

  player = malloc(sizeof(t_player));
  player->team = team;
  player->id = getpid();
  player->state = ALIVE;
  player->pos = FindFreespace(info->map, info->sem_id);
  Use_sem(info->sem_id);
  info->map[player->pos] = team;
  Release_sem(info->sem_id);
  sendMsgCreate(player->team, player->id, player->pos, info->msg_id);
  if (info->isFirst == true)
    {
      while (MapHandler(info, player) != -1)
        Play(player, info);
    }
  else
    {
      while (player->state == ALIVE)
        Play(player, info);
    }
  free (player);
}
