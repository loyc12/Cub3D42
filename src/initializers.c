/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/04/06 12:55:00 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//loads the configs from d-lvl
void	init_lvl(void)
{

}

//checks the validity of a map character
bool	is_char_valid(char c)
{
	if (c == ' ' || c == '0' || c == '1')
		return (true);
	return (false);
}

t_tile	*init_tile(char c, t_coords *_tc)
{
	t_tile	*tile;

	tile = ft_calloc(1, sizeof(t_tile));
	tile->tc = coords_copy(_tc);

	if (c == ' ')
		tile->type = TTYPE_VOID;
	else if (c == '1')
		tile->type = TTYPE_WALL;
	else if (c == '0')
		tile->type = TTYPE_ROOM;
	else
		tile->type = TTYPE_ERROR;

	return (tile);
}

//loads the map from d->lvl
void	init_map(void)
{
	t_data		*d;
	t_coords	*tc;
	int			i;
	int			j;

	d = get_data();
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
			printf("\n"); //												DEBUG
			(tc->y)++;
			(tc->x) = 0;
		}
		else if (is_char_valid(d->lvl[i]))
		{
			d->tiles[++j] = init_tile(d->lvl[i], tc);
			printf("created tile %i (type %i) at %i:%i\n", j, d->tiles[j]->type, tc->x, tc->y); //		DEBUG
			(tc->x)++;
		}
		else
		{
			ft_puterr(ERR_LVL_SY);
			d->state = MSTATE_ERROR;
			return ;
		}
	}
	ft_free_null(ADRS tc); //			frees the tile coordinate template
}
