/*
** sem.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Fri Mar 31 19:11:31 2017 aubanel_m
** Last update Sun Apr  2 05:48:06 2017 Aubanel Maxime
*/

#include "LemiPC.h"

int      Use_sem(int sem_id)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = -1;
  if (semop(sem_id, &sops, 1) == -1)
    return (-1);
  return (0);
}

void      Release_sem(int sem_id)
{
  struct sembuf sops;

  sops.sem_num = 0;
  sops.sem_flg = 0;
  sops.sem_op = 1;
  semop(sem_id, &sops, 1);
}
