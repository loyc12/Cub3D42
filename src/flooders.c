/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flooders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:17:14 by llord             #+#    #+#             */
/*   Updated: 2023/04/07 12:25:12 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//checks wheter the player is enclosed
void	flood_check(t_tile *tile)
{
	if (!tile || tile->type == TTYPE_VOID)
		exit_err(ERR_LVL_OP);

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

