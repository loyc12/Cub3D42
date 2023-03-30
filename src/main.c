/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/03/30 10:59:11 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//this function acts as a pseudo "global" t_data var
t_data	*get_data(void)
{
	static t_data	*d;

	if (!d)
	{
		d = ft_calloc(1, sizeof(t_data));
	}

	return (d);
}

//tries to free everything and returns t_data state
int	free_data(void)
{
	t_data	*d;
	int		state;

	d = get_data();
	state = d->state;

	ft_free_array(ADRS2 d->tiles);
	ft_free_array(ADRS2 d->assets);
	ft_free_null(ADRS d->player);

	//d->window; //					DESTROY ME

	ft_free_null(ADRS d);

	return (state);
}

//entrypoint function
int	main(int ac, char **av)
{
	t_data	*d;

	if (ac != 2) //				checks for a proper argcount
		return (ft_puterr(ERR_ARG_CO));

	d = get_data(); //			fills the t_data struct with default base values

	d->lvl_fd = get_lvl(av); //	checks and opens the .cub file, returning its fd

	init_lvl(); //				checks and gets the level info from the .cub file
	//	init_asset(texture_path)
	//	set_colour

	init_map(); //				checks and gets the map info from the .cub file (move into init_lvl (?))
	//	init_player(tc)

	init_gfx(); //				initializes the mlx and its textures
	//	init_window
	//	load_assets

	launch_game(); //			main game loop function
	//	check_moves
	//	re_display

	return (free_data());
}
