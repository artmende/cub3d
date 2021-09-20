/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 08:04:06 by artmende          #+#    #+#             */
/*   Updated: 2021/06/01 14:06:42 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_minimap_params(t_win *win)
{
	win->minimap_scale_factor = 0.35;
	win->minimap_grid_color = 0x900000FF;
	win->minimap_block_color = 0x900000FF;
	win->minimap_sprite_color = 0x00419837;
	win->minimap_player_color = 0x00FF0000;
}

void	put_minimap(t_win *win)
{
	put_grid(win, win->minimap_grid_color);
	put_blocks(win, win->minimap_block_color, win->minimap_sprite_color);
	put_player(win, win->minimap_player_color);
}

void	put_grid(t_win *win, int color)
{
	double	x;
	double	y;
	t_point	from;
	t_point	to;

	x = 0;
	while (x < win->map.width * win->minimap_size)
	{
		from = (t_point){x, 0};
		to = (t_point){x, win->map.height * win->minimap_size - 1};
		put_line_pp(&win->bckgrd, (t_line_pp){from, to}, color);
		x += win->minimap_size;
	}
	y = 0;
	while (y < win->map.height * win->minimap_size)
	{
		from = (t_point){0, y};
		to = (t_point){win->map.width * win->minimap_size - 1, y};
		put_line_pp(&win->bckgrd, (t_line_pp){from, to}, color);
		y += win->minimap_size;
	}
}

void	put_blocks(t_win *win, int block_color, int sprite_color)
{
	int		x;
	int		y;
	int		mwidth;
	double	msize;

	mwidth = win->map.width;
	msize = win->minimap_size;
	y = 0;
	while (y < win->map.height)
	{
		x = 0;
		while (x < mwidth)
		{
			if (win->map.map[y * mwidth + x] == '1')
				put_fsquare(&win->bckgrd,
					(t_square){{x * msize, y * msize}, msize}, block_color);
			if (win->map.map[y * mwidth + x] == '2')
				put_fsquare(&win->bckgrd,
					(t_square){{x * msize, y * msize}, msize}, sprite_color);
			x++;
		}
		y++;
	}
}

void	put_player(t_win *win, int color)
{
	t_point	pos_player;

	pos_player.x = win->px * win->minimap_size / win->square_size;
	pos_player.y = win->py * win->minimap_size / win->square_size;
	put_line_a(&win->bckgrd,
		(t_line_a){pos_player, win->pa, 2.5 * win->minimap_size}, color);
	put_fcircle(&win->bckgrd, (t_circle){pos_player, 0.5 * win->minimap_size},
		color);
}
