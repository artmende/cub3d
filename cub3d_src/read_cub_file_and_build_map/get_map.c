/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:16:36 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:37:18 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_map_content(t_win *win, char **map_content)
{
	int		i;
	char	*l;

	while (call_gnl(win, win->map.fd2, &l) && win->map.first_line_map--)
		free(l);
	if (win->gnl_return == -1)
	{
		free(map_content);
		call_exit(win, "Error reading cub file !\n");
	}
	map_content[0] = l;
	i = 0;
	while (++i < win->map.height)
	{
		if (!call_gnl(win, win->map.fd2, &l) && win->gnl_return == -1)
		{
			back_free_array(map_content, i - 1);
			call_exit(win, "Error reading cub file !\n");
		}
		map_content[i] = l;
	}
	i--;
	if (!is_only_empty_lines(win->map.fd2) && back_free_array(map_content, i))
		call_exit(win, "Error with map in file !\n");
	(void)(!close(win->map.fd2) && (win->map.fd2 = 0));
}

/*
	fill_map converts the map data from an array that contains all the map lines
	read in the cub file, to a single string.
	It adds spaces at the end of lines to make each map row the same length.
	It "fills" the shorter lines with spaces.

	win->map.width - len can only be a positive value, since map.width is the
	length of the longest line of the map.
*/

void	fill_map(t_win *win, char **map_content)
{
	int	i;
	int	j;
	int	len;

	win->map.map = malloc(sizeof(char) * win->map.height * win->map.width);
	if (!win->map.map)
	{
		back_free_array(map_content, win->map.height);
		call_exit(win, "Malloc issue !\n");
	}
	i = 0;
	j = 0;
	while (i < win->map.height)
	{
		len = ft_len_nl(map_content[i], 0);
		ft_memmove(&win->map.map[j], map_content[i], len);
		j += len;
		ft_memset(&win->map.map[j], ' ', win->map.width - len);
		j += win->map.width - len;
		free(map_content[i]);
		i++;
	}
	free(map_content);
	if (incorrect_NSEW(win))
		call_exit(win, "Incorrect player position !\n");
}

void	check_correct_resolution(t_win *win)
{
	mlx_get_screen_size(win->mlx_ptr, &win->resx_max, &win->resy_max);
	if (win->resx > win->resx_max)
		win->resx = win->resx_max;
	if (win->resy > win->resy_max)
		win->resy = win->resy_max;
	if (win->resx < 105)
	{
		win->resx = 105;
		write(1, "Resolution is too low. Res x was corrected to 105 px.\n", 54);
	}
	if (win->resy < 105)
	{
		win->resy = 105;
		write(1, "Resolution is too low. Res y was corrected to 105 px.\n", 54);
	}
}

/*
	The parameters in the cub file can appear in any order and be separated by
	empty lines.

	To ensure no parameter appear more than once, and no parameter is missing,
	we first create a linked list containing all parameter identifiers that we
	must find.

	So for each line read, we browse the list and for each node of the list,
	we search the line for the identifier of that node.
	When a match has been found, the corresponding node is deleted from the
	list.

	If for a given line, the end of the list is reached and no match has been
	found, it means either that the parameter of that line appears more than
	once in the cub file, or that garbage data is present in the file.

	If when reaching the map part of cub file, there is still a list, it means
	that at least one parameter was missing in the cub file.
*/

void	get_map(t_win *win)
{
	char	**map_content;

	win->map.word_list = init_list_name(win->map.word_list, win->map.list_temp);
	if (!win->map.word_list)
		call_exit(win, "Malloc issue !\n");
	match_line_w_cub_data(win);
	check_correct_resolution(win);
	map_content = malloc(sizeof(char *) * win->map.height);
	if (!map_content)
		call_exit(win, "Malloc issue !\n");
	get_map_content(win, map_content);
	fill_map(win, map_content);
	get_block_size(win);
	get_player_pos(win);
	verify_map_is_closed(win);
}

int	back_free_array(char **array, int i)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
	return (1);
}
