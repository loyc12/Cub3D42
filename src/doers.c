/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_actions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/30 11:57:53 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	key_esc(void)
{
	mlx_close_window(get_master()->window);
	return ;
}

void	remove_wall(t_master *d)
{
	t_slice	*slice;

	slice = cast_ray(d->player->vector, 0);
	if (slice->hit_tile)
		slice->hit_tile->type = TTYPE_ROOM;
	d->should_refresh = true;
}

void	place_wall(t_master *d)
{
	t_slice	*slice;

	slice = cast_ray(d->player->vector, 0);
	if (slice->hit_tile)
	{
		if (slice->hit_dir == 0 && slice->hit_tile->south)
			slice->hit_tile->south->type = TTYPE_WALL;
		if (slice->hit_dir == 1 && slice->hit_tile->west)
			slice->hit_tile->west->type = TTYPE_WALL;
		if (slice->hit_dir == 2 && slice->hit_tile->north)
			slice->hit_tile->north->type = TTYPE_WALL;
		if (slice->hit_dir == 3 && slice->hit_tile->east)
			slice->hit_tile->east->type = TTYPE_WALL;
	}
	d->should_refresh = true;
}

void	respawn_player(t_master *d)
{
	free(d->player->vector);
	d->player->vector = coords_to_vector(d->spawn->coords);
	d->should_refresh = true;
}
