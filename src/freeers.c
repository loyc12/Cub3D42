/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/04/07 12:26:04 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//tries to free every tile
void	free_tiles(t_tile **tiles)
{
	int		i;

	i = -1;
	while (tiles[++i])
	{
		//free the stuff inside the tiles here

		ft_free_null(ADRS tiles[i]->tc);
		ft_free_null(ADRS tiles[i]);
	}
	ft_free_null(ADRS tiles);
}

//tries to free everything and returns t_data state
int	free_data(void)
{
	t_data	*d;
	int		state;

	d = get_data();
	state = d->state;

	//free the stuff inside d here

	free_tiles(d->tiles);
	ft_free_array(ADRS2 d->assets);
	ft_free_null(ADRS d->player);
	ft_free_null(ADRS d->lvl);

	//d->window; //					DESTROY MLX HERE (?)

	ft_free_null(ADRS d); //		MUST BE LAST FREED

	return (state);
}

//frees all and exits if the d->state is negative (error)
void	check_state(void) //									OBSOLETED BY exit_err (?)
{
	if (get_data()->state <= MSTATE_ERROR)
		exit(free_data());
}

//frees all and exits
void	exit_err(char *err)
{
	ft_puterr(err);
	printf("\n");
	get_data()->state = MSTATE_ERROR;
	exit (free_data());
}
