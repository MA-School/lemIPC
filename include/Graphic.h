/*
** Graphic.h for PSU_2016_lemipc in /home/aubanel_m/tek2/PSU_2016_lemipc/include
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Sat Apr 01 21:10:12 2017 aubanel_m
** Last update Sat Aug 19 23:05:29 2017 sshSupreme
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

typedef struct    s_draw
{
  int             sem_id;
  sfVector2f      size;
  sfVector2f      pos;
}									t_draw;
