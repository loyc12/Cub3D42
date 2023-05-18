/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/05/18 10:53:35 by llord            ###   ########.fr       */
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
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		tile->type = TTYPE_ROOM;
		get_data()->spawn = tile;
	}
	else
		tile->type = TTYPE_ERROR;

	printf("Created tile at %i:%i with type ", _tc->x, _tc->y); //	DEBUG
	if (tile->type == TTYPE_ROOM)
		printf("floor");
	else if (tile->type == TTYPE_VOID)
		printf("void ");
	else if (tile->type == TTYPE_WALL)
		printf("wall ");
	else
		printf("%i", tile->type);
	printf(" (%c)\n", c); //	DEBUG

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
	}
}

//DEBUG FUNCTION
void	print_tile(t_tile *tile)
{
	if (tile)
	{
		if (tile->tc)
			printf("%i:%i", tile->tc->x, tile->tc->y);
		else
			printf("ERR");
	}
	else
		printf("NUL");
}

//DEBUG FUNCTION
void	print_neighbours(t_tile *tile)
{
	/*
	     [x:y]\n
	[x:y] x:y [x:y]\n
	     [x:y]\n
	*/
	printf("     [");
	print_tile(tile->north);
	printf("]\n[");
	print_tile(tile->west);
	printf("] ");
	print_tile(tile);
	printf(" [");
	print_tile(tile->east);
	printf("]\n     [");
	print_tile(tile->south);
	printf("]\n");
}

//DEBUG FUNCTION
void	print_tiles(void)
{
	t_tile	**tiles;
	int		i;


	tiles = get_data()->tiles;
	i = -1;
	while (tiles[++i])
	{
		print_neighbours(tiles[i]);
		printf("\n");
	}
}
