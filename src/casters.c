/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/08 13:07:44 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//hit_struct();

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
		y -= 1;
	hit_tile = find_tile((int)x, (int)y);

	printf("Hit Tile : %i,%i\n", (int)x, (int)y); //	0======== DEBUG ========0
	if (hit_tile)
	{
		printf("Hit Type : %i\n\n", hit_tile->type); //	0======== DEBUG ========0
		return (hit_tile->type);
	}
	else
	{
		printf("Hit Type : NOT FOUND\n\n"); //	0======== DEBUG ========0
		return (TTYPE_ERROR);
	}

}

void	cast_ray(t_vector *pos, double angle)
{
	double	x;
	int		x_dir;
	double	x_dist;
	double	x_ratio;

	double	y;
	int		y_dir;
	double	y_dist;
	double	y_ratio;

	int		type;

	angle += pos->d; //	make the angle relative to the player angle

	x_ratio = find_x_ratio(angle);
	y_ratio = find_y_ratio(angle);

	if ((-90 <= angle && angle <= 90) || (270 <= angle && angle <= 450)) //	if x+
	{
		x_dir = 1;
		if (angle != 0 && angle != 360)
		{
			printf("1\n");
			x_dist = ((pos->x) - (int)(pos->x)) / x_ratio; //	will crash at right angle
		}
		else
		{
			printf("2\n");
			x_dist = INFINITY;
		}
	}
	else //																if x-
	{
		x_dir = -1;
		if (angle != -180 && angle != 180)
		{
			printf("3\n");
			x_dist = (1 - ((pos->x) - (int)(pos->x))) / x_ratio; //	will crash at right angle
		}
		else
		{
			printf("4\n");
			x_dist = INFINITY;
		}
	}

	if ((0 <= angle && angle <= 180) || (360 <= angle && angle <= 540)) //	if y+
	{
		y_dir = 1;
		if (angle != 90 && angle != 450)
		{
			printf("5\n");
			y_dist = ((pos->y) - (int)(pos->y)) / y_ratio;
		}
		else
		{
			printf("6\n");
			y_dist = INFINITY;
		}
	}
	else //																if y-
	{
		y_dir = -1;
		if (angle != -90 && angle != 270)
		{
			printf("7\n");
			y_dist = (1 - ((pos->y) - (int)(pos->y))) / x_ratio; //	will crash at right angle
		}
		else
		{
			printf("8\n");
			y_dist = INFINITY;
		}
	}

	printf("Dxi : %.3f\n", x_dist); //		0======== DEBUG ========0
	printf("Dyi : %.3f\n\n", y_dist); //	0======== DEBUG ========0

	while (true) //don't forget test pour si depasse mur (fausse donnée, si oui on doit revoir le calcul)
	{
		while (x_dist <= y_dist)
		{
			x = pos->x + (x_dist * x_ratio);
			y = pos->y + (x_dist * y_ratio);
			type = find_hit_type(x, y, x_dir, y_dir);
			if (type == TTYPE_WALL)
			{
				printf("Hit wall at %.3f:%.3f\n", x, y); //	0======== DEBUG ========0
				printf("Distance : %.3f\n\n", x_dist); //	0======== DEBUG ========0
				return ;
			}
			else if (type == TTYPE_ERROR)
			{
				printf("Out of bound at %.3f:%.3f\n", x, y); //	0======== DEBUG ========0
				printf("Distance : %.3f\n\n", x_dist); //	0======== DEBUG ========0
				return ;
			}
			x_dist += x_ratio; //	increment distance in x
		}
		while (x_dist >= y_dist)
		{
			x = pos->x + (y_dist * x_ratio);
			y = pos->y + (y_dist * y_ratio);
			type = find_hit_type(x, y, x_dir, y_dir);
			if (type == TTYPE_WALL)
			{
				printf("Hit wall at %.3f:%.3f\n", x, y); //	0======== DEBUG ========0
				printf("Distance : %.3f\n\n", y_dist); //	0======== DEBUG ========0
				return ;
			}
			else if (type == TTYPE_ERROR)
			{
				printf("Out of bound at %.3f:%.3f\n", x, y); //	0======== DEBUG ========0
				printf("Distance : %.3f\n\n", y_dist); //	0======== DEBUG ========0
				return ;
			}
			y_dist += y_ratio; //	increment distance in y
		}
	}

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