/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/04/06 13:40:57 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//loads the configs from d-lvl
void	init_lvl(t_data *d)
{
	(void)d;
}

//checks the validity of a map character
bool	is_char_valid(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (true);
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
		if (d->lvl[i] == '\n') //		increments y and reset x when changing line
		{
			(tc->y)++;
			(tc->x) = -1;
		}
		else if (is_char_valid(d->lvl[i]))
			d->tiles[++j] = create_tile(d->lvl[i], tc);
		else
			exit_err(ERR_LVL_SY);
		(tc->x)++;
	}
	ft_free_null(ADRS tc); //			frees the tile coordinate template
}
