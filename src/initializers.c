/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/05/22 14:10:30 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_player(void)
{
	//...
}

//creates the map grid from the map-info contained in d.level
void	init_map(void)
{
	check_map(); //				verifies each map character and the total map lenght
	build_map(get_master()); //	creates the unconnected tiles for the map grid
	connect_map(); //			connects all the map's tiles into a tile grid
	flood_check_map(); //		verifies that the map is closed around the player
//	init_player() //			creates the player's entity
}
