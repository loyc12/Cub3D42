/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:36:32 by llord             #+#    #+#             */
/*   Updated: 2023/06/30 12:08:36 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_tile_type(double x, double y)
{
	t_tile	*tile;

	tile = find_tile((int)floor(x), (int)floor(y));
	if (tile)
		return (tile->type);
	else
		return (TTYPE_ERROR);
}

int	check_colision(t_entity *e, double dx, double dy)
{
	if (get_tile_type(e->vector->x + dx + e->radius, e->vector->y + dy
			+ e->radius))
		return (1);
	if (get_tile_type(e->vector->x + dx - e->radius, e->vector->y + dy
			+ e->radius))
		return (1);
	if (get_tile_type(e->vector->x + dx - e->radius, e->vector->y + dy
			- e->radius))
		return (1);
	if (get_tile_type(e->vector->x + dx + e->radius, e->vector->y + dy
			- e->radius))
		return (1);
	return (0);
}

void	move_entity(t_entity *e, double angle)
{
	double	dx;
	double	dy;

	dx = WALK_SPEED * cos(M_PI * (e->vector->d + angle) / 180);
	dy = WALK_SPEED * sin(M_PI * (e->vector->d + angle) / 180);
	if (get_master()->run)
	{
		dx *= RUN_FACTOR;
		dy *= RUN_FACTOR;
	}
	if (check_colision(e, dx, dy) == 0)
	{
		e->vector->x += dx;
		e->vector->y += dy;
	}
	else if (check_colision(e, dx, 0) == 0)
		e->vector->x += dx;
	else if (check_colision(e, 0, dy) == 0)
		e->vector->y += dy;
}

void	move_towards(double angle)
{
	t_entity	*player;

	player = get_master()->player;
	move_entity(player, angle);
	get_master()->should_refresh = true;
}

/*
void	turn_left(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	if (get_master()->run)
		pv->d = normalize_angle(pv->d - (TURN_SPEED * RUN_FACTOR));
	else
		pv->d = normalize_angle(pv->d - TURN_SPEED);
	get_master()->should_refresh = true;
}

void	turn_right(void)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	if (get_master()->run)
		pv->d = normalize_angle(pv->d + (TURN_SPEED * RUN_FACTOR));
	else
		pv->d = normalize_angle(pv->d + TURN_SPEED);
	get_master()->should_refresh = true;
}
*/

void	turn_angle(double angle)
{
	t_vector	*pv;

	pv = get_master()->player->vector;
	if (get_master()->run)
		pv->d = normalize_angle(pv->d + (angle * RUN_FACTOR));
	else
		pv->d = normalize_angle(pv->d + angle);
	get_master()->should_refresh = true;
}
