/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/04/04 13:19:42 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//loads the configs from d-lvl
void	init_lvl(void)
{

}

//loads the map from d->lvl
void	init_map(void)
{
	t_data		*d;
	t_coords	*tc;
	int			i;

	d = get_data();
	tc = ft_calloc(1, sizeof(t_coords));
	i = -1;
	while (d->lvl[i + 1] == '\n') //	skips initial empty lines
		i++;
	while (d->lvl[++i]) //				ASSUMES THAT LVL[i] IS AT MAP STARTS BY DEFAULT
	{

	}
}
