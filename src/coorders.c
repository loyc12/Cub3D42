/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coorders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/04/06 12:00:35 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//duplicates the content of a coords struct into a new one, and returns it
t_coords	*coords_copy(t_coords *_c)
{
	t_coords	*c;

	c = ft_calloc(1, sizeof(t_coords));
	c->x = _c->x;
	c->y = _c->y;
	return (c);
}
