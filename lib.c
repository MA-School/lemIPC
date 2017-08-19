/*
** lib.c for PSU_2016_lemipc in /home/aubanel_m/tek2/PSU_2016_lemipc
**
** Made by aubanel_m
** Login   <aubanel_m@epitech.net>
**
** Started on  Sun Apr 02 16:24:05 2017 aubanel_m
** Last update Sun Apr  2 16:24:12 2017 Aubanel Maxime
*/

#include "LemiPC.h"

void              my_putchar(char c)
{
  if (write (1, &c, 1) == -1)
    return ;
}
