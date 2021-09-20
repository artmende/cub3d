/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_line_w_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:30:51 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:38:30 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	associate_line_w_var(t_win *win, char *l)
{
	char	*name;

	name = win->map.list_temp->name;
	if (name[0] == 'R' && name[1] == ' ')
		parse_res(win, l);
	else if (name[0] == 'N' && name[1] == 'O')
		parse_path(win, l, &win->map.no);
	else if (name[0] == 'S' && name[1] == 'O')
		parse_path(win, l, &win->map.so);
	else if (name[0] == 'E' && name[1] == 'A')
		parse_path(win, l, &win->map.ea);
	else if (name[0] == 'W' && name[1] == 'E')
		parse_path(win, l, &win->map.we);
	else if (name[0] == 'S' && name[1] == ' ')
		parse_path(win, l, &win->map.s);
	else if (name[1] == ' ' && (name[0] == 'C' || name[0] == 'F'))
	{
		check_color_line(win, l);
		parse_f_c_color(win, l, name[0]);
	}
}

/*
	find_match returns 1 if : match has been found or line is empty.
	returns 0 if : line is not empty AND there is no match.
	(no list means no match).
*/

int	find_match(t_win *win, char *l)
{
	int	len;

	len = ft_len_nl(l, 0);
	if (!len)
		return (1);
	win->map.list_temp = win->map.word_list;
	while (win->map.list_temp)
	{
		if (ft_strnstr(l, win->map.list_temp->name, len))
		{
			associate_line_w_var(win, l);
			delete_entry_list(&win->map.word_list, win->map.list_temp->name);
			return (1);
		}
		win->map.list_temp = win->map.list_temp->next;
	}
	return (0);
}

/*
	match_line_w_cub_data : Going out of the main loop means that keyword has
	not been found, or there is no list anymore, or there was a reading issue.
	find_match can return 0 if the list is complete,
	or if no item of the list could be matched with l.

	At the end of the loop, *l contains the first line of the map.
	We store the number of that line for the next reading of the cub file.
*/

void	match_line_w_cub_data(t_win *win)
{
	char	*l;

	while (call_gnl(win, win->map.fd1, &l) && find_match(win, l))
	{
		free(l);
		win->map.first_line_map++;
	}
	if (win->gnl_return == -1)
		call_exit(win, "Error reading cub file !\n");
	if (!is_map_line(l))
	{
		free(l);
		call_exit(win, "Error in cub file !\n");
	}
	win->map.height = 1;
	win->map.width = ft_len_nl(l, 0);
	free(l);
	get_map_width_height(win);
	if (win->map.word_list)
		call_exit(win, "Missing data in cub file.\n");
}
