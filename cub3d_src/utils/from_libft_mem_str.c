/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_libft_mem_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:19:44 by artmende          #+#    #+#             */
/*   Updated: 2021/06/01 14:09:29 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_e;

	if (!dest && !src)
		return (0);
	dest_e = (unsigned char *)dest;
	if (((char *)dest - (char *)src) > 0)
	{
		dest_e = dest_e + n;
		while (dest != dest_e && n)
		{
			dest_e--;
			*dest_e = *(dest_e - ((char *)dest - (char *)src));
		}
	}
	if (((char *)dest - (char *)src) < 0)
	{
		while (n)
		{
			*dest_e = *(dest_e - ((char *)dest - (char *)src));
			dest_e++;
			n--;
		}
	}
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	c_e;
	unsigned char	*edit;

	c_e = (unsigned char)c;
	edit = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		edit[i] = c_e;
		i++;
	}
	return (s);
}

char	*ft_strnstr(char *str, char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (to_find[0] == 0)
		return (str);
	while (str[i] && i < len)
	{
		if (str[i] == to_find[0])
		{
			while (str[i + j] == to_find[j] && i + j < len)
			{
				if (to_find[j + 1] == 0)
					return (&str[i]);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	c_e;
	char	*s_e;

	c_e = (char)c;
	s_e = (char *)s;
	i = 0;
	while (s[i])
	{
		if (s[i] == c_e)
			return (&s_e[i]);
		i++;
	}
	if (c == 0)
		return (&s_e[i]);
	return (0);
}
