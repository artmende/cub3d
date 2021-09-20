/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:01:12 by artmende          #+#    #+#             */
/*   Updated: 2021/06/01 14:01:46 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	update_pos(t_win *win, t_point next, double new_angle)
{
	if (!is_collision(win, next, 0))
	{
		win->px = next.x;
		win->py = next.y;
	}
	else if (!is_collision(win, (t_point){next.x, win->py}, 0))
	{
		win->px = next.x;
	}
	else if (!is_collision(win, (t_point){win->px, next.y}, 0))
	{
		win->py = next.y;
	}
	win->pa = new_angle;
}
