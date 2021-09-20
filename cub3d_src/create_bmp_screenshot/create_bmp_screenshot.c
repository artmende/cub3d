/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp_screenshot.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 14:04:22 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:12:29 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_bmp_screenshot(t_win *win)
{
	t_bmp_struct	bmp;
	int				x;
	int				y;

	generate_bmp_file_name(win, &bmp);
	bmp.fd = open(bmp.path, O_CREAT | O_WRONLY, 00664);
	free(bmp.path);
	if (bmp.fd == -1)
		call_exit(win, "Error creating BMP file !\n");
	(void)(write(bmp.fd, "BM", 2) && fill_bmp_header(win, &bmp));
	write(bmp.fd, &bmp.header, sizeof(t_bmp_header));
	y = win->resy - 1;
	while (y >= 0)
	{
		x = -1;
		bmp.row = malloc(sizeof(int) * win->resx);
		(void)(!bmp.row && call_exit(win, "Malloc issue.\n"));
		while (++x < win->resx)
			bmp.row[x] = *(unsigned int *)(win->bckgrd.addr + (y * win
						->bckgrd.sizeline + x * (win->bckgrd.bitppxl / 8)));
		write(bmp.fd, bmp.row, win->resx * sizeof(int));
		write(bmp.fd, "", (bmp.row_size / 4) - win->resx);
		free(bmp.row);
		y--;
	}
}

void	generate_bmp_file_name(t_win *win, t_bmp_struct *bmp)
{
	int		id_bmp;
	int		i;
	char	temp[11];

	bmp->fd = -2;
	id_bmp = 0;
	bmp->path = 0;
	bmp->file_name = (char *)&"./screenshots/cub3d_screenshot_";
	bmp->name_length = ft_len_nl(bmp->file_name, 0);
	while (bmp->fd != -1)
	{
		i = ft_int_to_str(id_bmp, (char *)&temp);
		free(bmp->path);
		bmp->path = malloc(sizeof(char) * (5 + (11 - i) + bmp->name_length));
		if (!bmp->path)
			call_exit(win, "Error creating BMP file !\n");
		ft_memmove(bmp->path, bmp->file_name, bmp->name_length);
		ft_memmove(&bmp->path[bmp->name_length], &temp[i], 11 - i);
		ft_memmove(&bmp->path[bmp->name_length + 11 - i], ".bmp", 5);
		bmp->fd = open(bmp->path, O_RDONLY);
		if (bmp->fd > 0)
			close(bmp->fd);
		id_bmp++;
	}
}

int	fill_bmp_header(t_win *win, t_bmp_struct *bmp)
{
	t_bmp_header	*header;

	header = &bmp->header;
	header->bits_per_pixel = 8 * sizeof(unsigned int);
	bmp->row_size = (4 * floor((header->bits_per_pixel * win->resx + 31) / 32));
	header->pixel_data_offset = 54;
	header->file_size = bmp->row_size * win->resy + header->pixel_data_offset;
	header->reserved_space = 0;
	header->header_size = 40;
	header->image_width = win->resx;
	header->image_height = win->resy;
	header->planes = 1;
	ft_memset(&header->compression, 0, 24);
	return (1);
}

int	ft_int_to_str(int n, char *temp)
{
	unsigned int	i;
	int				n_sav;

	i = 10;
	n_sav = n;
	if (!n)
		temp[i] = '0';
	while (n)
	{
		if (n > 0)
			temp[i--] = (n % 10) + '0';
		else
			temp[i--] = -(n % 10) + '0';
		n = n / 10;
	}
	if (n < 0)
		temp[i--] = '-';
	if (n_sav)
		i++;
	return (i);
}
