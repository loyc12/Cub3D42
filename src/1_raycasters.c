/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycasters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 15:02:11 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//finds the tile from given x and y (and x and y directions) and rets its type
//these prevent rounding errors
int	find_hit_type(t_ray *r)
{
	t_tile	*hit_tile;
	int		hit_x;
	int		hit_y;

	if (r->ray_to_x_ratio < 0)
		hit_x = floor(r->x_coord - 0.00001);
	else
		hit_x = floor(r->x_coord + 0.00001);
	if (r->ray_to_y_ratio < 0)
		hit_y = floor(r->y_coord - 0.00001);
	else
		hit_y = floor(r->y_coord + 0.00001);
	hit_tile = find_tile(hit_x, hit_y);
	if (hit_tile)
		return (hit_tile->type);
	else
		return (TTYPE_ERROR);
}

void	find_first_ray_dists(t_ray *r)
{
	if (!(r->ignore_x))
	{
		if ((-90 <= r->angle && r->angle <= 90) || (270 <= r->angle
				&& r->angle <= 450))
			r->x_ray_dist = (1 - ((r->player_pos->x) - \
				floor(r->player_pos->x))) * fabs(r->x_to_ray_ratio);
		else
			r->x_ray_dist = ((r->player_pos->x) - floor(r->player_pos->x)) \
				* fabs(r->x_to_ray_ratio);
	}
	else
		r->x_ray_dist = INFINITY;
	if (!(r->ignore_y))
	{
		if ((0 <= r->angle && r->angle <= 180) || (360 <= r->angle
				&& r->angle <= 540))
			r->y_ray_dist = (1 - ((r->player_pos->y) - \
				floor(r->player_pos->y))) * fabs(r->y_to_ray_ratio);
		else
			r->y_ray_dist = ((r->player_pos->y) - floor(r->player_pos->y)) \
				* fabs(r->y_to_ray_ratio);
	}
	else
		r->y_ray_dist = INFINITY;
}

//	Increment distance in x
bool	evaluate_x_hits(t_ray *r)
{
	r->is_checking_x = true;
	while (r->x_ray_dist <= r->y_ray_dist)
	{
		r->x_coord = r->player_pos->x + (r->x_ray_dist * r->ray_to_x_ratio);
		r->y_coord = r->player_pos->y + (r->x_ray_dist * r->ray_to_y_ratio);
		r->hit_type = find_hit_type(r);
		if (r->hit_type == TTYPE_WALL)
		{
			r->ray_dist = r->x_ray_dist;
			return (true);
		}
		else if (r->hit_type == TTYPE_ERROR)
		{
			r->ray_dist = r->x_ray_dist;
			return (true);
		}
		r->x_ray_dist += fabs(r->x_to_ray_ratio);
	}
	return (false);
}

//	Increment distance in y
bool	evaluate_y_hits(t_ray *r)
{
	r->is_checking_x = false;
	while (r->y_ray_dist <= r->x_ray_dist)
	{
		r->x_coord = r->player_pos->x + (r->y_ray_dist * r->ray_to_x_ratio);
		r->y_coord = r->player_pos->y + (r->y_ray_dist * r->ray_to_y_ratio);
		r->hit_type = find_hit_type(r);
		if (r->hit_type == TTYPE_WALL)
		{
			r->ray_dist = r->y_ray_dist;
			return (true);
		}
		else if (r->hit_type == TTYPE_ERROR)
		{
			r->ray_dist = r->y_ray_dist;
			return (true);
		}
		r->y_ray_dist += fabs(r->y_to_ray_ratio);
	}
	return (false);
}

//	Make the ray angle absolute
t_slice	*cast_ray(t_vector *pos, double ray_angle)
{
	t_ray	*r;

	r = ft_calloc(1, sizeof(t_ray));
	r->angle = normalize_angle(ray_angle + pos->d);
	r->player_pos = pos;
	find_ratios(r);
	find_first_ray_dists(r);
	while (true)
	{
		if (evaluate_x_hits(r))
			break ;
		if (evaluate_y_hits(r))
			break ;
	}
	find_texture_pos(r);
	return (create_slice(r, ray_angle));
}
