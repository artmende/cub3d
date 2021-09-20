/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_libft_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:08:57 by artmende          #+#    #+#             */
/*   Updated: 2021/06/01 14:09:42 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	ft_atoi has been modified a little bit to fit the norm v3 of 42 school.
	In case of a number outside of the range of a long int, the function is
	supposed to return 0 or -1.
	It has been set to always return -1 in such a case. It is safe to do so in
	this project.
*/

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			minus;
	long int	result_l;

	i = 0;
	j = 0;
	minus = 1;
	result_l = 0;
	while (str[j] == ' ' || (str[j] >= 9 && str[j] <= 13))
		j++;
	if (str[i + j] == '-' || str[i + j] == '+')
	{
		if (str[i + j] == '-')
			minus = minus - 2;
		i++;
	}
	while (str[i + j] >= '0' && str[i + j] <= '9')
	{
		result_l = 10 * result_l + str[i + j] - '0';
		if (result_l < 0 || (i > 18 && minus == 1) || (i > 19 && minus == -1))
			return (-1);
		i++;
	}
	return ((int)(minus * result_l));
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	i;
	char			temp[10];

	if (!n)
		write(fd, "0", 1);
	if (n < 0)
		write(fd, "-", 1);
	i = 0;
	while (n)
	{
		if (n > 0)
			temp[i++] = (n % 10) + '0';
		else
			temp[i++] = -(n % 10) + '0';
		n = n / 10;
	}
	while (i--)
		write(fd, &temp[i], 1);
}
