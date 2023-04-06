/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/04/06 14:11:58 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*

moslty done
- map parsing
- tile connecting

started
- getting level data (textures/colours)
- flood fill checks
- initializing player
- initializing textures

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

	// Initial checks for argcount and opennability
	if (ac != 2)
		return (ft_puterr(ERR_ARG_CO));
	if (access(av[1], F_OK) || access(av[1], R_OK))
		return (ft_puterr(ERR_ARG_OP));

	d = get_data(); //			creates the t_data *d struct when first called, accesses it after
	get_lvl(av[1]); //			opens and copies the lvl file into d->lvl

	printf(">%s<\n", d->lvl); //						DEBUG

	//init_level(); //			should remove the non-map data (replace it by \n (?))

	init_map(d); //				checks and gets the map info from the .cub file (move into init_lvl (?))
	connect_tiles(); //			connects tiles with their neighbours
	//init_player(tc)

	//init_gfx(); //			initializes the mlx and its textures
	//	init_window();
	//	init_textures();

	//launch_game(); //			main game loop function
	//	check_moves
	//	re_display

	return (free_data());
}
