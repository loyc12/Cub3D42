/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_checkers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 12:45:01 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 10:27:59 by llord            ###   ########.fr       */
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
	int		j;

	level = get_master()->level;
	j = 0;
	while (level[i + j] && level[i + j] != '\n')
	{
		if (!ft_isspace(level[i + j]))
		{
			if (is_char_valid(level[i + j]))
				j++;
			else
				return (false);
		}
		else
			i++;
	}
	if (j == 0)
		return (false);
	return (true);
}

//Verifies that the texture paths are valid
void	check_assets(void)
{
	t_master	*d;
	int			fd;
	int			i;

	d = get_master();
	i = 3;
	while (i >= 0)
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

//Verifies colour validity (0 <= c.v <= 255)
bool	is_colour_valid(int v)
{
	if (v < 0 || 255 < v)
		return (false);
	else
		return (true);
}

//Verifies that the floor & ceiling colours are within bounds
void	check_colours(void)
{
	t_colour	*cc;
	t_colour	*cf;

	cc = get_master()->c_ceiling;
	cf = get_master()->c_floor;
	if (!cc || !cf)
		close_with_error(ERR_FILE_SPECS);
	if (!is_colour_valid(cc->r) || !is_colour_valid(cc->g) || !is_colour_valid(cc->b))
		close_with_error(ERR_FILE_COLOR);
	if (!is_colour_valid(cf->r) || !is_colour_valid(cf->g) || !is_colour_valid(cf->b))
		close_with_error(ERR_FILE_COLOR);
}
