/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_hookers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llord <llord@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 10:46:03 by llord             #+#    #+#             */
/*   Updated: 2023/06/15 12:40:24 by llord            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//normal hook used during the game loop
//	calculate the angle based on the fov
void	loop_hook(void *param)
{
	t_master	*data;
	double		f;
	int			i;

	(void)param;
	data = get_master();
	i = -data->half_width;
	if (data->should_refresh)
	{
		while (i < data->half_width)
		{
			f = data->fov_ratio * i;
			f *= sin((180 - f) * M_PI / 360);
			draw_slice(data, cast_ray(data->player->vector, f), i);
			i++;
		}
		data->should_refresh = false;
	}
}

//key hook used during the game loop
void	key_hook(mlx_key_data_t keydata, void *param)
{
	(void)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		key_esc();
	if (!(keydata.key == MLX_KEY_ESCAPE) && !get_master()->should_refresh)
	{
		if (keydata.key == MLX_KEY_W)
			move_towards(0);
		if (keydata.key == MLX_KEY_S)
		{
			move_towards(180);
			get_master()->run = false;
		}
		if (keydata.key == MLX_KEY_D)
			turn_left();
		if (keydata.key == MLX_KEY_A)
			turn_right();
		if (keydata.key == MLX_KEY_E)
			move_towards(90);
		if (keydata.key == MLX_KEY_Q)
			move_towards(270);
		if (keydata.key == MLX_KEY_LEFT_SHIFT)
			get_master()->run = true;
	}
}
