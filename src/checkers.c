/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/05 11:07:06 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

//checks if the line at level[start] is the begining of the map
bool	is_map_start(int i)
{
	char	*level;
	int		j; //			counts the number of valid chars

	level = get_master()->level;
	j = 0;
	while (level[i + j] && level[i + j] != '\n')
	{
		if (!ft_isspace(level[i + j])) //		ignores spaces
		{
			if (is_char_valid(level[i + j])) //	check if the line has only valid chars
				j++;
			else
				return (false); //				else its not the start of the map
		}
		else
			i++; //			doesn't count spaces as valid chars
	}
	if (j == 0)
		return (false);
	return (true);
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
	if (!tile)
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
