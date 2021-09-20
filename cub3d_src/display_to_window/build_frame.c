/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 06:15:42 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:14:23 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	build_frame(t_win *win)
{
	fill_img_half_half(&win->bckgrd, win->map.ceiling_color,
		win->map.floor_color);
	render_walls_sprites(win);
	if (win->minimap_display_or_not % 2)
		put_minimap(win);
	if (win->save_to_bmp == 1)
	{
		create_bmp_screenshot(win);
		ft_memset(&win->error[0], 0, 6 * sizeof(char));
		call_exit(win, "\nScreenshot saved successfully !\n");
	}
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->bckgrd.img, 0, 0);
}

void	fill_img_half_half(t_img *img, int colorup, int colordown)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->resy / 2)
	{
		x = 0;
		while (x < img->resx)
		{
			my_mlx_pixel_put(img, x, y, colorup);
			x++;
		}
		y++;
	}
	while (y < img->resy)
	{
		x = 0;
		while (x < img->resx)
		{
			my_mlx_pixel_put(img, x, y, colordown);
			x++;
		}
		y++;
	}
}
