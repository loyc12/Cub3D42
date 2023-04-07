/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/04/07 10:00:54 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//creates a tile of a given type with the copy of given coords
t_tile	*create_tile(char c, t_coords *_tc)
{
	t_tile	*tile;

	tile = ft_calloc(1, sizeof(t_tile));
	tile->tc = coords_copy(_tc);


	if (c == ' ')
		tile->type = TTYPE_VOID;
	else if (c == '1')
		tile->type = TTYPE_WALL;
	else if (c == '0')
		tile->type = TTYPE_ROOM;
	else
		tile->type = TTYPE_ERROR;

	printf("Created tile at %i:%i with type %i(%c)\n", _tc->x, _tc->y, tile->type, c); //	DEBUG
	return (tile);
}

// Tries to find a tile in d->tiles based on given x and y coords
t_tile	*find_tile(int x, int y)
{
	t_tile	**tiles;
	int		i;

	tiles = get_data()->tiles;
	i = -1;
	while (tiles[++i])
	{
		if (tiles[i]->tc->x == x && tiles[i]->tc->y == y)
			return (tiles[i]);
	}
	return (NULL);
}

// Tries to connect all tiles with their neighbour
void	connect_tiles(void)
{
	t_tile	**tiles;
	int		i;

	printf("\n"); //			DEBUG

	tiles = get_data()->tiles;
	i = -1;
	while (tiles[++i])
	{
		tiles[i]->west = find_tile((tiles[i]->tc->x) - 1, (tiles[i]->tc->y));
		if (tiles[i]->west)
			tiles[i]->west->east = tiles[i];

		tiles[i]->north = find_tile((tiles[i]->tc->x), (tiles[i]->tc->y) - 1);
		if (tiles[i]->north)
			tiles[i]->north->south = tiles[i];

		//	PRINTS DEBUG INFO
		printf("Connected tile at %i:%i with neighbours  :  ", tiles[i]->tc->x, tiles[i]->tc->y);
		if (tiles[i]->west)
			printf("W = %i:%i  :  ", (tiles[i]->tc->x) - 1, (tiles[i]->tc->y));
		else
			printf("W = NONE :  ");
		if (tiles[i]->north)
			printf("N = %i:%i\n", (tiles[i]->tc->x), (tiles[i]->tc->y) - 1);
		else
			printf("N = NONE\n");
	}
}
