/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_maths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:32 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 09:42:41 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	find_ratios(t_ray *r)
{
	if (r->angle != -90 && r->angle != 90 && r->angle != 270 && r->angle != 450)
	{
		r->ray_to_x_ratio = cos(M_PI * r->angle / 180);
		r->x_to_ray_ratio = (1 / r->ray_to_x_ratio);
	}
	else
	{
		r->ignore_x = true;
		r->ray_to_x_ratio = 0;
		r->x_to_ray_ratio = INFINITY;
	}
	if (r->angle != -180 && r->angle != 0 && r->angle != 180 && r->angle != 360)
	{
		r->ray_to_y_ratio = sin(M_PI * r->angle / 180);
		r->y_to_ray_ratio = (1 / r->ray_to_y_ratio);
	}
	else
	{
		r->ignore_y = true;
		r->ray_to_y_ratio = 0;
		r->y_to_ray_ratio = INFINITY;
	}
}
//	0======== DEBUG ========0
//	printf("\nrtx : %.3f\n", r->ray_to_x_ratio);
//	printf("xtr : %.3f\n", r->x_to_ray_ratio);
//	printf("\nrty : %.3f\n", r->ray_to_y_ratio);
//	printf("ytr : %.3f\n", r->y_to_ray_ratio); 

double	normalize_angle(double angle)
{
	while (angle <= 0)
		angle += 360;
	while (360 < angle)
		angle -= 360;
	return (angle);
}

uint32_t	get_rgba(t_colour *c)
{
	uint32_t	rgba;

	rgba = (c->r << 24 | c->g << 16 | c->b << 8 | 255);
	return (rgba);
}

double	set_precision(double value, long precision)
{
	return (floor(value * precision) / precision);
}