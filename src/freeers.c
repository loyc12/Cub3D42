/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_freeers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 08:55:54 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 14:57:53 by llord            ###   ########.fr       */
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
			ft_free_null(ADRS data->tiles[i]->coords);
			ft_free_null(ADRS data->tiles[i]);
		}
		ft_free_null(ADRS data->tiles);
	}
}

//tries to free every tile
void	free_textures(t_master *data)
{
	int		i;

	if (data->textures)
	{
		i = -1;
		while (data->textures[++i])
		{
			mlx_delete_texture(data->textures[i]);
		}
		ft_free_null(ADRS data->textures);
	}
}

void	free_entity(t_entity *entity)
{
	if (entity)
	{
		ft_free_null(ADRS entity->vector);
		ft_free_null(ADRS entity);
	}
}

//tries to free everything and returns t_master state
int	free_master(void)
{
	t_master	*data;
	int			state;

	data = get_master();
	state = data->master_state;
	free_tiles(data);
	free_textures(data);
	free_entity(data->player);
	ft_free_null(ADRS data->level);
	ft_free_null(ADRS data->c_ceiling);
	ft_free_null(ADRS data->c_floor);
	ft_free_array(ADRS2 data->t_paths);
	ft_free_null(ADRS data);
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
