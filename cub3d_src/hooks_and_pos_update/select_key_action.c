/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_key_action.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 10:58:22 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:58:55 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	Key id :
	65307 : Esc
	119 : w
	115 : s
	97 : a
	100 : d
	65361 : left arrow
	65362 : up arrow
	65363 : right arrow
	65364 : down arrow
	32 : space bar
	61 : +
	45 : -
	91 : brackets open
	93 : brackets close
*/

void	select_key_action(t_win *win, int key, t_point *next, double *new_angle)
{
	no_movement_key_press(win, key);
	if (key == 119 || key == 65362)
	{
		(*next).x += win->pxspeed * cos(*new_angle);
		(*next).y += win->pxspeed * sin(*new_angle);
	}
	if (key == 115 || key == 65364)
	{
		(*next).x -= win->pxspeed * cos(*new_angle);
		(*next).y -= win->pxspeed * sin(*new_angle);
	}
	if (key == 97)
	{
		(*next).x += win->pxspeed * cos(*new_angle - win->pi_2);
		(*next).y += win->pxspeed * sin(*new_angle - win->pi_2);
	}
	if (key == 100)
	{
		(*next).x += win->pxspeed * cos(*new_angle + win->pi_2);
		(*next).y += win->pxspeed * sin(*new_angle + win->pi_2);
	}
	if (key == 65361)
		*new_angle -= win->angspeed;
	if (key == 65363)
		*new_angle += win->angspeed;
}

void	no_movement_key_press(t_win *win, int key)
{
	if (key == 65307)
	{
		ft_memset(&win->error[0], 0, 6);
		call_exit(win, "\ncub3D closed succesfully !\n");
	}
	if (key == 32)
		win->minimap_display_or_not++;
	if (key == 61)
		win->minimap_size += 1;
	if (key == 45)
		win->minimap_size -= 1;
	if (key == 91 || key == 93)
	{
		(void)(key == 93 && (win->fov += win->pi / 180));
		(void)(key == 91 && (win->fov -= win->pi / 180));
		write(1, "Field of view : ", 16);
		ft_putnbr_fd((int)(win->fov * 180 / win->pi), 1);
		write(1, " degrees.\n", 10);
	}
}
