/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_square_circle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 17:30:31 by artmende          #+#    #+#             */
/*   Updated: 2021/05/29 08:26:49 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_square(t_img *img, t_square sqr, int color)
{
	t_point	next_point;

	next_point = sqr.top_left;
	next_point.x += sqr.side_len;
	put_line_pp(img, (t_line_pp){sqr.top_left, next_point}, color);
	sqr.top_left = next_point;
	sqr.top_left.y += sqr.side_len;
	put_line_pp(img, (t_line_pp){next_point, sqr.top_left}, color);
	next_point = sqr.top_left;
	next_point.x -= sqr.side_len;
	put_line_pp(img, (t_line_pp){sqr.top_left, next_point}, color);
	sqr.top_left = next_point;
	sqr.top_left.y -= sqr.side_len;
	put_line_pp(img, (t_line_pp){next_point, sqr.top_left}, color);
}

void	put_fsquare(t_img *img, t_square sqr, int color)
{
	double	cntr_top_x;
	double	y_end;

	cntr_top_x = sqr.top_left.x + sqr.side_len / 2;
	y_end = sqr.top_left.y + sqr.side_len;
	while (sqr.top_left.y <= y_end)
	{
		sqr.top_left.x = cntr_top_x - sqr.side_len / 2;
		while (sqr.top_left.x <= cntr_top_x + sqr.side_len / 2)
		{
			my_mlx_pixel_put(img, sqr.top_left.x, sqr.top_left.y, color);
			sqr.top_left.x++;
		}
		sqr.top_left.y++;
	}
}

void	put_fcircle(t_img *img, t_circle crcl, int color)
{
	double	x;
	double	y;

	y = crcl.center.y - crcl.ray;
	while (y <= crcl.center.y + crcl.ray)
	{
		x = crcl.center.x - crcl.ray;
		while (x <= crcl.center.x + crcl.ray)
		{
			if (get_distance((t_point){x, y}, crcl.center) < crcl.ray)
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_circle(t_img *img, t_circle crcl, double thck, int color)
{
	double	x;
	double	y;

	y = crcl.center.y - crcl.ray;
	while (y <= crcl.center.y + crcl.ray)
	{
		x = crcl.center.x - crcl.ray;
		while (x <= crcl.center.x + crcl.ray)
		{
			if (get_distance((t_point){x, y}, crcl.center) > crcl.ray - thck
				&& get_distance((t_point){x, y}, crcl.center) < crcl.ray + thck)
				my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}
