/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 06:10:37 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 07:34:59 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	The linked list has been sorted by distance to have the furthest sprite at
	the beginning of the list.
	Some sprites might be further than the wall, so they need to be skipped.
	Then the sprites are drawn on top of each other in the list order.
*/

void	render_sprites(t_win *win)
{
	double			len;
	t_sprite_list	*sprite;

	sprite = win->ray.sprite;
	while (sprite)
	{
		if (sprite->distance > win->ray.len)
		{
			sprite = sprite->next;
			continue ;
		}
		sprite->y = win->resy / 2;
		win->ray.y_depth = 0.5;
		len = (win->square_size * win->resx)
			/ (2 * tan(0.5 * win->fov) * sprite->distance);
		while (sprite->y < win->resy)
		{
			apply_sprite_color(win, &win->ray, sprite);
			sprite->y++;
			if (sprite->y > win->resy / 2 + len / 2)
				break ;
			win->ray.y_depth += (1 / len);
		}
		sprite = sprite->next;
	}
}

/*
	if the sprite texel has a color equal to 0, we don't draw the texel on the
	screen. That allows sprites to have transparency.
*/

void	apply_sprite_color(t_win *win, t_ray *ray, t_sprite_list *sprite)
{
	int	texel;
	int	tex_x;
	int	tex_y;

	tex_x = sprite->x_depth * win->text_s.resx;
	tex_y = ray->y_depth * win->text_s.resy;
	if (tex_x < 0 || tex_y < 0 || tex_x > win->text_s.resx
		|| tex_y > win->text_s.resy)
	{
		return ;
	}
	texel = *(unsigned int *)(win->text_s.addr + (tex_y * win->text_s.sizeline
				+ tex_x * (win->text_s.bitppxl / 8)));
	if (texel)
		my_mlx_pixel_put(&win->bckgrd, sprite->x, sprite->y, texel);
	tex_y = (1 - ray->y_depth) * win->text_s.resy;
	texel = *(unsigned int *)(win->text_s.addr + (tex_y * win->text_s.sizeline
				+ tex_x * (win->text_s.bitppxl / 8)));
	if (texel)
		my_mlx_pixel_put(&win->bckgrd, sprite->x, win->resy - sprite->y, texel);
}
