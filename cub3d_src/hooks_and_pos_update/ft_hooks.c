/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:18:28 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:58:49 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	keyhook(int key, t_win *win)
{
	t_point	next;
	double	new_angle;

	next.x = win->px;
	next.y = win->py;
	new_angle = win->pa;
	select_key_action(win, key, &next, &new_angle);
	update_pos(win, next, new_angle);
	build_frame(win);
	return (0);
}

int	xposehook(t_win *win)
{
	keyhook(0, win);
	return (0);
}

/*
	various_hooks is the function in charge of handling events.

	mlx_hook(win->win_ptr, 2, (1L << 0), keyhook, win); --> detects that a key
	was pressed and call the keyhook function giving key id and win as a
	parameter.
	2, (1L << 0) : Triggers on key press. Can press continuously.
	3, (1L << 1) : Triggers on key release. Have to press many times.

	mlx_hook(win->win_ptr, 33, (1L << 17), red_cross_clicked, win); --> detects
	that the red cross button has been pressed.
	17, (1L << 17) has to be used instead for use in Mac.

	mlx_expose_hook(win->win_ptr, xposehook, win); --> detects that the window
	has been exposed to the screen. It is used to render an image when the
	window is created / maximised, before any key has been pressed.
*/

void	various_hooks(t_win *win)
{
	mlx_hook(win->win_ptr, 2, (1L << 0), keyhook, win);
	mlx_hook(win->win_ptr, 33, (1L << 17), red_cross_clicked, win);
	mlx_expose_hook(win->win_ptr, xposehook, win);
}

int	red_cross_clicked(t_win *win)
{
	ft_memset(&win->error[0], 0, 6);
	call_exit(win, "\ncub3D closed succesfully !\n");
	return (1);
}
