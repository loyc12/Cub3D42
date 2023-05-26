/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/05/26 16:32:08 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//tries to free every tile
void	free_tiles(t_master *data)
{
	int		i;

	if (data->tiles)
	{
		i = -1;
		while (data->tiles[++i])
		{
			//free the stuff inside the tiles here

			ft_free_null(ADRS data->tiles[i]->tc);
			ft_free_null(ADRS data->tiles[i]);
		}
		ft_free_null(ADRS data->tiles);
	}
}

//tries to free everything and returns t_master state
int	free_master(void)
{
	t_master	*data;
	int			state;

	data = get_master();
	state = data->master_state;

	//free the stuff inside d here

	free_tiles(data);
	ft_free_array(ADRS2 data->assets);
	ft_free_null(ADRS data->player);
	ft_free_null(ADRS data->level);

	//d->window; //					DESTROY MLX HERE (?)

	ft_free_null(ADRS data); //		MUST BE LAST FREED

	return (state);
}

//frees all and exits
void	close_with_error(char *err)
{
	ft_puterr(err);
	printf("\n");
	get_master()->master_state = MSTATE_ERROR;
	exit (free_master());
}
