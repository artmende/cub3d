/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:00:14 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:56:09 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_win	win;

	check_args_and_initialize_t_win(&win, argc, argv);
	get_map(&win);
	win.pxspeed = win.square_size / 5;
	win.angspeed = 5 * (win.pi / 180);
	make_win(&win);
	if (win.save_to_bmp == 1)
	{
		build_frame(&win);
	}
	welcome_message();
	various_hooks(&win);
	mlx_loop(win.mlx_ptr);
	return (0);
}

int	call_gnl(t_win *win, int fd, char **line)
{
	win->gnl_return = get_next_line(fd, line);
	if (win->gnl_return == 1)
		return (1);
	else
		return (0);
}

int	call_exit(t_win *win, char *str)
{
	(void)(write(1, &win->error[0], 6) && write(1, str, ft_len_nl(str, 0)));
	(void)(win->bckgrd.img && mlx_destroy_image(win->mlx_ptr,
			win->bckgrd.img));
	(void)(win->text_no.img && mlx_destroy_image(win->mlx_ptr,
			win->text_no.img));
	(void)(win->text_so.img && mlx_destroy_image(win->mlx_ptr,
			win->text_so.img));
	(void)(win->text_ea.img && mlx_destroy_image(win->mlx_ptr,
			win->text_ea.img));
	(void)(win->text_we.img && mlx_destroy_image(win->mlx_ptr,
			win->text_we.img));
	(void)(win->text_s.img && mlx_destroy_image(win->mlx_ptr, win->text_s.img));
	if (win->save_to_bmp != 1)
		(void)(win->win_ptr && mlx_destroy_window(win->mlx_ptr, win->win_ptr));
	free_param_lst(win->map.word_list);
	free(win->map.no);
	free(win->map.s);
	free(win->map.so);
	free(win->map.we);
	free(win->map.ea);
	free(win->map.map);
	(void)(win->map.fd1 && close(win->map.fd1));
	(void)(win->map.fd2 && close(win->map.fd2));
	exit(0);
	return (1);
}

void	welcome_message(void)
{
	write(1, "\nWelcome to cub3D !\nList of available keys :\nW-A-S-D or ", 56);
	write(1, "arrow keys for navigation.\nSpace bar to show or hide the ", 57);
	write(1, "minimap.\n+ or - keys to adjust the minimap size.\n[ or ] ", 56);
	write(1, "keys to increase or decrease the field of view.\n", 48);
	write(1, "ESC to quit.\n\nEnjoy !\n", 22);
}
