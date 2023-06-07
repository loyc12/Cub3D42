/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/07 10:10:04 by llord            ###   ########.fr       */
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

//verifies the inputs (arguments and level file) are valid
void	init_game(int ac, char **av)
{
	if (ac != 2)
		close_with_error(ERR_ARG_COUNT);

	read_level(av[1]);

	printf(">%s<\n\n", get_master()->level); //	0============ DEBUG ============0

	init_map();

//	print_tiles(); //							0============ DEBUG ============0

//	init_window();
	print_paths(); //							0============ DEBUG ============0
	print_colours(); //							0============ DEBUG ============0

}

int	main(int ac, char **av)
{
	init_game(ac, av);

//	...

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
//			check_flood_fill()		verifies that the map is closed
			init_player() //		creates the player's entity
		init_window()
			init_mlx()
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
			from position with angle
			find the nearest wall
			return wall type, distance and hit position (in a struct?)
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
