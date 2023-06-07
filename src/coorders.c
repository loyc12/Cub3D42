/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coorders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/07 10:40:58 by llord            ###   ########.fr       */
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

//creates a vector at the center of a tile (from its coords)
t_vector	*coords_to_vector(t_coords	*_c)
{
	t_vector	*v;

	v = ft_calloc(1, sizeof(t_vector));
	v->x = (double)_c->x + (double)0.5;
	v->y = (double)_c->y + (double)0.5;
	return (v);
}
