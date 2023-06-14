/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 12:12:38 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//creates the t_master *d struct (first call behaviour)
t_master	*get_master(void)
{
	static t_master	*data;

	if (!data)
		data = ft_calloc(1, sizeof(t_master));
	return (data);
}

void	play_game(t_master *data)
{
	mlx_key_hook(data->window, &key_hook, NULL);
	mlx_loop_hook(data->window, &loop_hook, NULL);
	mlx_loop(data->window);
	mlx_terminate(data->window);
}

int	main(int ac, char **av)
{
	init_game(ac, av);

	play_game(get_master());

	printf("\n");
	return (free_master());
}

/*

use // in front of the line to mark what is completed


//	init_game() //			verifies the argc and init all things
//		read_level() //			opens the .cub file and copies its contents into d.level
//			read_file() //			copies the .cub file's contents into d.level
//			get_info() //			collects and voids the non-map info from d.level
//			check_assets() //		verifies that the texture paths are valid
//			check_colours() //		verifies that the floor & ceiling colours are within bounds
//		init_map() //			creates the map grid from the map-info contained in d.level
//			check_map() //			verifies each map character and the total map lenght
//			build_map()				creates the unconnected tiles for the map grid
//			connect_map() //		connects all the map's tiles into a tile grid
//			check_flood_fill() //	verifies that the map is closed
		init_player() //			creates the player's entity
//		init_window()
//			init_mlx()
			get_textures()
			check_textures()
			open_window()

	game_loop()
	{
		...
		if (...)
			close_game()
	}

	t_master {

		char		*level
		t_colour	colour x 2
		char		*texture x 4
		char		*last_line_read

	}



	player entity
		position
		angle

	do this for every slice of the screen
	{
		ray_cast()
			from player position & angle
			find the nearest wall (from angle relative to player)
				find step direction (+/- x, +/- y)
				find Xi and Yi
				find Xscale and Yscale
				while (!hit)
					check in X until Dx > Dy
					check in Y until Dy > Dx
			return hit struct (distance + position + wall type)
		display_slice()
			display a colum in the midle of the screen (at ray 'position')
			height based on hit distance
			texture based on wall type and hit position
	}

	hitpoint struct
		ray lenght
		wall type
		texture position (x)

*/
