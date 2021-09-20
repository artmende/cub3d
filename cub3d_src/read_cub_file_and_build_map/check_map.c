/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 09:26:55 by artmende          #+#    #+#             */
/*   Updated: 2021/06/01 14:13:35 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	incorrect_NSEW(t_win *win)
{
	int	i;

	i = 0;
	while (i <= win->map.index_max)
	{
		if (ft_strchr("NSEW", win->map.map[i]) && ++i)
		{
			while (i <= win->map.index_max)
			{
				if (ft_strchr("NSEW", win->map.map[i]))
					return (1);
				i++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_map_line(char *l)
{
	while (*l)
	{
		if (!ft_strchr("012NSEW ", *l))
			return (0);
		l++;
	}
	return (1);
}

int	is_only_empty_lines(int fd)
{
	int		gnl;
	char	*l;

	gnl = 1;
	while (gnl && gnl != -1)
	{
		gnl = get_next_line(fd, &l);
		if (gnl == -1 || ft_len_nl(l, 0))
		{
			if (gnl != -1)
				free(l);
			return (0);
		}
		free(l);
	}
	return (1);
}
