/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flooders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 10:59:33 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//recursively checks whether a room is next to void
void	flood_check(t_tile *tile)
{
	if (!tile)
		close_with_error(ERR_MAP_BOUND);

	if (tile->fff == 0)
	{
		tile->fff++;
		if (tile->type != TTYPE_WALL)
		{
			flood_check(tile->north);
			flood_check(tile->east);
			flood_check(tile->south);
			flood_check(tile->west);
		}
	}
}

//verifies that the map is closed around the player
void	flood_check_map(void)
{
	t_tile	*tile;

	tile = get_master()->spawn;

	tile->fff = 0;
	flood_check(tile->north);
	flood_check(tile->east);
	flood_check(tile->south);
	flood_check(tile->west);
}
