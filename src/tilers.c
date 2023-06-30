/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/30 12:12:41 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//creates a tile of a given type with the copy of given coords
t_tile	*create_tile(char c, t_coords *_coords)
{
	t_tile	*tile;

	tile = ft_calloc(1, sizeof(t_tile));
	tile->coords = coords_copy(_coords);
	if (c == '0')
		tile->type = TTYPE_ROOM;
	else if (c == '1')
		tile->type = TTYPE_WALL;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		tile->type = TTYPE_ROOM;
		get_master()->spawn = tile;
		get_master()->player_dir = c;
	}
	else
		tile->type = TTYPE_ERROR;
	return (tile);
}

//finds a tile in d->tiles based on given x and y coords
t_tile	*find_tile(int x, int y)
{
	t_tile	**tiles;
	int		i;

	tiles = get_master()->tiles;
	i = -1;
	while (tiles[++i])
	{
		if (tiles[i]->coords->x == x && tiles[i]->coords->y == y)
			return (tiles[i]);
	}
	return (NULL);
}

//creates the unconnected tiles for the map grid
void	build_map(t_master *d)
{
	t_coords	coords;
	int			i;
	int			j;

	coords.x = 0;
	coords.y = 0;
	i = -1;
	while (d->level[i + 1] == '\n')
		i++;
	d->tiles = ft_calloc(ft_strlen(&(d->level[i])), sizeof(t_tile *));
	j = -1;
	while (d->level[++i])
	{
		if (d->level[i] != '\n')
		{
			if (coords.x >= MAX_MAP_SIZE || coords.y >= MAX_MAP_SIZE)
				close_with_error(ERR_MAP_SIZE);
			if (!ft_isspace(d->level[i]))
				d->tiles[++j] = create_tile(d->level[i], &coords);
		}
		else
		{
			(coords.y)++;
			(coords.x) = -1;
		}
		(coords.x)++;
	}
}

//connects tiles with their neighbours (creates the map grid)
void	connect_map(void)
{
	t_tile	**tiles;
	int		i;

	tiles = get_master()->tiles;
	i = -1;
	while (tiles[++i])
	{
		tiles[i]->west = find_tile((tiles[i]->coords->x) - 1, \
			(tiles[i]->coords->y));
		if (tiles[i]->west)
			tiles[i]->west->east = tiles[i];
		tiles[i]->north = find_tile((tiles[i]->coords->x), (tiles[i]->coords->y)
				- 1);
		if (tiles[i]->north)
			tiles[i]->north->south = tiles[i];
	}
}
