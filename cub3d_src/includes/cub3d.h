/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:43:48 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 11:00:37 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line.h"
# include "structs.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

/*
	main.c
*/

int				main(int argc, char **argv);
int				call_gnl(t_win *win, int fd, char **line);
int				call_exit(t_win *win, char *str);
void			welcome_message(void);

/*
	initialize_window_and_mlx/initialize_window_and_mlx.c
*/

void			create_new_img(t_win *win, t_img *img, int resx, int resy);
void			get_fd_cub(t_win *win, char *cub_path);
void			check_args_and_initialize_t_win(t_win *win, int argc,
					char **argv);
void			load_textures_sprite(t_win *win);
void			make_win(t_win *win);

/*
	create_bmp_screenshot/create_bmp_screenshot.c
*/

void			create_bmp_screenshot(t_win *win);
void			generate_bmp_file_name(t_win *win, t_bmp_struct *bmp);
int				fill_bmp_header(t_win *win, t_bmp_struct *bmp);
int				ft_int_to_str(int n, char *temp);

/*
	draw_shapes/put_line.c
*/

void			put_line_pp(t_img *img, t_line_pp line, int color);
void			put_line_a(t_img *img, t_line_a line, int color);

/*
	draw_shapes/put_square_circle.c
*/

void			put_square(t_img *img, t_square sqr, int color);
void			put_fsquare(t_img *img, t_square sqr, int color);
void			put_fcircle(t_img *img, t_circle crcl, int color);
void			put_circle(t_img *img, t_circle crcl, double thck, int color);

/*
	read_cub_file_and_build_map/get_map.c
*/

void			get_map_content(t_win *win, char **map_content);
void			fill_map(t_win *win, char **map_content);
void			check_correct_resolution(t_win *win);
void			get_map(t_win *win);
int				back_free_array(char **array, int i);

/*
	read_cub_file_and_build_map/match_line_w_list.c
*/

void			associate_line_w_var(t_win *win, char *l);
int				find_match(t_win *win, char *l);
void			match_line_w_cub_data(t_win *win);

/*
	read_cub_file_and_build_map/manage_param_list.c
*/

t_param_name	*init_list_name(t_param_name *new1, t_param_name *new2);
t_param_name	*free_param_lst(t_param_name *lst);
int				create_new_name(t_param_name **new, char *str);
void			delete_entry_list(t_param_name **lst, char *name);

/*
	read_cub_file_and_build_map/check_map.c
*/

int				incorrect_NSEW(t_win *win);
int				is_map_line(char *l);
int				is_only_empty_lines(int fd);

/*
	read_cub_file_and_build_map/verify_map_is_closed.c
*/

void			verify_map_is_closed(t_win *win);
int				flood_fill_from_p(t_win *win, char *map, int x, int y);
int				display_leak_coordinate(int x, int y);

/*
	read_cub_file_and_build_map/check_cub_params.c
*/

int				check_path_length_extension(t_win *win, char *l, int *len);
void			check_color_line_ends_with_only_spaces(t_win *win, char *l);
void			check_color_line(t_win *win, char *l);
int				is_correct_color_number(t_win *win, char *l);

/*
	read_cub_file_and_build_map/parse_params_lines.c
*/

void			parse_res(t_win *win, char *l);
void			parse_path(t_win *win, char *l, char **address);
void			parse_f_c_color(t_win *win, char *l, char f_or_c);

/*
	read_cub_file_and_build_map/get_data_about_map.c
*/

void			get_map_width_height(t_win *win);
void			get_block_size(t_win *win);
double			get_p_angle(t_win *win, char c);
void			get_player_pos(t_win *win);

/*
	display_to_window/build_frame.c
*/
void			build_frame(t_win *win);
void			fill_img_half_half(t_img *img, int colorup, int colordown);

/*
	display_to_window/minimap.c
*/

void			init_minimap_params(t_win *win);
void			put_minimap(t_win *win);
void			put_grid(t_win *win, int color);
void			put_blocks(t_win *win, int block_color, int sprite_color);
void			put_player(t_win *win, int color);

/*
	display_to_window/render_walls_sprites.c
*/

void			render_walls_sprites(t_win *win);
void			render_walls(t_win *win);
void			apply_texture_color(t_win *win, t_ray *t_ray, t_point p);
void			extract_texture_color(t_win *win, t_img *texture, t_ray *ray,
					t_point p);

/*
	display_to_window/render_sprites.c
*/

void			render_sprites(t_win *win);
void			apply_sprite_color(t_win *win, t_ray *ray,
					t_sprite_list *sprite);

/*
	cast_rays/cast_ray.c
*/

void			cast_ray(t_win *win, t_ray *ray);
void			get_cross_hor(t_win *win, t_point p, t_ray *ray,
					t_point *cross);
void			get_cross_ver(t_win *win, t_point p, t_ray *ray,
					t_point *cross);
int				is_collision(t_win *win, t_point point, t_ray *ray);
void			calculate_texture_x_depth(t_win *win, t_ray *ray);

/*
	cast_rays/handling_sprites.c
*/

void			colision_with_sprite(t_win *win, t_ray *ray, int i);
double			get_angle_to_point(t_win *win, t_point point);
void			sort_sprites_by_distance(t_ray *ray, t_sprite_list *temp1,
					t_sprite_list *temp2);
void			free_sprite_lst(t_sprite_list *lst);

/*
	hooks_and_pos_update/ft_hooks.c
*/

int				keyhook(int key, t_win *win);
int				xposehook(t_win *win);
void			various_hooks(t_win *win);
int				red_cross_clicked(t_win *win);

/*
hooks_and_pos_update/select_key_action.c
*/

void			select_key_action(t_win *win, int key, t_point *next,
					double *new_angle);
void			no_movement_key_press(t_win *win, int key);

/*
	hooks_and_pos_update/update_pos.c
*/

void			update_pos(t_win *win, t_point next, double new_angle);

/*
	utils/from_libft_mem_str.c
*/

void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memset(void *s, int c, size_t n);
char			*ft_strnstr(char *str, char *to_find, size_t len);
char			*ft_strchr(const char *s, int c);

/*
	utils/from_libft_nbr.c
*/

int				ft_atoi(const char *str);
void			ft_putnbr_fd(int n, int fd);

/*
	utils/various_utils.c
*/

void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
double			get_distance(t_point a, t_point b);
int				get_index_from_point(t_win *win, t_point point);
int				get_index_from_square(t_win *win, int x, int y);
int				is_in_map(t_win *win, t_point point);

#endif
