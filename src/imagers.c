/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imagers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:57:50 by llord             #+#    #+#             */
/*   Updated: 2023/06/13 10:08:36 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//draws an imaged on screen based on its coords and id
mlx_image_t	*make_background(void)
{
	mlx_image_t	*background;
	t_master	*d;

	d = get_master();
	background = mlx_new_image(d->window, SCREEN_WIDTH, SCREEN_HEIGHT);

	ft_memset(background->pixels, 128, background->width * background->height * BPP); //	DEBUG

	mlx_image_to_window(d->window, background, 0, 0);

	return (background);
}

//initializes a single mlx image
mlx_texture_t	*make_texture(char *path)
{
	mlx_texture_t	*texture;
	xpm_t			*xpm;

	texture = ft_calloc(1, sizeof(texture));
	xpm = mlx_load_xpm42(path);

	*texture = xpm->texture; //		copies the texture from xpm_t
	mlx_delete_xpm42(xpm);

	return (texture);
}
