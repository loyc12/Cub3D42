/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_raycasters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 10:52:08 by llord            ###   ########.fr       */
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
//	0======== DEBUG ========0
//	printf("Hit point : %.3f, %.3f\n", r->x_coord, r->y_coord);
//	printf("Hit tile  : %i, %i\n", hit_x, hit_y);
//	printf("Hit Type  : %i\n\n", hit_tile->type);
//	printf("Hit Type  : NOT FOUND\n\n");

void	find_first_ray_dists(t_ray *r)
{
	if (!(r->ignore_x))
	{
		if ((-90 <= r->angle && r->angle <= 90) || (270 <= r->angle
				&& r->angle <= 450))
		{
			r->x_ray_dist = (1 - ((r->player_pos->x) - floor(r->player_pos->x)))
				* fabs(r->x_to_ray_ratio);
		}
		else
		{
			r->x_ray_dist = ((r->player_pos->x) - floor(r->player_pos->x))
				* fabs(r->x_to_ray_ratio);
		}
	}
	else
		r->x_ray_dist = INFINITY;
	if (!(r->ignore_y))
	{
		if ((0 <= r->angle && r->angle <= 180) || (360 <= r->angle
				&& r->angle <= 540))
		{
			r->y_ray_dist = (1 - ((r->player_pos->y) - floor(r->player_pos->y)))
				* fabs(r->y_to_ray_ratio);
		}
		else
		{
			r->y_ray_dist = ((r->player_pos->y) - floor(r->player_pos->y))
				* fabs(r->y_to_ray_ratio);
		}
	}
	else
		r->y_ray_dist = INFINITY;
}
//	0======== DEBUG ========0
//	printf("\nInitial distance in x : %.3f\n", r->x_ray_dist);
//	printf("Initial distance in y: %.3f\n\n", r->y_ray_dist);
//	printf("\nPositive x\n");
//	printf("\nNegative x\n");
//	printf("\nIgnoring x\n");
//	printf("Positive y\n");
//	printf("Negative y\n");
//	printf("Ignoring y\n");

//	increment distance in x
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
//	0======== DEBUG ========0
//	printf("Switching to X checks\n\n");
//	printf("Distance : %.3f\n\n", r->x_ray_dist);
//	printf("Out of bound at %.3f:%.3f\n", r->x_coord, r->y_coord);
//	printf("Distance : %.3f\n", r->x_ray_dist);

//	increment distance in y
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
//	0======== DEBUG ========0
//	printf("Switching to Y checks\n\n");
//	printf("Distance : %.3f\n", r->y_ray_dist);
//	printf("Out of bound at %.3f:%.3f\n", r->x_coord, r->y_coord);
//	printf("Distance : %.3f\n", r->y_ray_dist);

//	makse the ray angle absolute
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

//		0======== DEBUG ========0
//	printf("Casting ray at angle : %.3f (%.3f)\n", r->angle, ray_angle);
//	printf("Wall height : %.3f\n\n", 1 / r->ray_dist);

/*
	ray_cast()
		from player position & angle
		find the nearest wall (from angle relative to player)
//			find step direction (+/- x, +/- y)
			find Xi and Yi
			find Xratio and Yratio
			while (!hit)
				check in X until Dx > Dy
				check in Y until Dy > Dx
		return hit struct (distance + position + wall type)
*/
