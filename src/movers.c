/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:32 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 12:56:20 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_entity(t_entity *e, double angle)
{
	double	dx;
	double	dy;

	dx = cos(M_PI * (e->vector->d + angle) / 180);
	dy = sin(M_PI * (e->vector->d + angle) / 180);

	//check for colisions

	e->vector->x += dx * WALK_SPEED;
	e->vector->y += dy * WALK_SPEED;
}
