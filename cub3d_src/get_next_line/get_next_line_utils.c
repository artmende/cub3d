/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 11:13:16 by artmende          #+#    #+#             */
/*   Updated: 2021/05/31 09:03:48 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

/*
**	With a non null flag, ft_len_nl locates a new line in string str,
**	or returns -1 if none is found.
**	With a null flag, it returns the string length.
*/

int	ft_len_nl(char *str, int flag)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		if (flag && str[i] == '\n')
			return (i);
		i++;
	}
	if (flag)
		return (-1);
	else
		return (i);
}

/*
**	The malagain function allocates enough memory for a copy of string from and
**	len bytes of string add. It does the copy and returns a pointer to it.
**	It also frees the memory pointed by from.
*/

char	*malagain(char *from, char *add, int len)
{
	int		i;
	int		j;
	char	*ret;

	if (len == -1)
		return ((char *)((unsigned long)error_free_ptr(&from)));
	i = 0;
	if (from)
		i = ft_len_nl(from, 0);
	ret = malloc(sizeof(char) * (i + len + 1));
	if (!ret)
		return ((char *)((unsigned long)error_free_ptr(&from)));
	ret[i + len] = 0;
	if (from)
	{
		i = -1;
		while (from[++i])
			ret[i] = from[i];
		free(from);
	}
	j = 0;
	while (j < len)
		ret[i++] = add[j++];
	return (ret);
}

int	error_free_ptr(char **ptr)
{
	free(*ptr);
	*ptr = 0;
	return (-1);
}

int	alloc_buf(char **buf)
{
	*buf = malloc(sizeof(char) * BUF_SIZE);
	if (*buf)
		return (1);
	else
		return (0);
}

int	call_malagain(char **ret, char *from, char *add, int len)
{
	*ret = malagain(from, add, len);
	if (*ret)
		return (1);
	else
		return (0);
}
