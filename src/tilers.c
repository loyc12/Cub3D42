/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilers.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/05/26 16:28:06 by llord            ###   ########.fr       */
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
		get_master()->spawn = tile;
	}
	else
		tile->type = TTYPE_ERROR;

	// 0======== DEBUG ========0
	printf("Created tile at %i:%i with type ", _tc->x, _tc->y);
	if (tile->type == TTYPE_ROOM)
		printf("floor");
	else if (tile->type == TTYPE_VOID)
		printf("void ");
	else if (tile->type == TTYPE_WALL)
		printf("wall ");
	else
		printf("%i", tile->type);
	printf(" (%c)\n", c);

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
			if (tc->x >= M_SIZE || tc->y >= M_SIZE)
				exit_err(ERR_MAP_SIZE);
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
