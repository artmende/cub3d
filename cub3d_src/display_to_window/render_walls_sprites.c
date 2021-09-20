/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:21:10 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 07:37:34 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	For each vertical band of the window (each x within win->resx),
	two rays are casted. Each ray grows until hitting a wall, or the map border.
	One ray will look for vertical hit, the other for horizontal hit.
	The shortest distance of those 2 rays is kept as the ray length for this x.

	On their way, they might find a sprite. (In the function is_collision).
	When a sprite is found, a new node in the linked list "sprite" is created.
	All the info necessary to render the sprite on this x of the window is
	saved in the linked list node.
*/

void	render_walls_sprites(t_win *win)
{
	win->ray.x = 0;
	win->ray.angle = win->pa - win->fov / 2;
	while (win->ray.x < win->resx)
	{
		win->ray.sprite = 0;
		cast_ray(win, &win->ray);
		render_walls(win);
		if (win->ray.sprite)
		{
			render_sprites(win);
			free_sprite_lst(win->ray.sprite);
		}
		win->ray.x++;
		win->ray.angle = win->pa + atan((win->ray.x - win->resx / 2)
				/ (0.5 * win->resx / tan(0.5 * win->fov)));
	}
}

/*
	len is the height of the part of wall / sprite to display.

	The complicated formula is set so a block always looks square.
	The cos part is there to compensate the fish bowl effect.

	it's interresting to see that (without looking at the cos part), the only
	variable is win->ray.len. It means that the wall / sprite height is
	inversely proportional to its distance from the player. All the rest is
	constant for all rays.

	The window is browsed from the middle to the edges in both direction
	simultaneously.
*/

void	render_walls(t_win *win)
{
	int		y;
	double	len;

	len = (win->square_size * win->resx)
		/ (2 * tan(0.5 * win->fov) * cos(win->ray.angle - win->pa)
			* win->ray.len);
	y = win->resy / 2;
	win->ray.y_depth = 0.5;
	while (y < win->resy)
	{
		apply_texture_color(win, &win->ray, (t_point){win->ray.x, y});
		y++;
		if (y > win->resy / 2 + len / 2)
			break ;
		win->ray.y_depth += (1 / len);
	}
}

void	apply_texture_color(t_win *win, t_ray *ray, t_point p)
{
	if (ray->n_s_e_w == 'n')
		extract_texture_color(win, &win->text_no, ray, p);
	else if (ray->n_s_e_w == 's')
		extract_texture_color(win, &win->text_so, ray, p);
	else if (ray->n_s_e_w == 'e')
		extract_texture_color(win, &win->text_ea, ray, p);
	else
		extract_texture_color(win, &win->text_we, ray, p);
}

void	extract_texture_color(t_win *win, t_img *texture, t_ray *ray, t_point p)
{
	int	texel;
	int	tex_x;
	int	tex_y;

	tex_x = ray->x_depth * texture->resx;
	tex_y = ray->y_depth * texture->resy;
	if (tex_x < 0 || tex_y < 0 || tex_x > texture->resx
		|| tex_y > texture->resy)
	{
		return ;
	}
	texel = *(unsigned int *)(texture->addr
			+ (tex_y * texture->sizeline + tex_x * (texture->bitppxl / 8)));
	my_mlx_pixel_put(&win->bckgrd, p.x, p.y, texel);
	tex_y = (1 - ray->y_depth) * texture->resy;
	texel = *(unsigned int *)(texture->addr
			+ (tex_y * texture->sizeline + tex_x * (texture->bitppxl / 8)));
	my_mlx_pixel_put(&win->bckgrd, p.x, win->resy - p.y, texel);
}
