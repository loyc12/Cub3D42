/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 15:00:12 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//finds the tile from given x and y (and x and y directions) and returns its type
int	find_hit_type(t_ray *r)
{
	t_tile	*hit_tile;
	int		hit_x;
	int		hit_y;

	//these prevent rounding errors
	if (r->ray_to_x_ratio < 0)
		hit_x = floor(r->x_coord - 0.00001);
	else
		hit_x = floor(r->x_coord + 0.00001);
	if (r->ray_to_y_ratio < 0)
		hit_y = floor(r->y_coord - 0.00001);
	else
		hit_y = floor(r->y_coord + 0.00001);

	hit_tile = find_tile(hit_x, hit_y);

//	printf("Hit point : %.3f, %.3f\n", r->x_coord, r->y_coord); //	0======== DEBUG ========0
//	printf("Hit tile  : %i, %i\n", hit_x, hit_y); //	0======== DEBUG ========0
	if (hit_tile)
	{
//		printf("Hit Type  : %i\n\n", hit_tile->type); //	0======== DEBUG ========0
		return (hit_tile->type);
	}
	else
	{
//		printf("Hit Type  : NOT FOUND\n\n"); //	0======== DEBUG ========0
		return (TTYPE_ERROR);
	}

}

void	find_first_ray_dists(t_ray *r)
{
	if (!(r->ignore_x))
	{
		if ((-90 <= r->angle && r->angle <= 90) || (270 <= r->angle && r->angle <= 450))
		{
//			printf("\nPositive x\n"); //	0======== DEBUG ========0
			r->x_ray_dist = (1 - ((r->player_pos->x) - floor(r->player_pos->x))) * fabs(r->x_to_ray_ratio);
		}
		else
		{
//			printf("\nNegative x\n"); //	0======== DEBUG ========0
			r->x_ray_dist = ((r->player_pos->x) - floor(r->player_pos->x)) * fabs(r->x_to_ray_ratio);
		}
	}
	else
	{
		r->x_ray_dist = INFINITY;
//		printf("\nIgnoring x\n"); //	0======== DEBUG ========0
	}
	if (!(r->ignore_y))
	{
		if ((0 <= r->angle && r->angle <= 180) || (360 <= r->angle && r->angle <= 540))
		{
//			printf("Positive y\n"); //	0======== DEBUG ========0
			r->y_ray_dist = (1 - ((r->player_pos->y) - floor(r->player_pos->y))) * fabs(r->y_to_ray_ratio);
		}
		else
		{
//			printf("Negative y\n"); //	0======== DEBUG ========0
			r->y_ray_dist = ((r->player_pos->y) - floor(r->player_pos->y)) * fabs(r->y_to_ray_ratio);
		}
	}
	else
	{
		r->y_ray_dist = INFINITY;
//		printf("Ignoring y\n"); //	0======== DEBUG ========0
	}

//	printf("\nInitial distance in x : %.3f\n", r->x_ray_dist); //		0======== DEBUG ========0
//	printf("Initial distance in y: %.3f\n\n", r->y_ray_dist); //	0======== DEBUG ========0
}

bool	evaluate_x_hits(t_ray *r)
{
//	printf("Switching to X checks\n\n"); //	0======== DEBUG ========0
	while (r->x_ray_dist <= r->y_ray_dist)
	{
		r->x_coord = r->player_pos->x + (r->x_ray_dist * r->ray_to_x_ratio);
		r->y_coord = r->player_pos->y + (r->x_ray_dist * r->ray_to_y_ratio);

		r->hit_type = find_hit_type(r);

		if (r->hit_type == TTYPE_WALL)
		{
			r->ray_dist = r->x_ray_dist;
//			printf("Distance : %.3f\n\n", r->x_ray_dist); //	0======== DEBUG ========0
			return (true);
		}
		else if (r->hit_type == TTYPE_ERROR)
		{
//			printf("Out of bound at %.3f:%.3f\n", r->x_coord, r->y_coord); //	0======== DEBUG ========0
//			printf("Distance : %.3f\n", r->x_ray_dist); //	0======== DEBUG ========0
			r->ray_dist = r->x_ray_dist;
			return (true);
		}
		r->x_ray_dist += fabs(r->x_to_ray_ratio); //	increment distance in x
	}
	return (false);
}

bool	evaluate_y_hits(t_ray *r)
{
//	printf("Switching to Y checks\n\n"); //	0======== DEBUG ========0
	while (r->y_ray_dist <= r->x_ray_dist)
	{
		r->x_coord = r->player_pos->x + (r->y_ray_dist * r->ray_to_x_ratio);
		r->y_coord = r->player_pos->y + (r->y_ray_dist * r->ray_to_y_ratio);

		r->hit_type = find_hit_type(r);

		if (r->hit_type == TTYPE_WALL)
		{
//			printf("Distance : %.3f\n", r->y_ray_dist); //	0======== DEBUG ========0
			r->ray_dist = r->y_ray_dist;
			return (true);
		}
		else if (r->hit_type == TTYPE_ERROR)
		{
//			printf("Out of bound at %.3f:%.3f\n", r->x_coord, r->y_coord); //	0======== DEBUG ========0
//			printf("Distance : %.3f\n", r->y_ray_dist); //	0======== DEBUG ========0
			r->ray_dist = r->y_ray_dist;
			return (true);
		}
		r->y_ray_dist += fabs(r->y_to_ray_ratio); //	increment distance in y
	}
	return (false);
}

t_slice	*cast_ray(t_vector *pos, double ray_angle)
{
	t_ray	*r;

	r = ft_calloc(1, sizeof(t_ray));

	r->angle = normalize_angle(ray_angle + pos->d); //	makse the ray angle absolute
	r->player_pos = pos;

//	printf("Casting ray at angle : %.3f (%.3f)\n", r->angle, ray_angle); //		0======== DEBUG ========0

	find_ratios(r);
	find_first_ray_dists(r);

	while (true)
	{
		if (evaluate_x_hits(r))
		{
			if (0 <= r->ray_to_x_ratio)
				r->hit_dir = 1;
			else
				r->hit_dir = 3;
			break ;
		}
		if (evaluate_y_hits(r))
		{
			if (0 <= r->ray_to_y_ratio)
				r->hit_dir = 2;
			else
				r->hit_dir = 0;
			break ;
		}
	}
//	printf("Wall height : %.3f\n\n", 1 / r->ray_dist); //	0======== DEBUG ========0

	return (create_slice(r, ray_angle));
}

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
