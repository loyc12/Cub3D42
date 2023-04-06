/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/04/06 13:02:56 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

	check_state(); //			aborts process if d->state is negative

	printf(">%s<\n", d->lvl); //						DEBUG

	//init_level();
	//	init_asset(texture_path)
	//	set_colour

	init_map(); //				checks and gets the map info from the .cub file (move into init_lvl (?))
	//	init_player(tc)

	//init_gfx(); //				initializes the mlx and its textures
	//	init_window
	//	load_assets

	//launch_game(); //			main game loop function
	//	check_moves
	//	re_display

	return (free_data());
}
