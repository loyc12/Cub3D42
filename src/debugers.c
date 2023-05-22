/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:51:15 by llord             #+#    #+#             */
/*   Updated: 2023/05/22 14:05:09 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


//	0================ DEBUG FUNCTIONS ================0


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

void	print_neighbours(t_tile *tile)
{
	/*
	     [x:y]\n
	[x:y] x:y [x:y]\n
	     [x:y]\n
	*/
	printf("\n     [");
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

void	print_tiles(void)
{
	t_tile	**tiles;
	int		i;


	tiles = get_master()->tiles;
	i = -1;
	while (tiles[++i])
	{
		print_neighbours(tiles[i]);
	}
}