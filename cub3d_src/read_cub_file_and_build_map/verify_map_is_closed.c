/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map_is_closed.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:11:56 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:40:55 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	verify_map_is_closed(t_win *win)
{
	char	*map_copy;
	int		x_start;
	int		y_start;

	x_start = win->p_index_start % win->map.width;
	y_start = win->p_index_start / win->map.width;
	map_copy = malloc(sizeof(char) * win->map.height * win->map.width);
	if (!map_copy)
		call_exit(win, "Malloc issue !\n");
	ft_memmove(map_copy, win->map.map, win->map.height * win->map.width);
	if (!flood_fill_from_p(win, map_copy, x_start, y_start))
	{
		free(map_copy);
		call_exit(win, "Map is not closed !\n");
	}
	free(map_copy);
}

/*
	Very simple implementation of recursive flood fill algorithm.
	From the player start square, it checks all the 8 squares around it.
	Then each square will check all 8 squares around them too.
	The content of each square checked is modified to not check the same square
	again.

	If only one check returns 0, it means the flood fill failed and the map is
	not closed from the player start position.
*/

int	flood_fill_from_p(t_win *win, char *map, int x, int y)
{
	int	i;

	i = get_index_from_square(win, x, y);
	if (i < 0 || i > win->map.index_max || map[i] == ' ')
		return (display_leak_coordinate(x, y));
	if (map[i] == '1' || map[i] == 'c')
		return (1);
	map[i] = 'c';
	if (flood_fill_from_p(win, map, x + 1, y) == 1
		&& flood_fill_from_p(win, map, x, y + 1) == 1
		&& flood_fill_from_p(win, map, x + 1, y + 1) == 1
		&& flood_fill_from_p(win, map, x - 1, y) == 1
		&& flood_fill_from_p(win, map, x, y - 1) == 1
		&& flood_fill_from_p(win, map, x - 1, y - 1) == 1
		&& flood_fill_from_p(win, map, x + 1, y - 1) == 1
		&& flood_fill_from_p(win, map, x - 1, y + 1) == 1)
	{
		return (1);
	}
	else
		return (0);
}

int	display_leak_coordinate(int x, int y)
{
	write(1, "\nLeak in the map at coordinate ", 31);
	ft_putnbr_fd(x, 1);
	write(1, ":", 1);
	ft_putnbr_fd(y, 1);
	write(1, ".\n", 2);
	return (0);
}
