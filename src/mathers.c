/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_maths.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:32 by llord             #+#    #+#             */
/*   Updated: 2023/06/16 12:19:48 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//Finds the size ratio of the angle when projected on the x | y axis
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

//Caps the angles above 0 and bellow 360
double	normalize_angle(double angle)
{
	while (angle <= 0)
		angle += 360;
	while (360 < angle)
		angle -= 360;
	return (angle);
}

//Multiplies the colour value by a scale and rounds it to pixel size (for fun)
int	get_colour_value(int c, double s)
{
	return ((((int)(c * s)))); // / COLOUR_DEF) * COLOUR_DEF); //	slows rendering by ~ 10%
}

//Converts a colour struct into a uin32 for mlx usage
uint32_t	get_rgba(t_colour *c, double scale)
{
	uint32_t	rgba;

	rgba = (get_colour_value(c->r, scale) << 24 | \
		get_colour_value(c->g, scale) << 16 | \
		get_colour_value(c->b, scale) << 8 | 255);
	return (rgba);
}

//rounds of a double at a given fractional value
double	set_precision(double value, long precision)
{
	return (floor(value * precision) / precision);
}
