/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 13:05:28 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:32:57 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_path_length_extension(t_win *win, char *l, int *len)
{
	*len = 0;
	while (l[*len] && l[*len] != ' ')
		(*len)++;
	if (*len < 5 || !ft_strnstr(&l[*len - 4], ".xpm", 4))
		call_exit(win, "Textures and sprite must have xpm format !\n");
	return (1);
}

void	check_color_line_ends_with_only_spaces(t_win *win, char *l)
{
	while (*l)
	{
		if (*l != ' ')
			call_exit(win, "Wrong character in color line.\n");
		l++;
	}
}

void	check_color_line(t_win *win, char *l)
{
	while (*l == ' ')
		l++;
	if ((l[0] == 'C' || l[0] == 'F') && l[1] == ' ')
		l += 2;
	else
		call_exit(win, "Incorrect color !\n");
	while (*l == ' ')
		l++;
	if (!ft_strchr("0123456789", *l) || !*l)
		call_exit(win, "Incorrect color !\n");
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	if (l[0] == ',' && ft_strchr("0123456789", l[1]) && l[1])
		l += 2;
	else
		call_exit(win, "Incorrect color !\n");
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	if (l[0] == ',' && ft_strchr("0123456789", l[1]) && l[1])
		l += 2;
	else
		call_exit(win, "Incorrect color !\n");
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	check_color_line_ends_with_only_spaces(win, l);
}

int	is_correct_color_number(t_win *win, char *l)
{
	int	i;

	i = 0;
	while (l[i] && ft_strchr("0123456789", l[i]))
		i++;
	if (i > 3 || ft_atoi(l) > 255 || !ft_strchr("0123456789", *l) || !*l)
		call_exit(win, "Invalid color in cub file !\n");
	return (1);
}
