/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_textures.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:50:45 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 10:10:49 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//initializes a single mlx image
//	copies the texture from xpm_t
mlx_texture_t	*make_texture(char *path)
{
	mlx_texture_t *texture;
	xpm_t *xpm;

	texture = ft_calloc(1, sizeof(texture));
	xpm = mlx_load_xpm42(path);
	*texture = xpm->texture;
	mlx_delete_xpm42(xpm);
	return (texture);
}