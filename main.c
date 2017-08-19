/*
** main.c for new in /home/aubanel_m/tek2/PSU_2016_lemipc/new
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Fri Mar 31 17:37:47 2017 aubanel_m
** Last update Sun Apr  2 17:40:43 2017 Aubanel Maxime
*/

#include "LemiPC.h"

int               Parser(int ac, char **av)
{
  if (ac != 3 || atoi(av[2]) <= 0 || atoi(av[2]) >= 8)
    {
      printf("Usage : %s \"pwd\" unsigned_int\n", av[0]);
      return (-1);
    }
  return (0);
}

t_info*           firstInfo(key_t key)
{
  t_info          *info;

  info = malloc(sizeof(t_info));
  info->shm_id = shmget(key, sizeof(int) * (__MAP_SIZE__ * __MAP_SIZE__),
                SHM_R | SHM_W | IPC_CREAT);
  info->sem_id = semget(key, 1, SHM_R | SHM_W | IPC_CREAT);
  info->msg_id = msgget(key, SHM_R | SHM_W | IPC_CREAT);
  info->map = shmat(info->shm_id, NULL, SHM_R | SHM_W);
  bzero(info->map, __MAP_SIZE__ * __MAP_SIZE__);
  info->isFirst = true;
  START = 0;
  semctl(info->sem_id, 0, SETVAL, 1);
  return (info);
}

t_info*           fillInfo(char *path)
{
  key_t		       key;
  t_info          *info;

  if ((key = ftok(path, 0)) == -1)
    return (NULL);
  info = malloc(sizeof(t_info));
  if ((info->shm_id = shmget(key, sizeof(int) * (__MAP_SIZE__ * __MAP_SIZE__),
                      SHM_R | SHM_W)) == -1)
    {
      free (info);
      return (firstInfo(key));
    }
  if ((info->sem_id = semget(key, 1, SHM_R | SHM_W)) == -1)
      {
        free(info);
        return (NULL);
      }
  if ((info->msg_id = msgget(key, SHM_R | SHM_W)) == -1)
    {
      free(info);
      return (NULL);
    }
  info->map = shmat(info->shm_id, NULL, SHM_R | SHM_W);
  info->isFirst = false;
  return (info);
}

int								main(int ac, char **av)
{
  t_info          *info;
  int             team;
  struct timeval	t1;

  gettimeofday(&t1, NULL);
  srand(t1.tv_usec * t1.tv_sec);
  if (Parser(ac, av) == -1)
    return (-1);
  team = atoi(av[2]);
  info = fillInfo(av[1]);
  if (info == NULL)
    return (-1);
  Player(info, team);
  free (info);
  return (0);
}
