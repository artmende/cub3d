/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   various_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:32:53 by artmende          #+#    #+#             */
/*   Updated: 2021/06/01 06:05:11 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > img->resx || y < 0 || y > img->resy)
		return ;
	dst = img->addr + (y * img->sizeline + x * (img->bitppxl / 8));
	*(unsigned int *)dst = color;
}

double	get_distance(t_point a, t_point b)
{
	return (sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)));
}

int	get_index_from_point(t_win *win, t_point point)
{
	if (point.x >= win->map.width * win->square_size)
		return (-1);
	if (point.y >= win->map.height * win->square_size)
		return (-1);
	if (point.x < 0 || point.y < 0)
		return (-1);
	return ((int)((point.y) / win->square_size) *win->map.width
				+ (int)(point.x / win->square_size));
}

int	get_index_from_square(t_win *win, int x, int y)
{
	t_point	point;

	point.x = x * win->square_size + 0.5 * win->square_size;
	point.y = y * win->square_size + 0.5 * win->square_size;
	return (get_index_from_point(win, point));
}

int	is_in_map(t_win *win, t_point point)
{
	if (get_index_from_point(win, point) < 0
		|| get_index_from_point(win, point) >= win->map.height * win->map.width)
		return (0);
	return (1);
}
