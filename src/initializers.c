/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/04/07 12:12:03 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//loads the configs from d-lvl
void	init_lvl(t_data *d)
{
	(void)d;
	/*
	match initial chars
	skip spaces
	check path/colour validity
	add it to t_data *d
	*/
}

//checks the validity of a map character
bool	is_char_valid(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (true);
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
	{
		get_data()->pf++;
		return (true);
	}
	return (false);
}

//loads the map from d->lvl
void	init_map(t_data *d)
{
	t_coords	*tc;
	int			i;
	int			j;

	tc = ft_calloc(1, sizeof(t_coords));
	i = -1;
	while (d->lvl[i + 1] == '\n') //	skips initial empty lines
		i++;
	d->tiles = ft_calloc(ft_strlen(&(d->lvl[i])), sizeof(t_tile *)); // makes the tile array longer than needed
	j = -1;
	while (d->lvl[++i]) //				ASSUMES THAT LVL[i] IS AT MAP STARTS BY DEFAULT
	{
		if (d->lvl[i] == '\n') //		if neline: increments y and reset x
		{
			(tc->y)++;
			(tc->x) = -1;
		}
		else if (is_char_valid(d->lvl[i])) //	if char is valid: create a tiele
			d->tiles[++j] = create_tile(d->lvl[i], tc);
		else
			exit_err(ERR_LVL_SY);
		(tc->x)++;
	}
	if (get_data()->pf != 1)
		exit_err(ERR_LVL_PL);
	ft_free_null(ADRS tc); //			frees the tile coordinate template
}
