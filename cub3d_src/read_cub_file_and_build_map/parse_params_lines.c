/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 13:50:00 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:40:14 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	parse_res(t_win *win, char *l)
{
	while (*l == ' ')
		l++;
	if (*l == 'R')
		l++;
	else
		call_exit(win, "Incorrect resolution !\n");
	while (*l == ' ')
		l++;
	if (!ft_strchr("0123456789", *l) || !*l)
		call_exit(win, "Incorrect resolution !\n");
	win->resx = ft_atoi(l);
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	while (*l == ' ')
		l++;
	if (!ft_strchr("0123456789", *l) || !*l)
		call_exit(win, "Incorrect resolution !\n");
	win->resy = ft_atoi(l);
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	while (*(l++))
		if (*(l - 1) != ' ')
			call_exit(win, "Incorrect resolution !\n");
}

void	parse_path(t_win *win, char *l, char **address)
{
	int		len;
	int		i;
	char	*path_start;

	while (*l == ' ')
		l++;
	len = ft_len_nl(win->map.list_temp->name, 0);
	i = 0;
	while (i++ < len)
		if (l[i - 1] != win->map.list_temp->name[i - 1])
			call_exit(win, "Wrong texture path !\n");
	l += len;
	while (*l == ' ')
		l++;
	(void)((path_start = l) && check_path_length_extension(win, l, &len));
	l += len;
	while (*(l++))
		if (*(l - 1) != ' ')
			call_exit(win, "Wrong texture path !\n");
	*address = malloc(sizeof(char) * (len + 1));
	if (*address)
		(void)(ft_memmove(*address, path_start, len) && ((*address)[len] = 0));
	else
		call_exit(win, "Malloc issue !\n");
}

void	parse_f_c_color(t_win *win, char *l, char f_or_c)
{
	int	r;
	int	g;
	int	b;

	if (f_or_c == 'F')
		while (ft_strchr("F ", *l) && *l)
			l++;
	if (f_or_c == 'C')
		while (ft_strchr("C ", *l) && *l)
			l++;
	(void)(is_correct_color_number(win, l) && (r = ft_atoi(l)));
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	if (*l == ',')
		l++;
	(void)(is_correct_color_number(win, l) && (g = ft_atoi(l)));
	while (ft_strchr("0123456789", *l) && *l)
		l++;
	if (*l == ',')
		l++;
	(void)(is_correct_color_number(win, l) && (b = ft_atoi(l)));
	if (f_or_c == 'F')
		win->map.floor_color = 65536 * r + 256 * g + b;
	if (f_or_c == 'C')
		win->map.ceiling_color = 65536 * r + 256 * g + b;
}
