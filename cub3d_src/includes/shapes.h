/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 14:23:38 by artmende          #+#    #+#             */
/*   Updated: 2021/05/31 11:55:41 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_line_pp
{
	t_point	from;
	t_point	to;
}				t_line_pp;

typedef struct s_line_a
{
	t_point	origin;
	double	angle;
	double	length;
}				t_line_a;

typedef struct s_square
{
	t_point	top_left;
	double	side_len;
}				t_square;

typedef struct s_cirle
{
	t_point	center;
	double	ray;
}				t_circle;

#endif
