/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/06 13:46:44 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//creates a tile of a given type with the copy of given coords
t_tile	*create_tile(char c, t_coords *_tc)
{
	t_tile	*tile;

	tile = ft_calloc(1, sizeof(t_tile));
	tile->tc = coords_copy(_tc);

	if (c == '0')
		tile->type = TTYPE_ROOM;
	else if (c == '1')
		tile->type = TTYPE_WALL;
	else if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		tile->type = TTYPE_ROOM;
		get_master()->spawn = tile;
	}
	else
		tile->type = TTYPE_ERROR;

//	announce_tile(tile, c); // 			0======== DEBUG ========0

	return (tile);
}

//creates the unconnected tiles for the map grid
void	build_map(t_master *d)
{
	t_coords	*tc;
	int			i;
	int			j;

	tc = ft_calloc(1, sizeof(t_coords));
	i = -1;
	while (d->level[i + 1] == '\n') //	skips initial empty lines
		i++;
	d->tiles = ft_calloc(ft_strlen(&(d->level[i])), sizeof(t_tile *)); // makes the tile array longer than needed
	j = -1;
	while (d->level[++i]) //
	{
		if (d->level[i] != '\n') //		if newline: increments y and reset x
		{
			if (tc->x >= MAX_MAP_SIZE || tc->y >= MAX_MAP_SIZE)
				close_with_error(ERR_MAP_SIZE);
			if (!ft_isspace(d->level[i]))
				d->tiles[++j] = create_tile(d->level[i], tc);
		}
		else
		{
			(tc->y)++;
			(tc->x) = -1;
		}
		(tc->x)++;
	}
	ft_free_null(ADRS tc); //			frees the tile coordinate template
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
		if (tiles[i]->tc->x == x && tiles[i]->tc->y == y)
			return (tiles[i]);
	}
	return (NULL);
}

//connects tiles with their neighbours (creates the map grid)
void	connect_map(void)
{
	t_tile		**tiles;
	int			i;

	tiles = get_master()->tiles;
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
