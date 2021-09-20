/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 08:25:17 by artmende          #+#    #+#             */
/*   Updated: 2021/05/29 08:26:52 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_line_pp(t_img *img, t_line_pp line, int color)
{
	double	x;
	double	y;
	double	dvsr;

	x = line.from.x;
	y = line.from.y;
	dvsr = fmax(fabs(line.to.x - line.from.x), fabs(line.to.y - line.from.y));
	while (x >= fmin(line.from.x, line.to.x)
		&& x <= fmax(line.from.x, line.to.x)
		&& y >= fmin(line.from.y, line.to.y)
		&& y <= fmax(line.from.y, line.to.y))
	{
		my_mlx_pixel_put(img, (int)x, (int)y, color);
		if (!dvsr)
			return ;
		x += (line.to.x - line.from.x) / dvsr;
		y += (line.to.y - line.from.y) / dvsr;
	}
}

void	put_line_a(t_img *img, t_line_a line, int color)
{
	t_point	to;

	to.x = line.origin.x + cos(line.angle) * line.length;
	to.y = line.origin.y + sin(line.angle) * line.length;
	put_line_pp(img, (t_line_pp){line.origin, to}, color);
}
