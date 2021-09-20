/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/13 12:35:03 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:08:09 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "shapes.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bitppxl;
	int		sizeline;
	int		endian;
	int		resx;
	int		resy;
}				t_img;

typedef struct s_param_name
{
	char				*name;
	struct s_param_name	*next;
}				t_param_name;

typedef struct s_map
{
	char			*map;
	char			*no;
	char			*so;
	char			*ea;
	char			*we;
	char			*s;
	int				ceiling_color;
	int				floor_color;
	t_param_name	*word_list;
	t_param_name	*list_temp;
	int				width;
	int				height;
	int				index_max;
	int				fd1;
	int				fd2;
	int				first_line_map;
}				t_map;

typedef struct s_sprite_calculation_struct
{
	t_point			sprite_center;
	double			angle_to_sprite_center;
	double			distance_collision_to_centre_sprite;
}				t_sprite_calculation_struct;

typedef struct s_sprite_list
{
	double					x_depth;
	double					distance;
	int						x;
	int						y;
	struct s_sprite_list	*next;
}				t_sprite_list;

typedef struct s_ray
{
	t_point			to;
	double			len;
	double			angle;
	char			v_e_w;
	char			h_n_s;
	char			n_s_e_w;
	double			x_depth;
	double			y_depth;
	int				x;
	t_sprite_list	*sprite;
	t_sprite_list	*temp_ptr;
}				t_ray;

typedef struct s_win
{
	double	pi;
	double	pi_2;
	char	error[6];
	int		resx;
	int		resy;
	int		resx_max;
	int		resy_max;
	double	square_size;
	double	minimap_size;
	double	minimap_scale_factor;
	int		minimap_grid_color;
	int		minimap_block_color;
	int		minimap_sprite_color;
	int		minimap_player_color;
	int		minimap_display_or_not;
	double	fov;
	void	*win_ptr;
	void	*mlx_ptr;
	t_img	bckgrd;
	t_img	text_no;
	t_img	text_so;
	t_img	text_ea;
	t_img	text_we;
	t_img	text_s;
	double	px;
	double	py;
	double	pa;
	int		p_index_start;
	double	pxspeed;
	double	angspeed;
	t_map	map;
	t_ray	ray;
	int		gnl_return;
	int		save_to_bmp;
}				t_win;

typedef struct s_bmp_header
{
	unsigned int	file_size;
	unsigned int	reserved_space;
	unsigned int	pixel_data_offset;
	unsigned int	header_size;
	unsigned int	image_width;
	unsigned int	image_height;
	unsigned short	planes;
	unsigned short	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size_set_to_zero;
	unsigned int	x_pixels_per_meter;
	unsigned int	y_pixels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}				t_bmp_header;

typedef struct s_bmp_struct
{
	t_bmp_header	header;
	char			*path;
	char			*file_name;
	int				name_length;
	int				fd;
	int				row_size;
	unsigned int	*row;
}				t_bmp_struct;

#endif
