/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_about_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 06:48:13 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:33:24 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_width_height(t_win *win)
{
	char	*l;

	while (win->gnl_return)
	{
		call_gnl(win, win->map.fd1, &l);
		if (win->gnl_return == -1)
			call_exit(win, "Error reading cub file.\n");
		if (!ft_len_nl(l, 0) || !is_map_line(l))
		{
			free (l);
			break ;
		}
		win->map.width = fmax(win->map.width, ft_len_nl(l, 0));
		win->map.height++;
		free(l);
	}
	win->map.index_max = (win->map.width * win->map.height) - 1;
	(void)(!close(win->map.fd1) && (win->map.fd1 = 0));
}

void	get_block_size(t_win *win)
{
	win->square_size = fmin(((double)win->resx / win->map.width),
			(double)win->resy / win->map.height);
	win->minimap_size = win->square_size * win->minimap_scale_factor;
}

double	get_p_angle(t_win *win, char c)
{
	if (c == 'N')
		return (-1 * win->pi_2);
	else if (c == 'S')
		return (win->pi_2);
	else if (c == 'E')
		return (0);
	else
		return (win->pi);
}

void	get_player_pos(t_win *win)
{
	int	i;

	i = 0;
	while (i <= win->map.index_max)
	{
		if (ft_strchr("NSEW", win->map.map[i]))
		{
			win->p_index_start = i;
			win->px = ((i % win->map.width) + 0.5) * win->square_size;
			win->py = ((i / win->map.width) + 0.5) * win->square_size;
			win->pa = get_p_angle(win, win->map.map[i]);
		}
		i++;
	}
}
