/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:01 by llord             #+#    #+#             */
/*   Updated: 2023/05/26 16:32:26 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//verifies each map character and the total map lenght
void	check_info(void)
{
	//...
}

//checks the validity of a map character
bool	is_char_valid(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (true);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		get_master()->player_spawn_count++;
		return (true);
	}
	return (false);
}

//verifies each map character and the total map lenght
void	check_map(void)
{
	t_master	*data;
	int			i;

	data = get_master();
	i = -1;
	while (data->level[i + 1] == '\n') //	skips initial empty lines
		i++;

	i = -1;
	while (data->level[++i])
	{
		if (data->level[i] != '\n' && !is_char_valid(data->level[i]))
			close_with_error(ERR_MAP_CHAR);
	}
	if (data->player_spawn_count != 1)
		close_with_error(ERR_MAP_PLAYER);
}

//recursively checks whether a room is next to void
void	flood_check(t_tile *tile)
{
	if (!tile || tile->type == TTYPE_VOID)
		close_with_error(ERR_MAP_BOUND);

	if (tile->fff == 0)
	{
		tile->fff++;
		if (tile->type != TTYPE_WALL)
		{
			flood_check(tile->north);
			flood_check(tile->east);
			flood_check(tile->south);
			flood_check(tile->west);
		}
	}
}

//verifies that the map is closed around the player
void	flood_check_map(void)
{
	t_tile	*tile;

	tile = get_master()->spawn;

	tile->fff = 0;
	flood_check(tile->north);
	flood_check(tile->east);
	flood_check(tile->south);
	flood_check(tile->west);
}