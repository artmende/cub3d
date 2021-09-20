/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 15:51:13 by artmende          #+#    #+#             */
/*   Updated: 2021/05/30 06:36:44 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	cast_ray(t_win *win, t_ray *ray)
{
	t_point	cross_ver;
	t_point	cross_hor;
	t_point	posp;

	posp = (t_point){win->px, win->py};
	get_cross_ver(win, posp, ray, &cross_ver);
	get_cross_hor(win, posp, ray, &cross_hor);
	if (get_distance(posp, cross_ver) > get_distance(posp, cross_hor))
	{
		ray->to = cross_hor;
		ray->n_s_e_w = 's';
		(void)(ray->h_n_s == 'n' && (ray->n_s_e_w = 'n'));
	}
	else
	{
		ray->to = cross_ver;
		ray->n_s_e_w = 'e';
		(void)(ray->v_e_w == 'w' && (ray->n_s_e_w = 'w'));
	}
	ray->len = get_distance(posp, ray->to);
	calculate_texture_x_depth(win, ray);
	if (ray->sprite)
		sort_sprites_by_distance(ray, 0, 0);
}

/*
	sin(ray->angle) > 0 means that we look down, which means the surface that 
	we will see is facing north.

	cos(ray->angle) > 0 means that we look to the right, so surface facing west.

	We check each ray intersection with the grid until we find a collision.
*/

void	get_cross_hor(t_win *win, t_point p, t_ray *ray, t_point *cross)
{
	if (sin(ray->angle) > 0)
	{
		ray->h_n_s = 'n';
		(*cross).y = (int)(p.y / win->square_size) *win->square_size
			+ win->square_size;
		(*cross).x = p.x + (fabs((*cross).y - p.y) / tan(ray->angle));
		while (!is_collision(win, (t_point){(*cross).x, (*cross).y + 1}, ray))
		{
			(*cross).y += win->square_size;
			(*cross).x += win->square_size / tan(ray->angle);
		}
	}
	else
	{
		ray->h_n_s = 's';
		(*cross).y = (int)(p.y / win->square_size) *win->square_size;
		(*cross).x = p.x - (fabs((*cross).y - p.y) / tan(ray->angle));
		while (!is_collision(win, (t_point){(*cross).x, (*cross).y - 1}, ray))
		{
			(*cross).y -= win->square_size;
			(*cross).x -= win->square_size / tan(ray->angle);
		}
	}
}

void	get_cross_ver(t_win *win, t_point p, t_ray *ray, t_point *cross)
{
	if (cos(ray->angle) > 0)
	{
		ray->v_e_w = 'w';
		(*cross).x = ((int)(p.x / win->square_size) *win->square_size)
			+ win->square_size;
		(*cross).y = p.y + (fabs((*cross).x - p.x) * tan(ray->angle));
		while (!is_collision(win, (t_point){(*cross).x + 1, (*cross).y}, ray))
		{
			(*cross).x += win->square_size;
			(*cross).y += win->square_size * tan(ray->angle);
		}
	}
	else
	{
		ray->v_e_w = 'e';
		(*cross).x = (int)(p.x / win->square_size) *win->square_size;
		(*cross).y = p.y - (fabs((*cross).x - p.x) * tan(ray->angle));
		while (!is_collision(win, (t_point){(*cross).x - 1, (*cross).y}, ray))
		{
			(*cross).x -= win->square_size;
			(*cross).y -= win->square_size * tan(ray->angle);
		}
	}
}

int	is_collision(t_win *win, t_point point, t_ray *ray)
{
	int		i;

	i = get_index_from_point(win, point);
	if (!is_in_map(win, point) || win->map.map[i] == '1')
		return (1);
	if (win->map.map[i] == '2' && ray)
		colision_with_sprite(win, ray, i);
	return (0);
}

/*
	x_depth is a factor between 0 and 1 indicating how far we are inside of the
	texture.
*/

void	calculate_texture_x_depth(t_win *win, t_ray *ray)
{
	if (ray->n_s_e_w == 's' || ray->n_s_e_w == 'n')
	{
		ray->x_depth = (ray->to.x
				- ((int)(ray->to.x / win->square_size) *win->square_size))
			/ win->square_size;
		if (ray->n_s_e_w == 'n')
			ray->x_depth = 1 - ray->x_depth;
	}
	else
	{
		ray->x_depth = (ray->to.y
				- ((int)(ray->to.y / win->square_size) *win->square_size))
			/ win->square_size;
		if (ray->n_s_e_w == 'e')
			ray->x_depth = 1 - ray->x_depth;
	}
}
