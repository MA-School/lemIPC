/*
** displaySFML.c for PSU_2016_lemipc in /home/aubanel_m/tek2/PSU_2016_lemipc/bonus
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Thu Mar 30 14:10:45 2017 aubanel_m
** Last update Sun Apr  2 16:28:15 2017 Aubanel Maxime
*/

#include "Graphic.h"
#include "LemiPC.h"

void  Set_color(sfRectangleShape *rectangle, int team)
{
  if (team == 1)
    sfRectangleShape_setFillColor(rectangle, sfWhite);
  else if (team == 2)
    sfRectangleShape_setFillColor(rectangle, sfGreen);
  else if (team == 3)
    sfRectangleShape_setFillColor(rectangle, sfBlue);
  else if (team == 4)
    sfRectangleShape_setFillColor(rectangle, sfYellow);
  else if (team == 5)
    sfRectangleShape_setFillColor(rectangle, sfCyan);
  else if (team == 6)
    sfRectangleShape_setFillColor(rectangle, sfRed);
  else if (team == 7)
    sfRectangleShape_setFillColor(rectangle, sfMagenta);
  else if (team == 8)
    sfRectangleShape_setFillColor(rectangle, sfBlack);
  else if (team == 9)
    sfRectangleShape_setFillColor(rectangle, sfBlack);
  else if (team == 10)
    sfRectangleShape_setFillColor(rectangle, sfBlack);
}

int   Draw_Map_Extend(t_draw *draw, int *map, sfRectangleShape *rect,
                      sfRenderWindow *window)
{
  int   x;
  int   y;

  y = -1;
  while (++y != __MAP_SIZE__)
    {
      x = -1;
      draw->pos.x = 0;
      while (++x != __MAP_SIZE__)
        {
          if (Use_sem(draw->sem_id) == -1)
            return (-1);
          if (map[(__MAP_SIZE__ * y) + x] == 0)
            sfRectangleShape_setFillColor(rect, sfBlack);
          else
            Set_color(rect, map[(__MAP_SIZE__ * y) + x]);
          Release_sem(draw->sem_id);
          sfRectangleShape_setPosition(rect, draw->pos);
          sfRenderWindow_drawRectangleShape(window, rect, NULL);
          draw->pos.x += draw->size.x;
        }
      draw->pos.y += draw->size.y;
    }
  return (0);
}

int   Draw_Map(sfRenderWindow *window, int *map, int sem_id)
{
  sfVector2f  size;
  size.x = SCREEN_WIDTH / __MAP_SIZE__;
  size.y = SCREEN_HEIGHT / __MAP_SIZE__;
  sfVector2f  pos;
  pos.x = 0;
  pos.y = 0;
  t_draw      draw;

  sfRectangleShape* rect;
  rect =  sfRectangleShape_create();
  sfRectangleShape_setSize(rect, size);
  sfRectangleShape_setFillColor(rect, sfBlack);
  draw.sem_id = sem_id;
  draw.size = size;
  draw.pos = pos;
  if (Draw_Map_Extend(&draw, map, rect, window) == -1)
    return (-1);
  return (0);
}

int Launch_Board(int *map, int sem_id)
{
  sfVideoMode mode = {SCREEN_HEIGHT, SCREEN_WIDTH, 32};
  sfRenderWindow* window;
  sfEvent event;

  window = sfRenderWindow_create(mode, "LemiPC", sfResize | sfClose, NULL);
  while (sfRenderWindow_isOpen(window))
    {
      while (sfRenderWindow_pollEvent(window, &event))
        {
          if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
          if (event.type == sfEvtKeyPressed && event.key.code == sfKeyEscape)
            sfRenderWindow_close(window);
        }
      sfRenderWindow_clear(window, sfBlack);
      if (Draw_Map(window, map, sem_id) == -1)
        {
          sfRenderWindow_destroy(window);
          return (0);
        }
      sfRenderWindow_display(window);
    }
  sfRenderWindow_destroy(window);
  return (0);
}

int main(int ac, char **av)
{
  int shm_id;
  int sem_id;
  int *map;
  int key;

  if (ac != 2)
    {
      printf("Usage : %s \"pwd\"\n", av[0]);
      return (0);
    }
  key = ftok(av[1], 0);
  shm_id = shmget(key, sizeof(__MAP_SIZE__ * __MAP_SIZE__), SHM_R | SHM_W);
  sem_id = semget(key, 1, SHM_R | SHM_W);
  if (shm_id == -1)
    {
      printf("No shared memory segment detected\n");
      return (-1);
    }
  map = shmat(shm_id, NULL, SHM_R | SHM_W);
  Launch_Board(map, sem_id);
  return (0);
}
