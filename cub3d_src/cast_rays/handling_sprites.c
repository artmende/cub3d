/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_sprites.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 06:37:42 by artmende          #+#    #+#             */
/*   Updated: 2021/06/02 10:10:36 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
	The info needed to render a sprite band, is :
	- distance of the sprite (to know what height it has on the window)
	- x_depth of that band

	The distance is from the player to the CENTER of the sprite.
	So each band of the same sprite will have the same distance. That will make
	the sprite always facing the player.

	The x_depth is determined by making the ray intercept with the surface
	facing the player and intersecting the sprite center. We look for the 
	distance separating that virtual collision and the sprite center.
	It's the ratio between that distance and the full width of a sprite that
	determines x_depth.
*/

void	colision_with_sprite(t_win *win, t_ray *ray, int i)
{
	t_sprite_calculation_struct	s;

	ray->temp_ptr = ray->sprite;
	ray->sprite = malloc(sizeof(t_sprite_list));
	if (!ray->sprite)
	{
		free_sprite_lst(ray->temp_ptr);
		call_exit(win, "Malloc issue.\n");
	}
	ray->sprite->next = ray->temp_ptr;
	ray->sprite->x = ray->x;
	s.sprite_center.x = ((i % win->map.width) + 0.5) * win->square_size;
	s.sprite_center.y = ((i / win->map.width) + 0.5) * win->square_size;
	s.angle_to_sprite_center = get_angle_to_point(win, s.sprite_center);
	ray->sprite->distance = get_distance(s.sprite_center,
			(t_point){win->px, win->py});
	s.distance_collision_to_centre_sprite = tan(ray->angle
			- s.angle_to_sprite_center) * ray->sprite->distance;
	ray->sprite->x_depth = (s.distance_collision_to_centre_sprite
			+ 0.5 * win->square_size) / win->square_size;
}

/*
	get_angle_to_point returns the angle that corresponds to the direction
	from the player position to the point "point".
	If point was on the same x than the player, the angle returned would be
	+90 or -90.
	If point was on the same y than the player, the angle returned would be
	0 or 180.
*/

double	get_angle_to_point(t_win *win, t_point point)
{
	double	angle;
	double	delta_x;
	double	delta_y;

	delta_x = point.x - win->px;
	delta_y = point.y - win->py;
	angle = atan(delta_y / delta_x);
	if ((delta_x < 0 && cos(angle) > 0) || (delta_x > 0 && cos(angle) < 0))
		angle += win->pi;
	if ((delta_y > 0 && sin(angle) < 0) || (delta_y < 0 && sin(angle) > 0))
		angle += win->pi;
	return (angle);
}

void	sort_sprites_by_distance(t_ray *ray, t_sprite_list *temp1,
	t_sprite_list *temp2)
{
	temp1 = ray->sprite;
	while (temp1)
	{
		if (temp1->next && temp1->distance < temp1->next->distance)
		{
			temp2 = temp1->next->next;
			ray->sprite = temp1->next;
			temp1->next = temp2;
			ray->sprite->next = temp1;
			temp1 = ray->sprite;
		}
		if (temp1->next && temp1->next->next
			&& temp1->next->distance < temp1->next->next->distance)
		{
			temp2 = temp1->next;
			temp1->next = temp2->next;
			temp2->next = temp1->next->next;
			temp1->next->next = temp2;
			temp1 = ray->sprite;
			continue ;
		}
		temp1 = temp1->next;
	}
}

void	free_sprite_lst(t_sprite_list *lst)
{
	t_sprite_list	*temp1;
	t_sprite_list	*temp2;

	temp1 = lst;
	while (temp1)
	{
		temp2 = temp1->next;
		free(temp1);
		temp1 = temp2;
	}
}
