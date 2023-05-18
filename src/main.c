/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/05/18 10:45:17 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*

mostly done
- error handling
- map parsing
- tile connecting

to start
- getting level data (textures/colours)
- initializing textures
- flood fill checks
- initializing player

to do
- raycasting
- graphic managment
- input management
- collision management
- bonuses (?)

*/

//entrypoint function
int	main(int ac, char **av)
{
	t_data	*d;

	// Initial checks for argcount and openability
	if (ac != 2)
		return (ft_puterr(ERR_ARG_CO));
	if (access(av[1], F_OK) || access(av[1], R_OK))
		return (ft_puterr(ERR_ARG_OP));

	d = get_data(); //			creates the t_data *d struct when first called, accesses it after
	get_lvl(av[1]); //			opens and copies the lvl file into d->lvl

	printf(">%s<\n", d->lvl); // 0============ DEBUG ============0

	//init_level(); //			should remove the non-map data (replace it by \n (?))
	//	get_line_data(); //
	//		get_line_type(); //

	init_map(d); //				checks and gets the map info from the .cub file (move into init_lvl (?))
	connect_tiles(); //			connects tiles with their neighbours
	flood_check(d->spawn);
	//init_player()

	print_tiles(); //			0============ DEBUG ============0

	//init_gfx(); //			initializes the mlx and its textures
	//	init_window();
	//	init_textures();

	//launch_game(); //			main game loop function
	//	check_moves
	//	re_display

	printf("\n");
	return (free_data());
}


/*
	check_for_intial_errors()

	t_master *data = get_data()

	get_level_info()
		get_info()
		check_info()

	get_level_map() // takes the map data and puts it into a string
		get_map()
		check_map()

	init_map() // takes the map string and turns it into tiles
		build_tiles()
			? init_player() // creates the player's entity struct
		connect_tiles()
		check_flood_fill()





	t_master {

		char		*map
		t_colour	colour x 2
		char		*texture x 4
		char		*last_line_read

	}




*/

