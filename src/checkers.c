/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/14 11:01:39 by llord            ###   ########.fr       */
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

//Verifies that the texture paths are valid
void	check_assets(void)
{
	t_master	*d;
	int			fd;
	int			i;

	d = get_master();
	i = 3;
	while (i >= 0) // checks asset paths [1] to [4]
	{
		if (d->t_paths[i])
		{
			fd = open(d->t_paths[i], O_RDONLY);
			if (fd < 0)
				close_with_error(ERR_FILE_ASSET);
			close(fd);
		}
		else
			close_with_error(ERR_FILE_SPECS);
		i--;
	}
}

//Verifies that the floor & ceiling colours are within bounds
void	check_colours(void)
{
	t_master	*d;

	d = get_master();
	if (!(d->c_ceiling) || !(d->c_floor))
		close_with_error(ERR_FILE_SPECS);
	if (d->c_ceiling->r > 255 || d->c_ceiling->g > 255 || d->c_ceiling->b > 255 || \
		d->c_floor->r > 255 || d->c_floor->g > 255 || d->c_floor->b > 255)
		close_with_error(ERR_FILE_COLOR);
	if (d->c_ceiling->r < 0 || d->c_ceiling->g < 0 || d->c_ceiling->b < 0 || \
		d->c_floor->r < 0 || d->c_floor->g < 0 || d->c_floor->b < 0)
		close_with_error(ERR_FILE_COLOR);

}
