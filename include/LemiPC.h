/*
** LemiPC.h for PSU_2016_lemipc in /home/aubanel_m/tek2/PSU_2016_lemipc
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Mon Mar 27 16:25:24 2017 aubanel_m
** Last update Sun Apr  2 17:54:26 2017 Aubanel Maxime
*/

#ifndef _LEMIPC_H_
# define _LEMIPC_H_

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/msg.h>
#include <string.h>

#define __MAP_SIZE__ 50
#define __RANGE__    70

int      START;

typedef enum state {
  ALIVE,
  DEAD,
  WINNER
} t_state;

typedef struct  s_info
{
  int*          map;
  int           shm_id;
  int           sem_id;
  int           msg_id;
  int           isFirst;
}               t_info;

typedef struct s_player
{
  int               team;
  int               id;
  int               pos;
  t_state           state;
}							      t_player;

typedef struct s_msg
{
  long         mtype;
  char         data[20];
}__attribute__((__packed__))	  			     t_msg;

void            Player(t_info*, int);
int             Use_sem(int);
void            Release_sem(int);
int             FindFreespace(int *map, int sem_id);
int             MapHandler(t_info*, t_player*);
void            Play(t_player *player, t_info *info);
char          	**str_to_word_tab(char *str, char divide);
void            sendMsgMaj(t_player *player, int msg_id);
int             check_end(t_info*);
int             BEGIN_OK(t_info*);
int             check_end(t_info *info);
void            END(t_info *info, int);
int             check_free(int pos, int *map);
int             find_random_pos(int pos, int *map);
int             attack_algo(int pos, int *map, int team);
int             check_side(int pos, int dir, int *map);
void            sendMsgDeath(t_player *player, int msg_id);
void            my_putchar(char c);
int             Print_map(int *map, t_info *info);

#endif
