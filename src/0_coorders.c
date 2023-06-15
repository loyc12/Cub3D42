/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_coorders.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 09:38:50 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//duplicates the content of a coords struct into a new one, and returns it
t_coords	*coords_copy(t_coords *_c)
{
	t_coords	*c;

	c = ft_calloc(1, sizeof(t_coords));
	c->x = _c->x;
	c->y = _c->y;
	return (c);
}

//creates a vector at the center of a tile (from its coords)
t_vector	*coords_to_vector(t_coords *_c)
{
	t_vector	*v;

	v = ft_calloc(1, sizeof(t_vector));
	v->x = (double)_c->x + (double)0.5;
	v->y = (double)_c->y + (double)0.5;
	return (v);
}

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
