/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/08 11:33:13 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//hit_struct();

double	find_nearest(double x, double y, double dir) //	normally would work with swapped x and y
{
	(void)x;
	(void)y;
	(void)dir;
	return (dir);
}

double	find_x_ratio(double angle) //	superfluous;
{
	double	ratio;

	ratio = sin(2 * PI * angle / 360);

//	printf("Rx : %.3f\n", ratio); //	0======== DEBUG ========0

	return (ratio);
}

double	find_y_ratio(double angle) //	superfluous;
{
	double	ratio;

	ratio = cos(2 * PI * angle / 360);

//	printf("Ry : %.3f\n", ratio); //	0======== DEBUG ========0

	return (ratio);
}

//finds the tile from given x and y (and x and y directions) and returns its type
int	find_hit_type(double x, double y, double x_dir, double y_dir)
{
	t_tile	*hit_tile;

	if (x_dir < 0)
		x -= 1;
	if (y_dir < 0)
		y += 1;
	hit_tile = find_tile((int)x, (int)y);
	printf("\nlol\n");

	printf("Hit Tile : %i,%i\n", (int)x, (int)y); //	0======== DEBUG ========0
	if (hit_tile)
	{
		printf("Hit Type : %i\n", hit_tile->type); //	0======== DEBUG ========0
		return (hit_tile->type);
	}
	else
	{
		printf("Hit Type : NOT FOUND\n"); //	0======== DEBUG ========0
		return (TTYPE_ERROR);
	}

}

void	cast_ray(t_vector *pos, double angle)
{
	int	x_dir;
	int	x_dist;
	int	x_ratio;
	int	y_dir;
	int	y_dist;
	int	y_ratio;

	angle += pos->d; //	make the angle relative to the player angle

	y_dir = 1; //	find incrementation direction for y (used for tan())
	if (angle < 0 && 180 < angle)
		y_dir = -1;

	x_dir = 1; //	find incrementation direction for x (used for tan())
	if (angle < -90 && 90 < angle)
		x_dir = -1;

	x_dist = find_nearest(pos->x, pos->y, x_dir); // finds first distance in x, x_dist = init_dist, then new_dist
	y_dist = find_nearest(pos->y, pos->x, y_dir); // finds first distance in y, y_dist = init_dist, then new_dist

	x_ratio = find_x_ratio(angle);
	y_ratio = find_y_ratio(angle);
/*
	while (true) //don't forget test pour si depasse mur (fausse donnée, si oui on doit revoir le calcul)
	{
		while (x_dist <= y_dist)
		{
			if (TTYPE_WALL == find_hit_type(pos->x + (x_dist * x_ratio), pos->y + (x_dist * y_ratio), x_dir, y_dir))
				return (hit_struct());
			x_dist += x_ratio; //	increment distance in x
		}
		while (x_dist >= y_dist)
		{
			if (TTYPE_WALL == find_hit_type(pos->x + (y_dist * x_ratio), pos->y + (y_dist * y_ratio), x_dir, y_dir))
				return (hit_struct());
			y_dist += y_ratio; //	increment distance in y
		}
	}
*/
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