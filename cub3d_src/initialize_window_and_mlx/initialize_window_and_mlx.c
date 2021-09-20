/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_window_and_mlx.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 05:28:31 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 11:01:44 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_new_img(t_win *win, t_img *img, int resx, int resy)
{
	img->img = mlx_new_image(win->mlx_ptr, resx, resy);
	if (!img->img)
		call_exit(win, "MLX couldn't create image.\n");
	img->addr = mlx_get_data_addr(img->img, &img->bitppxl, &img->sizeline,
			&img->endian);
	img->resx = resx;
	img->resy = resy;
}

void	load_textures_sprite(t_win *win)
{
	win->text_we.img = mlx_xpm_file_to_image(win->mlx_ptr, win->map.we,
			&win->text_we.resx, &win->text_we.resy);
	win->text_ea.img = mlx_xpm_file_to_image(win->mlx_ptr, win->map.ea,
			&win->text_ea.resx, &win->text_ea.resy);
	win->text_so.img = mlx_xpm_file_to_image(win->mlx_ptr, win->map.so,
			&win->text_so.resx, &win->text_so.resy);
	win->text_no.img = mlx_xpm_file_to_image(win->mlx_ptr, win->map.no,
			&win->text_no.resx, &win->text_no.resy);
	win->text_s.img = mlx_xpm_file_to_image(win->mlx_ptr, win->map.s,
			&win->text_s.resx, &win->text_s.resy);
	if (!win->text_we.img || !win->text_ea.img || !win->text_so.img
		|| !win->text_no.img || !win->text_s.img)
		call_exit(win, "Can't open texture file !\n");
	win->text_we.addr = mlx_get_data_addr(win->text_we.img, &win
			->text_we.bitppxl, &win->text_we.sizeline, &win->text_we.endian);
	win->text_ea.addr = mlx_get_data_addr(win->text_ea.img, &win
			->text_ea.bitppxl, &win->text_ea.sizeline, &win->text_ea.endian);
	win->text_so.addr = mlx_get_data_addr(win->text_so.img, &win
			->text_so.bitppxl, &win->text_so.sizeline, &win->text_so.endian);
	win->text_no.addr = mlx_get_data_addr(win->text_no.img, &win
			->text_no.bitppxl, &win->text_no.sizeline, &win->text_no.endian);
	win->text_s.addr = mlx_get_data_addr(win->text_s.img,
			&win->text_s.bitppxl, &win->text_s.sizeline, &win->text_s.endian);
}

void	make_win(t_win *win)
{
	if (win->save_to_bmp != 1)
	{
		win->win_ptr = mlx_new_window(win->mlx_ptr, win->resx, win->resy,
				"cub3D");
	}
	else
		win->win_ptr = &"anything";
	if (!win->win_ptr)
		call_exit(win, "MLX couldn't create window.\n");
	create_new_img(win, &win->bckgrd, win->resx, win->resy);
	load_textures_sprite(win);
}

void	get_fd_cub(t_win *win, char *cub_path)
{
	int	i;

	i = ft_len_nl(cub_path, 0) - 4;
	if (i < 0 || !ft_strnstr(&cub_path[i], ".cub", 4))
		call_exit(win, "The cub file must have the .cub extension !\n");
	win->map.fd1 = open(cub_path, O_RDONLY);
	win->map.fd2 = open(cub_path, O_RDONLY);
	if (win->map.fd1 == -1 || win->map.fd2 == -1)
		call_exit(win, "Cannot open cub file !\n");
}

void	check_args_and_initialize_t_win(t_win *win, int argc, char **argv)
{
	ft_memset(win, 0, sizeof(*win));
	ft_memmove(&win->error[0], "Error\n", 6);
	if (argc < 2 || argc > 3)
	{
		call_exit(win, "Wrong number of arguments.\n");
	}
	if (argc == 3)
	{
		if (ft_len_nl(argv[2], 0) == 6 && ft_strnstr(argv[2], "--save", 6))
			win->save_to_bmp = 1;
		else
			call_exit(win, "Use '--save' to create a screenshot.\n");
	}
	get_fd_cub(win, argv[1]);
	win->pi = acos(-1);
	win->pi_2 = asin(1);
	init_minimap_params(win);
	win->fov = 60 * (win->pi / 180);
	win->mlx_ptr = mlx_init();
	if (!win->mlx_ptr)
		call_exit(win, "MLX couldn't be launched.\n");
}
